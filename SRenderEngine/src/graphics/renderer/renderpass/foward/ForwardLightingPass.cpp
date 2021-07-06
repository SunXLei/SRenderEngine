#include "./ForwardLightingPass.h"

namespace sre
{
	FowardLightingPass::FowardLightingPass(Scene* scene) :
		RenderPass(scene)
	{
		std::unordered_map<std::string, std::string> blinnShaderPaths;
		blinnShaderPaths.insert({ "vertex","res/shader/blinnphong.vert" });
		blinnShaderPaths.insert({ "fragment","res/shader/blinnphong.frag" });
		mBlinnShader = new Shader(blinnShaderPaths);
	}

	FowardLightingPass::~FowardLightingPass()
	{

	}
	void FowardLightingPass::Render()
	{
		ModelRenderer* modelRenderer = mScene->GetModelRenderer();
		Camera* camera = mScene->GetCamera();
		mScene->AddModelsToRender();
		mBlinnShader->Bind();
		// Set view, projection matrix, note the model matrix is set in modelrenderer
		mBlinnShader->SetUniform("view", camera->GetViewMatrix());
		mBlinnShader->SetUniform("projection", camera->GetProjectionMatrix());
		
		// set eye position
		mBlinnShader->SetUniform("viewPos", camera->GetPosition());

		// set light
		mBlinnShader->SetUniform("lightPos", glm::vec3(1.0f, 1.0f, 1.0f));


		// draw
		mBlinnShader->Bind();
		modelRenderer->SetupRenderState();
		modelRenderer->Render(mBlinnShader, true);
	}
}