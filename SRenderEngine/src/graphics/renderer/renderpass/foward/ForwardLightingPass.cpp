#include "./ForwardLightingPass.h"

#include "../common/ShadowmapPass.h"
#include "./platform/window/WindowManager.h"

namespace sre
{
	FowardLightingPass::FowardLightingPass(Scene* scene) :
		RenderPass(scene)
	{
		std::unordered_map<std::string, std::string> blinnShaderPaths;
		blinnShaderPaths.insert({ "vertex","res/shader/forward/BlinnPhong.vert" });
		blinnShaderPaths.insert({ "fragment","res/shader/forward/BlinnPhong.frag" });
		mBlinnShader = new Shader(blinnShaderPaths);
	}

	FowardLightingPass::~FowardLightingPass()
	{
		delete mBlinnShader;
	}

	void FowardLightingPass::Render(const ShadowmapPassOutput &smOutput)
	{
		WindowManager::Bind();
		glViewport(0, 0, WindowManager::Instance()->GetWidth(), WindowManager::Instance()->GetHeight());
		glm::mat4 lightSpaceMatrix = smOutput.directionalLightViewProjMatrix;
		smOutput.shadowmapFramebuffer->GetDepthStencilTexture()->bind();
		mBlinnShader->Bind();
		mBlinnShader->SetUniform("shadowMap", 0);
		mBlinnShader->SetUniform("lightSpaceMatrix", lightSpaceMatrix);


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