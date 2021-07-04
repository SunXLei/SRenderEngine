#include "./ModelRenderer.h"

namespace sre
{

	ModelRenderer::ModelRenderer(Camera *camera)
		:mCamera(camera)
	{
	}

	ModelRenderer::~ModelRenderer()
	{
	}

	void ModelRenderer::SubmitRenderModel(Model *model)
	{
		mRenderQueue.push_back(model);
	}

	void ModelRenderer::SetupRenderState()
	{
	}

	void ModelRenderer::Render(Shader *shader, bool isUseMaterial)
	{
		// render all objects
		while (!mRenderQueue.empty()) 
		{
			Model *current = mRenderQueue.front();

			SetupModelMatrix(current, shader, isUseMaterial);
			current->Draw(shader, isUseMaterial);

			mRenderQueue.pop_front();
		}
	}

	void ModelRenderer::SetupModelMatrix(Model *model, Shader *shader, bool isUseMaterial)
	{

	}

}