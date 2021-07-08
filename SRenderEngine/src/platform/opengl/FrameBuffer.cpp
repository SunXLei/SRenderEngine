#include "./FrameBuffer.h"

#include <iostream>



namespace sre
{
	FrameBuffer::FrameBuffer(int width, int height, bool isMultiSample):
		mWidth(width),mHeight(height),mIsMultiSample(isMultiSample)
	{
		mIsUseRBO = false;
		glGenFramebuffers(1, &mFBO);
	}

	FrameBuffer::~FrameBuffer()
	{
		glDeleteFramebuffers(1, &mFBO);
		if (mIsUseRBO)
			glDeleteRenderbuffers(1, &mDepthStencilRBO);
	}

	void FrameBuffer::CreateFrameBuffer()
	{
		Bind();
		if (!mColorTexture.IsGenerated()) 
		{
			// indicate that there won't be a colour buffer for this FBO
			glDrawBuffer(GL_NONE);
			glReadBuffer(GL_NONE);
		}

		// check if the creation failed
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
		{
			std::cerr << "CREATE FRAMEBUFFER FAILED!\n";
			return;
		}
		UnBind();

	}

	void FrameBuffer::AddColorTexture(GLenum textureFormat, GLenum dataFormat, GLenum dataType, GLenum attachType)
	{
		// bind framebuffer first
		Bind();

		// create the color texture with settings and attach it to framebuffer
		TextureSettings colorTextureSettings;
		colorTextureSettings.TextureFormat = textureFormat;
		colorTextureSettings.TextureWrapSMode = GL_CLAMP_TO_EDGE;
		colorTextureSettings.TextureWrapTMode = GL_CLAMP_TO_EDGE;
		colorTextureSettings.TextureMinificationFilterMode = GL_LINEAR;
		colorTextureSettings.TextureMagnificationFilterMode = GL_LINEAR;
		colorTextureSettings.HasMips = false;

		mColorTexture.SetTextureSettings(colorTextureSettings);
		mColorTexture.Generate2DTexture(mWidth, mHeight, dataFormat, dataType);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachType, GL_TEXTURE_2D, mColorTexture.GetTextureId(), 0);
	}

	void FrameBuffer::AddDepthStencilTexture(GLenum textureFormat, GLenum dataFormat, GLenum dataType, GLenum attachType)
	{
		// bind framebuffer first
		Bind();

		// create the depth/stencil texture with settings and attach it to framebuffer
		TextureSettings depthStencilSettings;
		depthStencilSettings.TextureFormat = textureFormat;
		depthStencilSettings.TextureWrapSMode = GL_CLAMP_TO_BORDER;
		depthStencilSettings.TextureWrapTMode = GL_CLAMP_TO_BORDER;
		depthStencilSettings.TextureMinificationFilterMode = GL_NEAREST;
		depthStencilSettings.TextureMagnificationFilterMode = GL_NEAREST;
		depthStencilSettings.HasBorder = true;
		depthStencilSettings.HasMips = false;
		mDepthStencilTexture.SetTextureSettings(depthStencilSettings);
		mDepthStencilTexture.Generate2DTexture(mWidth, mHeight, dataFormat, dataType);
		glFramebufferTexture2D(GL_FRAMEBUFFER, attachType, GL_TEXTURE_2D, mDepthStencilTexture.GetTextureId(), 0);

	}

	void FrameBuffer::AddDepthStencilRBO(GLenum rboFormat)
	{

	}

	void FrameBuffer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}

	void FrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
	}

	void FrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}
}