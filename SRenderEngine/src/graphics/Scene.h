#pragma once

#include "./Camera.h"

namespace sre
{
	class Scene
	{
	public:
		Scene();
		~Scene();

		void Update(float deltaTime);
		Camera* GetCamera() { return mCamera; }

	// TODO:
	private:
		Camera* mCamera;
	};


}