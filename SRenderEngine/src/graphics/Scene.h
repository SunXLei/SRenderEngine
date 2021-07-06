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

		// add all scene's models to render's renderqueue
		void AddModelsToRender();

		inline Camera* GetCamera() { return mCamera; }
		inline ModelRenderer* GetModelRenderer() { return mModelRenderer; }

	public:
		void Init(int sceneID);


	private:
		//TODO: remember to free pointer
		Camera* mCamera;
		ModelRenderer* mModelRenderer;

		//TODO: remember to free pointer
		std::vector<Model*> mModels;
	};


}