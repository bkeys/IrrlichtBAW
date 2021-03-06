#define _IRR_STATIC_LIB_
#include <irrlicht.h>
#include "driverChoice.h"
#include <string>
#include "../source/Irrlicht/CGeometryCreator.h"

using namespace irr;
using namespace core;
using namespace scene;


#define kNumHardwareInstancesX 10
#define kNumHardwareInstancesY 20
#define kNumHardwareInstancesZ 30

#define kHardwareInstancesTOTAL (kNumHardwareInstancesX*kNumHardwareInstancesY*kNumHardwareInstancesZ)


const float instanceLoDDistances[] = {8.f,50.f};

bool quit = false;


//!Same As Last Example
class MyEventReceiver : public IEventReceiver
{
public:

	MyEventReceiver()
	{
	}

	bool OnEvent(const SEvent& event)
	{
        if (event.EventType == irr::EET_KEY_INPUT_EVENT && !event.KeyInput.PressedDown)
        {
            switch (event.KeyInput.Key)
            {
            case irr::KEY_KEY_Q: // switch wire frame mode
                quit = true;
                return true;
            default:
                break;
            }
        }

		return false;
	}

private:
};

const char* uniformNames[] =
{
    "ProjViewWorldMat",
    "WorldMat",
    "ViewWorldMat",
    "eyePos",
    "LoDInvariantMinEdge",
    "LoDInvariantBBoxCenter",
    "LoDInvariantMaxEdge",
    "instanceLoDDistancesSQ"
};

enum E_UNIFORM
{
    EU_PROJ_VIEW_WORLD_MAT = 0,
    EU_WORLD_MAT,
    EU_VIEW_WORLD_MAT,
    EU_EYE_POS,
    EU_LOD_INVARIANT_MIN_EDGE,
    EU_LOD_INVARIANT_BBOX_CENTER,
    EU_LOD_INVARIANT_MAX_EDGE,
    EU_INSTANCE_LOD_DISTANCE_SQ,
    EU_COUNT
};

class SimpleCallBack : public video::IShaderConstantSetCallBack
{
    video::E_MATERIAL_TYPE currentMat;
    int32_t uniformLocation[video::EMT_COUNT+2][EU_COUNT];
    video::E_SHADER_CONSTANT_TYPE uniformType[video::EMT_COUNT+2][EU_COUNT];
    float currentLodPass;
public:
    core::aabbox3df instanceLoDInvariantBBox;

    SimpleCallBack()
    {
        for (size_t i=0; i<EU_COUNT; i++)
        for (size_t j=0; j<video::EMT_COUNT+2; j++)
            uniformLocation[j][i] = -1;
    }

    virtual void PostLink(video::IMaterialRendererServices* services, const video::E_MATERIAL_TYPE& materialType, const core::array<video::SConstantLocationNamePair>& constants)
    {
        for (size_t i=0; i<constants.size(); i++)
        for (size_t j=0; j<EU_COUNT; j++)
        {
            if (constants[i].name==uniformNames[j])
            {
                uniformLocation[materialType][j] = constants[i].location;
                uniformType[materialType][j] = constants[i].type;
                break;
            }
        }
    }

    virtual void OnSetMaterial(video::IMaterialRendererServices* services, const video::SMaterial& material, const video::SMaterial& lastMaterial)
    {
        currentMat = material.MaterialType;
        currentLodPass = material.MaterialTypeParam;
    }

