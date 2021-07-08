#pragma once

#include <vector>

#include "./Camera.h"
#include "./model/Model.h"
#include "./renderer/ModelRenderer.h"
#include "./graphics/light/LightManager.h"


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
		inline LightManager* GetLightManager() { return mLightManager; }

	public:
		void Init(int sceneID);


	private:
		//TODO: remember to free pointer
		Camera* mCamera;
		ModelRenderer* mModelRenderer;
		LightManager* mLightManager;

		//TODO: remember to free pointer
		std::vector<Model*> mModels;
	};


}