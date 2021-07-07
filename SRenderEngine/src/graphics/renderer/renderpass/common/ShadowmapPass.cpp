#include "./ShadowmapPass.h"

#include "./macros.h"

#include "./graphics/Camera.h"
#include "./glm/gtc/matrix_transform.hpp"

namespace sre
{
	ShadowmapPass::ShadowmapPass(Scene* scene):
		RenderPass(scene)
	{
		std::unordered_map<std::string, std::string> shadowmapShaderPaths;
		shadowmapShaderPaths.insert({ "vertex","res/shader/ShadowmapGeneration.vert" });
		shadowmapShaderPaths.insert({ "fragment","res/shader/ShadowmapGeneration.frag" });
		mShadowmapGenShader = new Shader(shadowmapShaderPaths);

		mShadowmapFB = new FrameBuffer(SHADOWMAP_RESOLUTION_X, SHADOWMAP_RESOLUTION_Y);
		mShadowmapFB->AddDepthStencilTexture(GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT);
		mShadowmapFB->CreateFrameBuffer();

	}
	ShadowmapPass::~ShadowmapPass()
	{
		delete mShadowmapFB;
		delete mShadowmapGenShader;
	}

	ShadowmapPassOutput ShadowmapPass::Render()
	{
		glViewport(0, 0, mShadowmapFB->GetWidth(), mShadowmapFB->GetHeight());
		mShadowmapFB->Bind();
		mShadowmapFB->Clear();

		// setup
		ModelRenderer* modelRenderer = mScene->GetModelRenderer();
		Camera* camera = mScene->GetCamera();
		glm::vec3 directionalLightDir(1.0f, 1.0f, 1.0f);

		// view setup
		mShadowmapGenShader->Bind();
		glm::vec3 dirLightShadowmapLookAtPos = camera->GetPosition() + (glm::normalize(camera->GetFront()) * 10.0f);
		glm::vec3 dirLightShadowmapEyePos = dirLightShadowmapLookAtPos + (glm::normalize(directionalLightDir) * 30.0f);
		glm::mat4 directionalLightProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, SHADOWMAP_NEAR_PLANE, SHADOWMAP_FAR_PLANE);
		glm::mat4 directionalLightView = glm::lookAt(dirLightShadowmapEyePos, dirLightShadowmapLookAtPos, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 directionalLightViewProjMatrix = directionalLightProjection * directionalLightView;
		mShadowmapGenShader->SetUniform("lightSpaceMatrix", directionalLightViewProjMatrix);

		// setup model renderer
		mScene->AddModelsToRender();

		// render models
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDisable(GL_BLEND);
		glDisable(GL_CULL_FACE); // for transparent object

		// render
		modelRenderer->Render(mShadowmapGenShader, false);


		// Render pass output
		ShadowmapPassOutput passOutput;
		passOutput.directionalLightViewProjMatrix = directionalLightViewProjMatrix;
		passOutput.shadowmapFramebuffer = mShadowmapFB;
		return passOutput;
	}
}