    virtual void OnSetConstants(video::IMaterialRendererServices* services, int32_t userData)
    {
        if (uniformLocation[currentMat][EU_PROJ_VIEW_WORLD_MAT]>=0)
            services->setShaderConstant(services->getVideoDriver()->getTransform(video::EPTS_PROJ_VIEW_WORLD).pointer(),uniformLocation[currentMat][EU_PROJ_VIEW_WORLD_MAT],uniformType[currentMat][EU_PROJ_VIEW_WORLD_MAT],1);
        if (uniformLocation[currentMat][EU_VIEW_WORLD_MAT]>=0)
            services->setShaderConstant(services->getVideoDriver()->getTransform(video::E4X3TS_WORLD_VIEW).pointer(),uniformLocation[currentMat][EU_VIEW_WORLD_MAT],uniformType[currentMat][EU_VIEW_WORLD_MAT],1);
        if (uniformLocation[currentMat][EU_WORLD_MAT]>=0)
            services->setShaderConstant(services->getVideoDriver()->getTransform(video::E4X3TS_WORLD).pointer(),uniformLocation[currentMat][EU_WORLD_MAT],uniformType[currentMat][EU_WORLD_MAT],1);

        if (uniformLocation[currentMat][EU_EYE_POS]>=0)
        {
            core::vectorSIMDf eyePos;
            eyePos.set(services->getVideoDriver()->getTransform(video::E4X3TS_VIEW_INVERSE).getTranslation());
            services->setShaderConstant(eyePos.pointer,uniformLocation[currentMat][EU_EYE_POS],uniformType[currentMat][EU_EYE_POS],1);
        }

        if (uniformLocation[currentMat][EU_LOD_INVARIANT_BBOX_CENTER]>=0)
        {
            services->setShaderConstant(&instanceLoDInvariantBBox.MinEdge,uniformLocation[currentMat][EU_LOD_INVARIANT_MIN_EDGE],uniformType[currentMat][EU_LOD_INVARIANT_MIN_EDGE],1);
            core::vector3df centre = instanceLoDInvariantBBox.getCenter();
            services->setShaderConstant(&centre,uniformLocation[currentMat][EU_LOD_INVARIANT_BBOX_CENTER],uniformType[currentMat][EU_LOD_INVARIANT_BBOX_CENTER],1);
            services->setShaderConstant(&instanceLoDInvariantBBox.MaxEdge,uniformLocation[currentMat][EU_LOD_INVARIANT_MAX_EDGE],uniformType[currentMat][EU_LOD_INVARIANT_MAX_EDGE],1);
        }


        if (uniformLocation[currentMat][EU_INSTANCE_LOD_DISTANCE_SQ]>=0)
        {
            float distancesSQ[2];
            distancesSQ[0] = instanceLoDDistances[0]*instanceLoDDistances[0];
            distancesSQ[1] = instanceLoDDistances[1]*instanceLoDDistances[1];
            services->setShaderConstant(distancesSQ,uniformLocation[currentMat][EU_INSTANCE_LOD_DISTANCE_SQ],uniformType[currentMat][EU_INSTANCE_LOD_DISTANCE_SQ],1);
        }
    }

    virtual void OnUnsetMaterial() {}
};


 IGPUMeshDataFormatDesc* vaoSetupOverride(ISceneManager* smgr, video::IGPUBuffer* instanceDataBuffer, const size_t& dataSizePerInstanceOutput, const scene::IGPUMeshDataFormatDesc* oldVAO, void* userData)
 {
    video::IVideoDriver* driver = smgr->getVideoDriver();
    scene::IGPUMeshDataFormatDesc* vao = driver->createGPUMeshDataFormatDesc();

    //
    for (size_t k=0; k<EVAI_COUNT; k++)
    {
        E_VERTEX_ATTRIBUTE_ID attrId = (E_VERTEX_ATTRIBUTE_ID)k;
        if (!oldVAO->getMappedBuffer(attrId))
            continue;

        vao->mapVertexAttrBuffer(const_cast<video::IGPUBuffer*>(oldVAO->getMappedBuffer(attrId)),attrId,oldVAO->getAttribComponentCount(attrId),oldVAO->getAttribType(attrId),
                                 oldVAO->getMappedBufferStride(attrId),oldVAO->getMappedBufferOffset(attrId),oldVAO->getAttribDivisor(attrId));
    }

    // I know what attributes are unused in my mesh and I've set up the shader to use thse as instance data
    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR4,ECPA_FOUR,ECT_FLOAT,28*sizeof(float),0,1);
    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR5,ECPA_FOUR,ECT_FLOAT,28*sizeof(float),4*sizeof(float),1);
    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR6,ECPA_FOUR,ECT_FLOAT,28*sizeof(float),8*sizeof(float),1);
    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR2,ECPA_FOUR,ECT_FLOAT,28*sizeof(float),12*sizeof(float),1);

    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR7,ECPA_THREE,ECT_FLOAT,28*sizeof(float),16*sizeof(float),1);
    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR8,ECPA_THREE,ECT_FLOAT,28*sizeof(float),19*sizeof(float),1);
    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR9,ECPA_THREE,ECT_FLOAT,28*sizeof(float),22*sizeof(float),1);
    vao->mapVertexAttrBuffer(instanceDataBuffer,EVAI_ATTR10,ECPA_THREE,ECT_FLOAT,28*sizeof(float),25*sizeof(float),1);


    if (oldVAO->getIndexBuffer())
        vao->mapIndexBuffer(const_cast<video::IGPUBuffer*>(oldVAO->getIndexBuffer()));

    return vao;
 }



