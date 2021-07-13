#pragma once

#include "../RenderPass.h"
#include "./graphics/Scene.h"
#include "./platform/opengl/FrameBuffer.h"
#include "./graphics/Shader.h"

namespace sre
{
	class SSRPass : public RenderPass
	{
	public:
		SSRPass(Scene* scene);
		~SSRPass();

		SSRPassOutput Render(GeometryPassOutput gInput, LightingPassOutput dlightInput);

	private:
		Shader* mSSRShader;
		FrameBuffer* mSSRFBO;
		
		bool mEnabled = true;
	};
}