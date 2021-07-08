#pragma once

#include "./glad/glad.h"
#include "./graphics/texture/Texture.h"

namespace sre
{
	// TODO: this framebuffer structure may need to change, i.e. the add attachment functions are not convinent now
	class FrameBuffer
	{
	public:
		FrameBuffer(int width, int height, bool isMultiSample = false);
		virtual ~FrameBuffer();

		void CreateFrameBuffer();
		void AddColorTexture(GLenum textureFormat, GLenum dataFormat, GLenum dataType, GLenum attachType);
		void AddDepthStencilTexture(GLenum textureFormat, GLenum dataFormat, GLenum dataType, GLenum attachType);
		void AddDepthStencilRBO(GLenum rboFormat);

		void Clear();
		void Bind();
		void UnBind();

		// getters
		inline int GetWidth() { return mWidth; }
		inline int GetHeight() { return mHeight; }

		inline unsigned int GetFramebuffer() { return mFBO; }
		inline unsigned int GetDepthStencilRBO() { return mDepthStencilRBO; }
		inline Texture* GetColourTexture() { return &mColorTexture; }
		inline Texture* GetDepthStencilTexture() { return &mDepthStencilTexture; }

	private:
		unsigned int mFBO;
		int mWidth, mHeight;
		bool mIsMultiSample;


		Texture mColorTexture;
		Texture mDepthStencilTexture;
		unsigned int mDepthStencilRBO;
		bool mIsUseRBO;
	};

}