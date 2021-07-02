#include "./Scene.h"

namespace sre 
{
	Scene::Scene()
	{
		mCamera = new Camera();
	}
	Scene::~Scene()
	{
	}

	void Scene::Update(float deltaTime)
	{
		mCamera->ProcessInput(deltaTime);
	}
}