void CPUCullingFunc(uint8_t** outputPtrs, const size_t& outputDataStride, const core::aabbox3df& LoDInvariantBBox, const size_t& instanceCount,
                    const core::matrix4x3& AbsoluteTransformation, const uint8_t* instanceData, const size_t& instanceDataStride, scene::ISceneManager* SceneManager, void* userData)
{
    video::IVideoDriver* driver = SceneManager->getVideoDriver();

    core::matrix4x3 ViewWorldMat = concatenateBFollowedByA(driver->getTransform(irr::video::E4X3TS_VIEW),AbsoluteTransformation);
    core::matrix4 ProjViewWorldMat = concatenateBFollowedByA(driver->getTransform(irr::video::EPTS_PROJ_VIEW),AbsoluteTransformation);
    float ViewNormalMat[9];
    ViewWorldMat.getSub3x3InverseTranspose(ViewNormalMat);
    core::vectorSIMDf eyePos;
    eyePos.set(driver->getTransform(video::E4X3TS_VIEW_INVERSE).getTranslation());

    core::vectorSIMDf LoDInvariantBBoxCenter;
    LoDInvariantBBoxCenter.set(LoDInvariantBBox.getCenter());


    for (size_t i=0; i<instanceCount; i++)
    {
        core::matrix4x3 instanceTform = *reinterpret_cast<const core::matrix4x3*>(instanceData+instanceDataStride*i);

        core::vectorSIMDf instancePos;
        instanceTform.transformVect(instancePos.pointer,LoDInvariantBBoxCenter.pointer);
        AbsoluteTransformation.transformVect(instancePos.pointer);

        core::vectorSIMDf eyeToInstance = instancePos-eyePos;
        float distanceToInstanceSQ = dot(eyeToInstance,eyeToInstance).X;

        uint32_t instanceLoD;
        if (distanceToInstanceSQ<instanceLoDDistances[0]*instanceLoDDistances[0])
            instanceLoD = 0;
        else if (distanceToInstanceSQ<instanceLoDDistances[1]*instanceLoDDistances[1])
            instanceLoD = 1;
        else
            continue;

        core::matrix4 instanceWorldViewProjMat = concatenateBFollowedByA(ProjViewWorldMat,instanceTform);

        ///Do frustum Culling
        if (!instanceWorldViewProjMat.isBoxInsideFrustum(LoDInvariantBBox))
            continue;


        *reinterpret_cast<core::matrix4*>(outputPtrs[instanceLoD]) = instanceWorldViewProjMat;
/* OLD EXAMPLE LEFTOVER, just to show normal matrix is still there
        const float* gNormalMat = reinterpret_cast<const float*>(instanceData+instanceDataStride*i+48);
        *reinterpret_cast<core::vector3df*>(outputPtrs[instanceLoD]+64+ 0) = reinterpret_cast<core::vector3df*>(ViewNormalMat)[0]*gNormalMat[0]+reinterpret_cast<core::vector3df*>(ViewNormalMat)[1]*gNormalMat[1]+reinterpret_cast<core::vector3df*>(ViewNormalMat)[2]*gNormalMat[2];
        *reinterpret_cast<core::vector3df*>(outputPtrs[instanceLoD]+64+12) = reinterpret_cast<core::vector3df*>(ViewNormalMat)[0]*gNormalMat[3]+reinterpret_cast<core::vector3df*>(ViewNormalMat)[1]*gNormalMat[4]+reinterpret_cast<core::vector3df*>(ViewNormalMat)[2]*gNormalMat[5];
        *reinterpret_cast<core::vector3df*>(outputPtrs[instanceLoD]+64+24) = reinterpret_cast<core::vector3df*>(ViewNormalMat)[0]*gNormalMat[6]+reinterpret_cast<core::vector3df*>(ViewNormalMat)[1]*gNormalMat[7]+reinterpret_cast<core::vector3df*>(ViewNormalMat)[2]*gNormalMat[8];
*/
        *reinterpret_cast<core::matrix4x3*>(outputPtrs[instanceLoD]+64) = concatenateBFollowedByA(ViewWorldMat,instanceTform);

        outputPtrs[instanceLoD] += outputDataStride;
    }
}

