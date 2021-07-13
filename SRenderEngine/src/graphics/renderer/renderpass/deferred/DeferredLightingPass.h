#pragma once

#include "../RenderPass.h"
#include "./graphics/Scene.h"
#include "./platform/opengl/FrameBuffer.h"
#include "./graphics/Shader.h"

namespace sre
{
	class DeferredLightingPass : public RenderPass
	{
	public:
		DeferredLightingPass(Scene* scene);
		~DeferredLightingPass();

		LightingPassOutput Render(GeometryPassOutput gInput, ShadowmapPassOutput smInput);

	private:
		Shader* mLightingShader;
		FrameBuffer* mLightingFBO;
	};
}