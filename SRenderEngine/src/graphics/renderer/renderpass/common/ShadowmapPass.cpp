#include "./ShadowmapPass.h"

#include "./macros.h"

#include "./graphics/Camera.h"
#include "./graphics/light/LightManager.h"
#include "./glm/gtc/matrix_transform.hpp"

namespace sre
{
	ShadowmapPass::ShadowmapPass(Scene* scene):
		RenderPass(scene)
	{
		// create shader
		std::unordered_map<std::string, std::string> shadowmapShaderPaths;
		shadowmapShaderPaths.insert({ "vertex","res/shader/common/ShadowmapGeneration.vert" });
		shadowmapShaderPaths.insert({ "fragment","res/shader/common/ShadowmapGeneration.frag" });
		mShadowmapGenShader = new Shader(shadowmapShaderPaths);

		// create framebuffer
		mShadowmapFB = new FrameBuffer(SHADOWMAP_RESOLUTION_X, SHADOWMAP_RESOLUTION_Y);
		mShadowmapFB->AddDepthStencilTexture(GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_FLOAT, GL_DEPTH_ATTACHMENT);
		mShadowmapFB->CreateFrameBuffer();

	}
	ShadowmapPass::~ShadowmapPass()
	{
		delete mShadowmapFB;
		delete mShadowmapGenShader;
	}

	ShadowmapPassOutput ShadowmapPass::Render()
	{
		// bind shadowmap framebuffer
		mShadowmapFB->Bind();
		mShadowmapFB->Clear();
		glViewport(0, 0, mShadowmapFB->GetWidth(), mShadowmapFB->GetHeight());

		// setup
		ModelRenderer* modelRenderer = mScene->GetModelRenderer();
		Camera* camera = mScene->GetCamera();
		LightManager* lightManager = mScene->GetLightManager();
		glm::vec3 directionalLightDir = lightManager->GetDirectionalLightDirection(0);

		// view setup
		mShadowmapGenShader->Bind();
		glm::vec3 dirLightShadowmapLookAtPos = camera->GetPosition() + (glm::normalize(camera->GetFront()) * 10.0f);
		glm::vec3 dirLightShadowmapEyePos = dirLightShadowmapLookAtPos + (glm::normalize(directionalLightDir) * 20.0f);
		glm::mat4 directionalLightProjection = glm::ortho(-30.0f, 30.0f, -30.0f, 30.0f, SHADOWMAP_NEAR_PLANE, SHADOWMAP_FAR_PLANE);
		glm::mat4 directionalLightView = glm::lookAt(dirLightShadowmapEyePos, dirLightShadowmapLookAtPos, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 directionalLightViewProjMatrix = directionalLightProjection * directionalLightView;
		mShadowmapGenShader->SetUniform("lightSpaceMatrix", directionalLightViewProjMatrix);

		// add models to renderer
		mScene->AddModelsToRender();

		// set render modes
		modelRenderer->SetupRenderState(); // We do not consider transpare or one face object now, assume it is all opaque.

		// render
		modelRenderer->Render(mShadowmapGenShader, false);


		// Render pass output
		ShadowmapPassOutput passOutput;
		passOutput.lightSpaceMatrix = directionalLightViewProjMatrix;
		passOutput.shadowmapFramebuffer = mShadowmapFB;
		return passOutput;
	}
}