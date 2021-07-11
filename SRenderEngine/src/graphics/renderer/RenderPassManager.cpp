#include "./RenderPassManager.h"

namespace sre
{
	RenderPassManager::RenderPassManager(Scene* scene):
		mScene(scene), mFowardLightingPass(scene), mShadowmapPass(scene),
		mDeferredGeometryPass(scene),mDeferredLightingPass(scene),mSSRPass(scene),
		mPS(scene)
	{

	}

	RenderPassManager::~RenderPassManager()
	{

	}

	void RenderPassManager::Render()
	{
		// it's a simple test now
		//ShadowmapPassOutput smOutput = mShadowmapPass.Render();
		//mFowardLightingPass.Render(smOutput, true);


		ShadowmapPassOutput smOutput = mShadowmapPass.Render();
		GeometryPassOutput gOutput = mDeferredGeometryPass.Render();
		DeferredLightingPassOutput lightOutput = mDeferredLightingPass.Render(gOutput, smOutput);
		
		SSRPassOutput ssrOutput =  mSSRPass.Render(gOutput, lightOutput);
		
		mPS.Render(gOutput, ssrOutput, lightOutput);
	}
}