#pragma once

#include "../RenderPass.h"
#include "./graphics/Scene.h"
#include "./graphics/Shader.h"

namespace sre
{
	struct ShadowmapPassOutput;

	class FowardLightingPass : public RenderPass
	{
	public:
		FowardLightingPass(Scene* scene);
		~FowardLightingPass();

		void Render(const ShadowmapPassOutput &smOutput, bool isUsePBR = true);

	private:
		Shader* mBlinnShader;
		Shader* mPBRShader;
		Shader* mDebugShader;
	};
}