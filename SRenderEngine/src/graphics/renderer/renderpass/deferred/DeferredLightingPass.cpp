#include "./DeferredLightingPass.h"

#include "./platform/window/WindowManager.h"

namespace sre
{
	DeferredLightingPass::DeferredLightingPass(Scene* scene):
		RenderPass(scene)
	{		
		// create shader
		std::unordered_map<std::string, std::string> lightingShaderPaths;
		lightingShaderPaths.insert({ "vertex","res/shader/deferred/LightingPass.vert" });
		lightingShaderPaths.insert({ "fragment","res/shader/deferred/LightingPass.frag" });
		mLightingShader = new Shader(lightingShaderPaths);

		// create FBO
		mLightingFBO = new FrameBuffer(WindowManager::Instance()->GetWidth(), WindowManager::Instance()->GetHeight());
		

		// add attachment and check whether success by call CreateFrameBuffer
		TextureSettings colorTextureSettings;
		colorTextureSettings.TextureFormat = GL_RGBA32F;
		colorTextureSettings.TextureWrapSMode = GL_CLAMP_TO_EDGE;
		colorTextureSettings.TextureWrapTMode = GL_CLAMP_TO_EDGE;
		colorTextureSettings.TextureMagnificationFilterMode = GL_LINEAR;
		colorTextureSettings.TextureMinificationFilterMode = GL_LINEAR;
		colorTextureSettings.HasMips = false;
		mLightingFBO->AddColorTexture(colorTextureSettings, GL_RGBA, GL_FLOAT, GL_COLOR_ATTACHMENT0);
		mLightingFBO->AddDepthStencilRBO(GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT);
		mLightingFBO->CreateFrameBuffer();

	}

	DeferredLightingPass::~DeferredLightingPass()
	{
		delete mLightingFBO;
		delete mLightingShader;
	}

	LightingPassOutput DeferredLightingPass::Render(GeometryPassOutput gInput, ShadowmapPassOutput smInput)
	{
		mLightingFBO->Bind();
		mLightingFBO->Clear();
		glViewport(0, 0, mLightingFBO->GetWidth(), mLightingFBO->GetHeight());

		// setup
		ModelRenderer* modelRenderer = mScene->GetModelRenderer();
		Camera* camera = mScene->GetCamera();
		LightManager* lightManager = mScene->GetLightManager();

		// set view position
		mLightingShader->Bind();
		mLightingShader->SetUniform("viewPos", camera->GetPosition());

		// set light
		lightManager->BindCurrentLights(mLightingShader);

		// set shadowmap 
		smInput.shadowmapFramebuffer->GetDepthStencilTexture()->bind(0);
		mLightingShader->SetUniform("shadowMap", 0);
		mLightingShader->SetUniform("lightSpaceMatrix", smInput.lightSpaceMatrix);

		// set gbuffet
		gInput.outputGBuffer->GetRenderTarget(0)->bind(4);
		mLightingShader->SetUniform("albedoTexture", 4);
		gInput.outputGBuffer->GetRenderTarget(1)->bind(5);
		mLightingShader->SetUniform("normalTexture", 5);
		gInput.outputGBuffer->GetRenderTarget(2)->bind(6);
		mLightingShader->SetUniform("positionTexture", 6);
		gInput.outputGBuffer->GetRenderTarget(3)->bind(7);
		mLightingShader->SetUniform("mixtureTexture", 7);

		// draw
		modelRenderer->NDC_Plane.Draw();

		DisplayTexture(0, 0, WindowManager::Instance()->GetWidth(), WindowManager::Instance()->GetHeight(), mLightingFBO->GetColourTexture(), 4, 8);

		return {mLightingFBO};
	}
}