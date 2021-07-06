#pragma once

#include "./graphics/Scene.h"
#include "./graphics/renderer/renderpass/foward/ForwardLightingPass.h"

namespace sre
{

	class RenderPassManager
	{
	public:
		RenderPassManager(Scene* scene);
		~RenderPassManager();

		void Init();
		void Render();

	private:
		Scene* mScene;  // mScene's memory is managed outside

		FowardLightingPass mFowardLightingPass;
	};

}