int main()
{
	// create device with full flexibility over creation parameters
	// you can add more parameters if desired, check irr::SIrrlichtCreationParameters
	irr::SIrrlichtCreationParameters params;
	params.Bits = 24; //may have to set to 32bit for some platforms
	params.ZBufferBits = 24; //we'd like 32bit here
    params.AntiAlias = 0; //No AA, yet
	params.DriverType = video::EDT_OPENGL; //! Only Well functioning driver, software renderer left for sake of 2D image drawing
	params.WindowSize = dimension2d<uint32_t>(1280, 720);
	params.Fullscreen = false;
	params.Vsync = true; //! If supported by target platform
	params.Doublebuffer = true;
	params.Stencilbuffer = false; //! This will not even be a choice soon
	IrrlichtDevice* device = createDeviceEx(params);

	if (device == 0)
		return 1; // could not create selected driver.


	video::IVideoDriver* driver = device->getVideoDriver();

    SimpleCallBack* cb = new SimpleCallBack();
    video::E_MATERIAL_TYPE newMaterialType = (video::E_MATERIAL_TYPE)driver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("mesh.vert",
                                                        "","","", //! No Geometry or Tessellation Shaders
                                                        "mesh.frag",
                                                        3,video::EMT_SOLID, //! 3 vertices per primitive (this is tessellation shader relevant only
                                                        cb, //! Our Shader Callback
                                                        0); //! No custom user data
    cb->drop();



	scene::ISceneManager* smgr = device->getSceneManager();
	driver->setTextureCreationFlag(video::ETCF_ALWAYS_32_BIT, true);
	scene::ICameraSceneNode* camera =
		smgr->addCameraSceneNodeFPS(0,100.0f,0.01f);
	camera->setPosition(core::vector3df(-4,0,0));
	camera->setTarget(core::vector3df(0,0,0));
	camera->setNearValue(0.01f);
	camera->setFarValue(100.0f);
    smgr->setActiveCamera(camera);
	device->getCursorControl()->setVisible(false);
	MyEventReceiver receiver;
	device->setEventReceiver(&receiver);

	//! Test Loading of Obj
    scene::ICPUMesh* cpumesh = smgr->getMesh("../media/cow.obj");
    scene::ICPUMesh* cpumesh2 = smgr->getMesh("../media/yellowflower.obj");
    if (!cpumesh||!cpumesh2)
        return 0;

    scene::IGPUMesh* gpumesh = driver->createGPUMeshFromCPU(dynamic_cast<scene::SCPUMesh*>(cpumesh));
    scene::IGPUMesh* gpumesh2 = driver->createGPUMeshFromCPU(dynamic_cast<scene::SCPUMesh*>(cpumesh2));
    smgr->getMeshCache()->removeMesh(cpumesh);
    smgr->getMeshCache()->removeMesh(cpumesh2);
    for (size_t i=0; i<gpumesh->getMeshBufferCount(); i++)
        gpumesh->getMeshBuffer(i)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)newMaterialType;
    for (size_t i=0; i<gpumesh2->getMeshBufferCount(); i++)
        gpumesh2->getMeshBuffer(i)->getMaterial().MaterialType = (video::E_MATERIAL_TYPE)newMaterialType;


    video::SMaterial cullingXFormFeedbackShader;
    const char* xformFeedbackOutputs[] =
    {
        "outLoD0_worldViewProjMatCol0",
        "outLoD0_worldViewProjMatCol1",
        "outLoD0_worldViewProjMatCol2",
        "outLoD0_worldViewProjMatCol3",
        "outLoD0_worldViewMatCol0",
        "outLoD0_worldViewMatCol1",
        "outLoD0_worldViewMatCol2",
        "outLoD0_worldViewMatCol3",
        "gl_NextBuffer",
        "outLoD1_worldViewProjMatCol0",
        "outLoD1_worldViewProjMatCol1",
        "outLoD1_worldViewProjMatCol2",
        "outLoD1_worldViewProjMatCol3",
        "outLoD1_worldViewMatCol0",
        "outLoD1_worldViewMatCol1",
        "outLoD1_worldViewMatCol2",
        "outLoD1_worldViewMatCol3"
    };
    cullingXFormFeedbackShader.MaterialType = (video::E_MATERIAL_TYPE)driver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("culling.vert","","","culling.geom","",3,video::EMT_SOLID,cb,xformFeedbackOutputs,17);
    cullingXFormFeedbackShader.RasterizerDiscard = true;


    //! The inside of the loop resets and recreates the instancedNode and instances many times to stress-test for GPU-Memory leaks

	uint64_t lastFPSTime = 0;
