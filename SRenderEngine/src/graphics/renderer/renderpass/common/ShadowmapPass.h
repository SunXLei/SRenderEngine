#pragma once

#include "./glm/glm.hpp"
#include "./graphics/renderer/renderpass/RenderPass.h"
#include "./graphics/Scene.h"
#include "./graphics/Shader.h"
#include "./platform/opengl/FrameBuffer.h"

namespace sre
{
	struct ShadowmapPassOutput 
	{
		glm::mat4 lightSpaceMatrix;
		FrameBuffer* shadowmapFramebuffer;
	};

	class ShadowmapPass: public RenderPass
	{
	public:
		ShadowmapPass(Scene* scene);
		virtual ~ShadowmapPass() override;

		ShadowmapPassOutput Render();

	private:
		FrameBuffer* mShadowmapFB;
		Shader* mShadowmapGenShader;


	};
}