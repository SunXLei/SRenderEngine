#pragma once

#include <string>

#include "./graphics/Scene.h"
#include "./graphics/renderer/renderpass/common/ShadowmapPass.h"
#include "./graphics/renderer/renderpass/foward/ForwardLightingPass.h"
#include "./graphics/renderer/renderpass/deferred/DeferredGeometryPass.h"
#include "./graphics/renderer/renderpass/deferred/DeferredLightingPass.h"
#include "./graphics/renderer/renderpass/postprocess/SSRPass.h"
#include "./graphics/renderer/renderpass/postprocess/FXAAPass.h"
#include "./graphics/renderer/renderpass/postprocess/PassThroughPass.h"

namespace sre
{

	class RenderPassManager
	{
	public:
		RenderPassManager(Scene* scene);
		~RenderPassManager();

		void Init();
		void Render();
		void SaverRenderFrame(const std::string& savePath);

	private:
		Scene* mScene;  // mScene's memory is managed outside


		ShadowmapPass mShadowmapPass;
		FowardLightingPass mFowardLightingPass;
		DeferredGeometryPass mDeferredGeometryPass;
		DeferredLightingPass mDeferredLightingPass;
		SSRPass mSSRPass;
		FXAAPass mFXAAPass;
		PassThroughPass mPS;
	};

}