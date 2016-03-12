/* GCC compile Flags
-flto
-fuse-linker-plugin
-fno-omit-frame-pointer //for debug
-msse3
-mfpmath=sse
-ggdb3 //for debug
*/
/* Linker Flags
-lIrrlicht
-lXrandr
-lGL
-lX11
-lpthread
-ldl

-fuse-ld=gold
-flto
-fuse-linker-plugin
-msse3
*/
#include <irrlicht.h>
#include "driverChoice.h"

/**
This example shows how to:
1) Set up and Use a Simple Shader
2) render triangle buffers to screen in all the different ways
**/
using namespace irr;
using namespace core;


/*
The start of the main function starts like in most other example. We ask the
user for the desired renderer and start it up.
*/
int main()
{
	// create device with full flexibility over creation parameters
	// you can add more parameters if desired, check irr::SIrrlichtCreationParameters
	irr::SIrrlichtCreationParameters params;
	params.Bits = 24; //may have to set to 32bit for some platforms
	params.ZBufferBits = 24; //we'd like 32bit here
    params.AntiAlias = 0; //No AA, yet
	params.DriverType = video::EDT_OPENGL; //! Only Well functioning driver, software renderer left for sake of 2D image drawing
	params.WindowSize = dimension2d<u32>(1920, 1080);
	params.Fullscreen = false;
	params.Vsync = true; //! If supported by target platform
	params.Doublebuffer = true;
	params.Stencilbuffer = false; //! This will not even be a choice soon
	IrrlichtDevice* device = createDeviceEx(params);

	if (device == 0)
		return 1; // could not create selected driver.


	video::IVideoDriver* driver = device->getVideoDriver();

    //! First need to make a material other than default to be able to draw with custom shader
    video::SMaterial material;
    //material.BackfaceCulling = false; //! Triangles will be visible from both sides
    material.MaterialType = (video::E_MATERIAL_TYPE)driver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("../points.vert",
                                                        "","","", //! No Geometry or Tessellation Shaders
                                                        "../points.frag",
                                                        3,video::EMT_SOLID, //! 3 vertices per primitive (this is tessellation shader relevant only
                                                        NULL, //! No Shader Callback (we dont have any constants/uniforms to pass to the shader)
                                                        0); //! No custom user data



	scene::ISceneManager* smgr = device->getSceneManager();


    scene::IGPUMeshBuffer* mb = new scene::IGPUMeshBuffer();
    scene::IGPUMeshDataFormatDesc* desc = driver->createGPUMeshDataFormatDesc();
    mb->setMeshDataAndFormat(desc);
    desc->drop();

    size_t xComps = 0x1u<<9;
    size_t yComps = 0x1u<<9;
    size_t zComps = 0x1u<<9;
    size_t verts = xComps*yComps*zComps;
    size_t bufSize = verts;
    bufSize *= 4;
    uint32_t* mem = (uint32_t*)malloc(bufSize);
    for (size_t i=0; i<xComps; i++)
    for (size_t j=0; j<yComps; j++)
    for (size_t k=0; k<zComps; k++)
    {
        mem[i+xComps*(j+yComps*k)] = (i<<20)|(j<<10)|(k);
    }
    video::IGPUBuffer* positionBuf = driver->createGPUBuffer(bufSize,mem);
    free(mem);


    //! By mapping we increase/grab() ref counter of positionBuf, any previously mapped buffer will have it's reference dropped
    desc->mapVertexAttrBuffer(positionBuf,
                            scene::EVAI_ATTR0, //! we use first attribute slot (out of a minimum of 16)
                            scene::ECPA_FOUR, //! there are 3 components per vertex
                            scene::ECT_INT_2_10_10_10_REV); //! and they are floats

    /** Since we mapped the buffer, the MeshBuffers will be using it.
        If we drop it, it will be automatically deleted when MeshBuffers are done using it.
    **/
    positionBuf->drop();


    mb->setIndexCount(verts);
    mb->setPrimitiveType(scene::EPT_POINTS);

    scene::ICameraSceneNode* camera = smgr->addCameraSceneNodeFPS(0,80.f,0.001f);
    smgr->setActiveCamera(camera);
    camera->setNearValue(0.001f);
    camera->setFarValue(10.f);

	uint64_t lastFPSTime = 0;

	while(device->run())
	if (device->isWindowActive())
	{
		driver->beginScene(true, true, video::SColor(255,0,0,255) );

        smgr->drawAll();

        driver->setTransform(video::ETS_WORLD,core::matrix4());
        driver->setMaterial(material);
        //! draw back to front
        driver->drawMeshBuffer(mb);

		driver->endScene();

		// display frames per second in window title
		uint64_t time = device->getTimer()->getRealTime();
		if (time-lastFPSTime > 1000)
		{
			stringw str = L"Terrain Renderer - Irrlicht Engine [";
			str += driver->getName();
			str += "] FPS:";
			str += driver->getFPS();
			str += " PrimitvesDrawn:";
			str += driver->getPrimitiveCountDrawn();

			device->setWindowCaption(str.c_str());
			lastFPSTime = time;
		}
	}
	mb->drop();

	device->drop();

	return 0;
}