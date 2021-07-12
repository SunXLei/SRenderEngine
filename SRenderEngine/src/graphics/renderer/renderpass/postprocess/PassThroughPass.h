#pragma once

#include "../RenderPass.h"
#include "./graphics/Scene.h"
#include "./platform/opengl/FrameBuffer.h"
#include "./graphics/Shader.h"

namespace sre
{
	class PassThroughPass : public RenderPass
	{
	public:
		PassThroughPass(Scene* scene);
		~PassThroughPass();

		void Render(GeometryPassOutput gInput,DeferredLightingPassOutput dlightInput, SSRPassOutput ssrInput = { nullptr });

	private:
		Shader* mPassThroughShader;
	};
}