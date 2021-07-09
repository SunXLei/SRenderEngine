#pragma once

#include "./graphics/Scene.h"
#include "./graphics/renderer/renderpass/common/ShadowmapPass.h"
#include "./graphics/renderer/renderpass/foward/ForwardLightingPass.h"
#include "./graphics/renderer/renderpass/deferred/DeferredGeometryPass.h"
#include "./graphics/renderer/renderpass/deferred/DeferredLightingPass.h"

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


		ShadowmapPass mShadowmapPass;
		FowardLightingPass mFowardLightingPass;
		DeferredGeometryPass mDeferredGeometryPass;
		DeferredLightingPass mDeferredLightingPass;
	};

}