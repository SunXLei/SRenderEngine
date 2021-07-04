#pragma once

#include <deque>

#include "./graphics/Camera.h"
#include "./graphics/model/Model.h"

namespace sre
{
	// ModelRenderer render all models which are in render queue
	class ModelRenderer
	{
	public:
		ModelRenderer(Camera *camera);
		~ModelRenderer();

		void SubmitRenderModel(Model *model);
		void SetupRenderState();

		void Render(Shader *shader, bool isUseMaterial);

	private:
		void SetupModelMatrix(Model *model, Shader *shader, bool isUseMaterial);

	private:
		Camera *mCamera;

		std::deque<Model*> mRenderQueue;

	};
}