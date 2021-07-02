#pragma once

#include <vector>

#include "./Camera.h"
#include "./model/Model.h"
#include "./renderer/ModelRenderer.h"


namespace sre
{
	class Scene
	{
	public:
		Scene(int sceneID = 0);
		~Scene();


		void Update(float deltaTime);

		void AddModelsToRender();

		inline Camera* GetCamera() { return mCamera; }

	public:
		void Init(int sceneID);

	// TODO:
	private:
		Camera* mCamera;
		ModelRenderer* mModelRenderer;

		std::vector<Model*> mModels;
	};


}