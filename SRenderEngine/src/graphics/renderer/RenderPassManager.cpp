#include "./RenderPassManager.h"

namespace sre
{
	RenderPassManager::RenderPassManager(Scene* scene):
		mScene(scene), mFowardLightingPass(scene), mShadowmapPass(scene)
	{

	}

	RenderPassManager::~RenderPassManager()
	{

	}

	void RenderPassManager::Render()
	{
		// it's a simple test now
		ShadowmapPassOutput smOutput = mShadowmapPass.Render();
		mFowardLightingPass.Render(smOutput);
	}
}