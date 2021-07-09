#pragma once

#include "./graphics/texture/Texture.h"
#include "./graphics/Scene.h"

namespace sre
{ 
	// for now, the RenderPass class is a little bit dumb
	class RenderPass
	{
	public:
		RenderPass(Scene *scene);
		virtual ~RenderPass();

		void DisplayTexture(int startx, int starty, int width, int height, Texture* texture, int unit = 9);

	protected:
		Scene* mScene;
		Shader* mDebugShader;
	};
}