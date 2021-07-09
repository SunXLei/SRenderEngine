#include "./RenderPass.h"

#include "./glad/glad.h"
#include "./platform/window/WindowManager.h"

namespace sre
{
	RenderPass::RenderPass(Scene* scene)
		:mScene(scene)
	{
		// create debug shader
		std::unordered_map<std::string, std::string> debugShaderPaths;
		debugShaderPaths.insert({ "vertex","res/shader/common/DebugDisplay.vert" });
		debugShaderPaths.insert({ "fragment","res/shader/common/DebugDisplay.frag" });
		mDebugShader = new Shader(debugShaderPaths);
	}

	RenderPass::~RenderPass()
	{
		delete mDebugShader;
	}

	void RenderPass::DisplayTexture(int startx, int starty, int width, int height, Texture* texture, int unit /* = 9  */)
	{
		// bind default framebuffer
		WindowManager::Bind();

		// bind debug shader
		mDebugShader->Bind();

		// set the texture display position
		glViewport(startx, starty, width, height);

		// bind texture
		texture->bind(unit);
		mDebugShader->SetUniform("displayTexture", unit);

		// draw ndc plane
		mScene->GetModelRenderer()->NDC_Plane.Draw();
	}
}