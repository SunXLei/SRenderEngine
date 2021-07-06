#pragma once

#include "../RenderPass.h"
#include "./graphics/Scene.h"
#include "./graphics/Shader.h"

namespace sre
{
	class FowardLightingPass : public RenderPass
	{
	public:
		FowardLightingPass(Scene* scene);
		~FowardLightingPass();

		void Render();

	private:
		Shader* mBlinnShader; // TODO: remember to release
	};
}