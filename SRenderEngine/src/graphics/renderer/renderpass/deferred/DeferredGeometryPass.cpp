#include "./DeferredGeometryPass.h"

#include "./platform/window/WindowManager.h"

namespace sre
{
	DeferredGeometryPass::DeferredGeometryPass(Scene* scene):
		RenderPass(scene)
	{
		// create shader
		std::unordered_map<std::string, std::string> geometryShaderPaths;
		geometryShaderPaths.insert({ "vertex","res/shader/deferred/GeometryPass.vert" });
		geometryShaderPaths.insert({ "fragment","res/shader/deferred/GeometryPass.frag" });
		mGeometryShader = new Shader(geometryShaderPaths);

		// create GBuffer
		mGBuffer = new GBuffer(WindowManager::Instance()->GetWidth(), WindowManager::Instance()->GetHeight());
	}

	DeferredGeometryPass::~DeferredGeometryPass()
	{
		delete mGBuffer;
		delete mGeometryShader;
	}

	GeometryPassOutput DeferredGeometryPass::Render()
	{
		// bind gbuffer framebuffer
		mGBuffer->Bind();
		mGBuffer->Clear();
		glViewport(0, 0, mGBuffer->GetWidth(), mGBuffer->GetHeight());

		// setup
		ModelRenderer* modelRenderer = mScene->GetModelRenderer();
		Camera* camera = mScene->GetCamera();
		LightManager* lightManager = mScene->GetLightManager();
		
		// bind shader
		mGeometryShader->Bind();

		// set view, projection matrix, note the model matrix is set in modelrenderer
		mGeometryShader->SetUniform("view", camera->GetViewMatrix());
		mGeometryShader->SetUniform("projection", camera->GetProjectionMatrix());

		// add models to renderer
		mScene->AddModelsToRender();

		// set renderer modes
		modelRenderer->SetupRenderState();

		// render
		modelRenderer->Render(mGeometryShader, true);

		DisplayTexture(0, 0, 100, 100, mGBuffer->GetRenderTarget(0), 4, 10);
		DisplayTexture(100, 0, 100, 100, mGBuffer->GetRenderTarget(1), 4, 11);
		DisplayTexture(200, 0, 100, 100, mGBuffer->GetRenderTarget(2), 4, 12);
		DisplayTexture(300, 0, 100, 100, mGBuffer->GetRenderTarget(3), 1, 13);
		DisplayTexture(400, 0, 100, 100, mGBuffer->GetRenderTarget(3), 2, 14);
		DisplayTexture(500, 0, 100, 100, mGBuffer->GetRenderTarget(3), 3, 15);

		return {mGBuffer};
	}
}