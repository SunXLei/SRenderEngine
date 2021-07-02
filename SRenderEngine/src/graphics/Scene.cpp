#include "./Scene.h"

namespace sre 
{
	Scene::Scene(int sceneID)
	{
		mCamera = new Camera();

		// TODO: this is a fake renderer now, wait to implement. And user-defined class 
		// should be intialized in initialization list
		mModelRenderer = new ModelRenderer();

		Init(sceneID);
	}
	Scene::~Scene()
	{
		delete mCamera;
	}

	void Scene::Update(float deltaTime)
	{
		mCamera->ProcessInput(deltaTime);
	}

	void Scene::AddModelsToRender()
	{
		// TODO: add all models to renderer's render queue

	}

	void Scene::Init(int sceneID)
	{
		// TODO: initialize model to mModels according to sceneID
	}
}