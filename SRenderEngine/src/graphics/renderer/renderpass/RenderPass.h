#pragma once

#include "./graphics/texture/Texture.h"
#include "./platform/opengl/GBuffer.h"
#include "./graphics/Scene.h"

namespace sre
{ 
	struct ShadowmapPassOutput
	{
		glm::mat4 lightSpaceMatrix;
		FrameBuffer* shadowmapFramebuffer;
	};

	struct GeometryPassOutput
	{
		GBuffer* outputGBuffer;
	};

	struct LightingPassOutput
	{
		FrameBuffer* outputGBuffer;
	};

	// for now, the RenderPass class is a little bit dumb
	class RenderPass
	{
	public:
		RenderPass(Scene *scene);
		virtual ~RenderPass();

		void DisplayTexture(int startx, int starty, int width, int height, Texture* texture,int displayChannel = 4, int unit = 9);
		bool DetectWindowSizeChange(int framebufferWidth, int framebufferHeight);

	protected:
		Scene* mScene;
		Shader* mDebugShader;
	};
}