/*
	while(device->run())
	//if (device->isWindowActive())
	{
		driver->beginScene(true, true, video::SColor(255,0,0,255) );

        IMeshSceneNodeInstanced* node = smgr->addMeshSceneNodeInstanced(smgr->getRootSceneNode());
        node->setBBoxUpdateEnabled();
        node->setAutomaticCulling(scene::EAC_FRUSTUM_BOX);
        {
            std::vector<scene::IMeshSceneNodeInstanced::MeshLoD> LevelsOfDetail;
            LevelsOfDetail.resize(2);
            LevelsOfDetail[0].mesh = gpumesh;
            LevelsOfDetail[0].lodDistance = instanceLoDDistances[0];
            LevelsOfDetail[1].mesh = gpumesh2;
            LevelsOfDetail[1].lodDistance = instanceLoDDistances[1];

            node->setLoDMeshes(LevelsOfDetail,37*sizeof(float),cullingXFormFeedbackShader,vaoSetupOverride,NULL,0,CPUCullingFunc);
            cb->instanceLoDInvariantBBox = node->getLoDInvariantBBox();
        }

        //! Special Juice for INSTANCING
        for (size_t z=0; z<kNumHardwareInstancesZ; z++)
        for (size_t y=0; y<kNumHardwareInstancesY; y++)
        for (size_t x=0; x<kNumHardwareInstancesX; x++)
        {
            core::matrix4x3 mat;
            mat.setTranslation(core::vector3df(x,y,z)*2.f);
            node->addInstance(mat);
        }

        srand(6945);

        bool alreadyKilled[kHardwareInstancesTOTAL];
        memset(alreadyKilled,0,kHardwareInstancesTOTAL*sizeof(bool));
        uint32_t* instancesToRemove = new uint32_t[kHardwareInstancesTOTAL];
        size_t j=0;
        for (size_t i=0; i<600; i++)
        {
            uint32_t instanceID = rand()%kHardwareInstancesTOTAL;
            if (alreadyKilled[instanceID])
                continue;

            instancesToRemove[j++] = instanceID;
            alreadyKilled[instanceID] = true;
        }
        node->removeInstances(j,instancesToRemove);

        //! This animates (moves) the camera and sets the transforms
        //! Also draws the meshbuffer
        smgr->drawAll();

        j=0;
        for (size_t i=0; i<kHardwareInstancesTOTAL; i++)
        {
            if (alreadyKilled[i])
                continue;

            instancesToRemove[j++] = i;
            alreadyKilled[i] = true;
        }
        node->removeInstances(j,instancesToRemove);
        delete [] instancesToRemove;
        node->remove();

		driver->endScene();

		// display frames per second in window title
		uint64_t time = device->getTimer()->getRealTime();
		if (time-lastFPSTime > 1000)
		{
			stringw str = L"Builtin Nodes Demo - Irrlicht Engine [";
			str += driver->getName();
			str += "] FPS:";
			str += driver->getFPS();
			str += " PrimitvesDrawn:";
			str += driver->getPrimitiveCountDrawn();

			device->setWindowCaption(str.c_str());
			lastFPSTime = time;
		}
	}
	*/

        IMeshSceneNodeInstanced* node = smgr->addMeshSceneNodeInstanced(smgr->getRootSceneNode());
        node->setBBoxUpdateEnabled();
        node->setAutomaticCulling(scene::EAC_FRUSTUM_BOX);
        {
            std::vector<scene::IMeshSceneNodeInstanced::MeshLoD> LevelsOfDetail;
            LevelsOfDetail.resize(2);
            LevelsOfDetail[0].mesh = gpumesh;
            LevelsOfDetail[0].lodDistance = instanceLoDDistances[0];
            LevelsOfDetail[1].mesh = gpumesh2;
            LevelsOfDetail[1].lodDistance = instanceLoDDistances[1];

            assert(node->setLoDMeshes(LevelsOfDetail,28*sizeof(float),cullingXFormFeedbackShader,vaoSetupOverride,2,NULL,0,CPUCullingFunc));
            node->setGPUCullingThresholdMultiplier(0.25f);
            cb->instanceLoDInvariantBBox = node->getLoDInvariantBBox();
        }

        //! Special Juice for INSTANCING
        for (size_t z=0; z<kNumHardwareInstancesZ; z++)
        for (size_t y=0; y<kNumHardwareInstancesY; y++)
        for (size_t x=0; x<kNumHardwareInstancesX; x++)
        {
            core::matrix4x3 mat;
            mat.setTranslation(core::vector3df(x,y,z)*2.f);
            node->addInstance(mat);
        }

        srand(6945);

        bool alreadyKilled[kHardwareInstancesTOTAL];
        memset(alreadyKilled,0,kHardwareInstancesTOTAL*sizeof(bool));
        uint32_t* instancesToRemove = new uint32_t[kHardwareInstancesTOTAL];
        size_t j=0;
        for (size_t i=0; i<600; i++)
        {
            uint32_t instanceID = rand()%kHardwareInstancesTOTAL;
            if (alreadyKilled[instanceID])
                continue;

            instancesToRemove[j++] = instanceID;
            alreadyKilled[instanceID] = true;
        }
        node->removeInstances(j,instancesToRemove);


        j=0;
        for (size_t i=0; i<kHardwareInstancesTOTAL; i++)
        {
            if (alreadyKilled[i])
                continue;

            instancesToRemove[j++] = i;
            alreadyKilled[i] = true;
        }

	while(device->run()&&(!quit))
	{
		driver->beginScene(true, true, video::SColor(255,0,0,255) );

        //! This animates (moves) the camera and sets the transforms
        //! Also draws the meshbuffer
        smgr->drawAll();

		driver->endScene();

		// display frames per second in window title
		uint64_t time = device->getTimer()->getRealTime();
		if (time-lastFPSTime > 1000)
		{
			std::wostringstream str;
			str << L"Builtin Nodes Demo - Irrlicht Engine [" << driver->getName() << "] FPS:" << driver->getFPS() << " PrimitvesDrawn:" << driver->getPrimitiveCountDrawn();

			device->setWindowCaption(str.str());
			lastFPSTime = time;
		}
	}

        node->removeInstances(j,instancesToRemove);
        delete [] instancesToRemove;
        node->remove();

    gpumesh->drop();
    gpumesh2->drop();
	device->drop();

	return 0;
}
