#pragma once

#include "../RenderPass.h"
#include "./graphics/Scene.h"
#include "./platform/opengl/GBuffer.h"
#include "./graphics/Shader.h"

namespace sre
{
	class DeferredGeometryPass : public RenderPass
	{
	public:
		DeferredGeometryPass(Scene* scene);
		~DeferredGeometryPass();

		GeometryPassOutput Render();

	private:
		GBuffer* mGBuffer;
		Shader* mGeometryShader;
	};
}