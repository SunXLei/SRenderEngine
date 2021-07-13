#pragma once

#include "../RenderPass.h"
#include "./graphics/Scene.h"
#include "./platform/opengl/FrameBuffer.h"
#include "./graphics/Shader.h"

namespace sre
{
	class FXAAPass : public RenderPass
	{
	public:
		FXAAPass(Scene* scene);
		~FXAAPass();

		PostProcessOutput Render(LightingPassOutput dlightInput);

	private:
		Shader* mFXAAShader;
		FrameBuffer* mFXAAFBO;
	};
}
