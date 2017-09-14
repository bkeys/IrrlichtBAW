cmake_minimum_required(VERSION 3.0.0)
project(IrrlichtBAW VERSION 0.0.0)

include(ExternalProject)

set(CMAKE_MODULE_PATH
        ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/CMake
        ${CMAKE_SOURCE_DIR}/CMake/Dependencies
        ${CMAKE_SOURCE_DIR}/examples_test
)

find_package(OpenGL REQUIRED)
include(DependencyBzip2)
include(DependencyLibJpeg)
include(DependencyLibPng)
include(DependencyZlib)

# Make an option to not build examples
include(Examples)

set(SOURCE_FILES
source/Irrlicht/CAnimatedMeshSceneNode.cpp
source/Irrlicht/CBillboardSceneNode.cpp
source/Irrlicht/CCSMLoader.cpp
source/Irrlicht/CCameraSceneNode.cpp
source/Irrlicht/CColorConverter.cpp
source/Irrlicht/CCubeSceneNode.cpp
source/Irrlicht/CDMFLoader.cpp
source/Irrlicht/CDefaultSceneNodeAnimatorFactory.cpp
source/Irrlicht/CDefaultSceneNodeFactory.cpp
source/Irrlicht/CDepthBuffer.cpp
source/Irrlicht/CEmptySceneNode.cpp
source/Irrlicht/CFPSCounter.cpp
source/Irrlicht/CFileList.cpp
source/Irrlicht/CFileSystem.cpp
source/Irrlicht/CGPUTransientBuffer.cpp
source/Irrlicht/CGeometryCreator.cpp
source/Irrlicht/CImage.cpp
source/Irrlicht/CImageLoaderBMP.cpp
source/Irrlicht/CImageLoaderDDS.cpp
source/Irrlicht/CImageLoaderJPG.cpp
source/Irrlicht/CImageLoaderPCX.cpp
source/Irrlicht/CImageLoaderPNG.cpp
source/Irrlicht/CImageLoaderPPM.cpp
source/Irrlicht/CImageLoaderPSD.cpp
source/Irrlicht/CImageLoaderRGB.cpp
source/Irrlicht/CImageLoaderTGA.cpp
source/Irrlicht/CImageLoaderWAL.cpp
source/Irrlicht/CImageWriterBMP.cpp
source/Irrlicht/CImageWriterJPG.cpp
source/Irrlicht/CImageWriterPCX.cpp
source/Irrlicht/CImageWriterPNG.cpp
source/Irrlicht/CImageWriterPPM.cpp
source/Irrlicht/CImageWriterPSD.cpp
source/Irrlicht/CImageWriterTGA.cpp
source/Irrlicht/CIrrDeviceConsole.cpp
source/Irrlicht/CIrrDeviceLinux.cpp
source/Irrlicht/CIrrDeviceSDL.cpp
source/Irrlicht/CIrrDeviceStub.cpp
source/Irrlicht/CIrrDeviceWin32.cpp
source/Irrlicht/CLimitReadFile.cpp
source/Irrlicht/CLogger.cpp
source/Irrlicht/CMemoryFile.cpp
source/Irrlicht/CMeshCache.cpp
source/Irrlicht/CMeshManipulator.cpp
source/Irrlicht/CMeshSceneNode.cpp
source/Irrlicht/CMeshSceneNodeInstanced.cpp
source/Irrlicht/CMountPointReader.cpp
source/Irrlicht/CNPKReader.cpp
source/Irrlicht/CNullDriver.cpp
source/Irrlicht/COBJMeshFileLoader.cpp
source/Irrlicht/COBJMeshWriter.cpp
source/Irrlicht/COCTLoader.cpp
source/Irrlicht/COSOperator.cpp
source/Irrlicht/COpenCLHandler.cpp
source/Irrlicht/COpenGL3DTexture.cpp
source/Irrlicht/COpenGLDriver.cpp
source/Irrlicht/COpenGLExtensionHandler.cpp
source/Irrlicht/COpenGLFrameBuffer.cpp
source/Irrlicht/COpenGLOcclusionQuery.cpp
source/Irrlicht/COpenGLPersistentlyMappedBuffer.cpp
source/Irrlicht/COpenGLQuery.cpp
source/Irrlicht/COpenGLRenderBuffer.cpp
source/Irrlicht/COpenGLSLMaterialRenderer.cpp
source/Irrlicht/COpenGLTexture.cpp
source/Irrlicht/COpenGLTransformFeedback.cpp
source/Irrlicht/COpenGLVAO.cpp
source/Irrlicht/CPLYMeshWriter.cpp
source/Irrlicht/CPakReader.cpp
source/Irrlicht/CReadFile.cpp
source/Irrlicht/CSTLMeshWriter.cpp
source/Irrlicht/CSTLMeshFileLoader.cpp
source/Irrlicht/CBurningShader_Raster_Reference.cpp
source/Irrlicht/CSceneManager.cpp
source/Irrlicht/CSceneNodeAnimatorCameraFPS.cpp
source/Irrlicht/CSceneNodeAnimatorCameraMaya.cpp
source/Irrlicht/CSceneNodeAnimatorDelete.cpp
source/Irrlicht/CSceneNodeAnimatorFlyCircle.cpp
source/Irrlicht/CSceneNodeAnimatorFlyStraight.cpp
source/Irrlicht/CSceneNodeAnimatorFollowSpline.cpp
source/Irrlicht/CSceneNodeAnimatorRotation.cpp
source/Irrlicht/CSceneNodeAnimatorTexture.cpp
source/Irrlicht/CSkinnedMesh.cpp
source/Irrlicht/CSkinnedMeshSceneNode.cpp
source/Irrlicht/CSkyBoxSceneNode.cpp
source/Irrlicht/CSkyDomeSceneNode.cpp
source/Irrlicht/CSoftwareDriver.cpp
source/Irrlicht/CSoftwareDriver2.cpp
source/Irrlicht/CSoftwareTexture.cpp
source/Irrlicht/CSoftwareTexture2.cpp
source/Irrlicht/CSphereSceneNode.cpp
source/Irrlicht/CTRFlat.cpp
source/Irrlicht/CTRFlatWire.cpp
source/Irrlicht/CTRGouraud.cpp
source/Irrlicht/CTRGouraud2.cpp
source/Irrlicht/CTRGouraudAlpha2.cpp
source/Irrlicht/CTRGouraudAlphaNoZ2.cpp
source/Irrlicht/CTRGouraudWire.cpp
source/Irrlicht/CTRNormalMap.cpp
source/Irrlicht/CTRStencilShadow.cpp
source/Irrlicht/CTRTextureBlend.cpp
source/Irrlicht/CTRTextureDetailMap2.cpp
source/Irrlicht/CTRTextureFlat.cpp
source/Irrlicht/CTRTextureFlatWire.cpp
source/Irrlicht/CTRTextureGouraud.cpp
source/Irrlicht/CTRTextureGouraud2.cpp
source/Irrlicht/CTRTextureGouraudAdd.cpp
source/Irrlicht/CTRTextureGouraudAdd2.cpp
source/Irrlicht/CTRTextureGouraudAddNoZ2.cpp
source/Irrlicht/CTRTextureGouraudAlpha.cpp
source/Irrlicht/CTRTextureGouraudAlphaNoZ.cpp
source/Irrlicht/CTRTextureGouraudNoZ.cpp
source/Irrlicht/CTRTextureGouraudNoZ2.cpp
source/Irrlicht/CTRTextureGouraudVertexAlpha2.cpp
source/Irrlicht/CTRTextureGouraudWire.cpp
source/Irrlicht/CTRTextureLightMap2_Add.cpp
source/Irrlicht/CTRTextureLightMap2_M1.cpp
source/Irrlicht/CTRTextureLightMap2_M2.cpp
source/Irrlicht/CTRTextureLightMap2_M4.cpp
source/Irrlicht/CTRTextureLightMapGouraud2_M4.cpp
source/Irrlicht/CTRTextureWire2.cpp
source/Irrlicht/CTarReader.cpp
source/Irrlicht/CVideoModeList.cpp
source/Irrlicht/CWADReader.cpp
source/Irrlicht/CWriteFile.cpp
source/Irrlicht/CXMeshFileLoader.cpp
source/Irrlicht/CZBuffer.cpp
source/Irrlicht/CZipReader.cpp
source/Irrlicht/FW_Mutex.cpp
source/Irrlicht/IBurningShader.cpp
source/Irrlicht/Irrlicht.cpp
source/Irrlicht/STextureSamplingParams.cpp
source/Irrlicht/aesGladman/aescrypt.cpp
source/Irrlicht/aesGladman/aeskey.cpp
source/Irrlicht/aesGladman/aestab.cpp
source/Irrlicht/aesGladman/fileenc.cpp
source/Irrlicht/aesGladman/hmac.cpp
source/Irrlicht/aesGladman/prng.cpp
source/Irrlicht/aesGladman/pwd2key.cpp
source/Irrlicht/aesGladman/sha1.cpp
source/Irrlicht/aesGladman/sha2.cpp
#source/Irrlicht/bzip2/blocksort
#source/Irrlicht/bzip2/bzcompress
#source/Irrlicht/bzip2/bzlib
#source/Irrlicht/bzip2/crctable
#source/Irrlicht/bzip2/decompress
#source/Irrlicht/bzip2/huffman
#source/Irrlicht/bzip2/randtable
source/Irrlicht/convert_utf/ConvertUTF
source/Irrlicht/coreutil.cpp
source/Irrlicht/lzma/LzmaDec
source/Irrlicht/os.cpp
)

include_directories(
  SYSTEM ${CMAKE_SOURCE_DIR}/include
  SYSTEM ${CMAKE_SOURCE_DIR}/source/Irrlicht/utf8/source
  SYSTEM ${CMAKE_SOURCE_DIR}/source/Irrlicht/convert_utf
)

set(CMAKE_CXX_FLAGS "-Wextra -Wall -g -W -Wno-unused-parameter -fno-omit-frame-pointer -fno-exceptions -fuse-ld=gold -msse3 -ggdb3 -std=c++03 -fstack-protector-strong -D_IRR_STATIC_LIB_ -D_DEBUG -fuse-ld=gold -fstack-protector-strong -lGL -D_IRR_COMPILE_WITH_OPENGL_")
add_library(IrrlichtBAW STATIC ${SOURCE_FILES})
target_link_libraries(IrrlichtBAW ${IRRBAW_DEPENDENCY_LIBRARIES} ${OPENGL_LIBRARIES} unwind Xrandr Xxf86vm X11 pthread unwind-x86_64)
add_dependencies(IrrlichtBAW libjpeg libpng bzip2 zlib)