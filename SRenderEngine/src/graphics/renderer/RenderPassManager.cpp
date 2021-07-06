#include "./RenderPassManager.h"

namespace sre
{
	RenderPassManager::RenderPassManager(Scene* scene):
		mScene(scene), mFowardLightingPass(scene)
	{

	}

	RenderPassManager::~RenderPassManager()
	{

	}

	void RenderPassManager::Render()
	{
		// it's a simple test now
		mFowardLightingPass.Render();
	}
}