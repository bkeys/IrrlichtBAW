// Copyright (C) 2002-2012 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __C_VIDEO_SOFTWARE_H_INCLUDED__
#define __C_VIDEO_SOFTWARE_H_INCLUDED__

#include "IrrCompileConfig.h"
#include "CNullDriver.h"

#ifdef _IRR_COMPILE_WITH_SOFTWARE_
#include "ITriangleRenderer.h"
#include "SViewFrustum.h"
#include "CImage.h"

namespace irr
{
namespace video
{
	class CSoftwareDriver : public CNullDriver
	{
	public:

		//! constructor
		CSoftwareDriver(const core::dimension2d<uint32_t>& windowSize, bool fullscreen, io::IFileSystem* io, video::IImagePresenter* presenter);

		//! destructor
		virtual ~CSoftwareDriver();

		//! queries the features of the driver, returns true if feature is available
		virtual bool queryFeature(E_VIDEO_DRIVER_FEATURE feature) const;

		//! sets a material
		virtual void setMaterial(const SMaterial& material);

		virtual bool setRenderTarget(video::ITexture* texture, bool clearBackBuffer,
						bool clearZBuffer, SColor color);

		//! sets a viewport
		virtual void setViewPort(const core::rect<int32_t>& area);

		//! clears the zbuffer
		virtual bool beginScene(bool backBuffer=true, bool zBuffer=true,
				SColor color=SColor(255,0,0,0),
				const SExposedVideoData& videoData=SExposedVideoData(),
				core::rect<int32_t>* sourceRect=0);

		//! presents the rendered scene on the screen, returns false if failed
		virtual bool endScene();

		//! Only used by the internal engine. Used to notify the driver that
		//! the window was resized.
		virtual void OnResize(const core::dimension2d<uint32_t>& size);

		//! returns size of the current render target
		virtual const core::dimension2d<uint32_t>& getCurrentRenderTargetSize() const;

		//! draws a vertex primitive list
		void drawVertexPrimitiveList(const void* vertices, uint32_t vertexCount,
				const void* indexList, uint32_t primitiveCount,
				E_VERTEX_TYPE vType, scene::E_PRIMITIVE_TYPE pType, E_INDEX_TYPE iType);

		//! Draws a 3d line.
		virtual void draw3DLine(const core::vector3df& start,
			const core::vector3df& end, SColor color = SColor(255,255,255,255));

		//! draws an 2d image, using a color (if color is other then Color(255,255,255,255)) and the alpha channel of the texture if wanted.
		virtual void draw2DImage(const video::ITexture* texture, const core::position2d<int32_t>& destPos,
			const core::rect<int32_t>& sourceRect, const core::rect<int32_t>* clipRect = 0,
			SColor color=SColor(255,255,255,255), bool useAlphaChannelOfTexture=false);

		//! draw an 2d rectangle
		virtual void draw2DRectangle(SColor color, const core::rect<int32_t>& pos,
			const core::rect<int32_t>* clip = 0);

		//!Draws an 2d rectangle with a gradient.
		virtual void draw2DRectangle(const core::rect<int32_t>& pos,
			SColor colorLeftUp, SColor colorRightUp, SColor colorLeftDown, SColor colorRightDown,
			const core::rect<int32_t>* clip = 0);

		//! Draws a 2d line.
		virtual void draw2DLine(const core::position2d<int32_t>& start,
								const core::position2d<int32_t>& end,
								SColor color=SColor(255,255,255,255));

		//! Draws a single pixel
		virtual void drawPixel(uint32_t x, uint32_t y, const SColor & color);

		//! \return Returns the name of the video driver. Example: In case of the Direct3D8
		//! driver, it would return "Direct3D8.1".
		virtual const wchar_t* getName() const;

		//! Returns type of video driver
		virtual E_DRIVER_TYPE getDriverType() const;

		//! get color format of the current color buffer
		virtual ECOLOR_FORMAT getColorFormat() const;

		//! returns a device dependent texture from a software surface (IImage)
		//! THIS METHOD HAS TO BE OVERRIDDEN BY DERIVED DRIVERS WITH OWN TEXTURES
		virtual video::ITexture* createDeviceDependentTexture(IImage* surface, const io::path& name, void* mipmapData=0);

		//! Creates a render target texture.
		virtual ITexture* addRenderTargetTexture(const core::dimension2d<uint32_t>& size,
				const io::path& name, const ECOLOR_FORMAT format = ECF_UNKNOWN);

		//! Clears the ZBuffer.
		virtual void clearZBuffer();

		//! Returns the maximum amount of primitives (mostly vertices) which
		//! the device is able to render with one drawIndexedTriangleList
		//! call.
		virtual uint32_t getMaximalIndicesCount() const;

	protected:

		//! sets a render target
		void setRenderTarget(video::CImage* image);

		//! sets the current Texture
		bool setActiveTexture(uint32_t stage, video::ITexture* texture);

		//! switches to a triangle renderer
		void switchToTriangleRenderer(ETriangleRenderer renderer);

		//! void selects the right triangle renderer based on the render states.
		void selectRightTriangleRenderer();

		//! clips a triangle agains the viewing frustum
		void clipTriangle(float* transformedPos);


		//! draws a vertex primitive list
		void drawVertexPrimitiveList16(const void* vertices, uint32_t vertexCount,
				const uint16_t* indexList, uint32_t primitiveCount,
				E_VERTEX_TYPE vType, scene::E_PRIMITIVE_TYPE pType);

		template<class VERTEXTYPE>
		void drawClippedIndexedTriangleListT(const VERTEXTYPE* vertices,
			int32_t vertexCount, const uint16_t* indexList, int32_t triangleCount);

		video::CImage* BackBuffer;
		video::IImagePresenter* Presenter;
		void* WindowId;
		core::rect<int32_t>* SceneSourceRect;

		core::array<S2DVertex> TransformedPoints;

		video::ITexture* RenderTargetTexture;
		video::CImage* RenderTargetSurface;
		core::position2d<int32_t> Render2DTranslation;
		core::dimension2d<uint32_t> RenderTargetSize;
		core::dimension2d<uint32_t> ViewPortSize;


		ITriangleRenderer* CurrentTriangleRenderer;
		ITriangleRenderer* TriangleRenderers[ETR_COUNT];
		ETriangleRenderer CurrentRenderer;

		IZBuffer* ZBuffer;

		video::ITexture* Texture;

		SMaterial Material;
	};

} // end namespace video
} // end namespace irr
#endif // _IRR_COMPILE_WITH_SOFTWARE_

#endif

