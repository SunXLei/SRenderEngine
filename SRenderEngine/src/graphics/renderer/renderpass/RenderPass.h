#pragma once

#include "./graphics/Scene.h"

namespace sre
{ 
	// for now, the RenderPass class is a little bit dumb
	class RenderPass
	{
	public:
		RenderPass(Scene *scene);
		virtual ~RenderPass();

	protected:
		Scene* mScene;

	};
}