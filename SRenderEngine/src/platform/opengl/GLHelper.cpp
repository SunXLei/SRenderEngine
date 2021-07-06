//#include "./GLHelper.h"
//
//namespace sre
//{
//	GLHelper* GLHelper::sInstance = nullptr;
//
//	GLHelper* GLHelper::Instance()
//	{
//		if (sInstance == nullptr)
//			sInstance = new GLHelper();
//		return sInstance;
//	}
//
//	GLHelper::~GLHelper()
//	{
//	}
//
//	void GLHelper::SetDepthTest(bool choice)
//	{
//		if (choice)
//			glEnable(GL_DEPTH_TEST);
//		else
//			glDisable(GL_DEPTH_TEST);
//	}
//
//	void GLHelper::SetStencilTest(bool choice)
//	{
//		if (choice)
//			glEnable(GL_STENCIL_TEST);
//		else
//			glDisable(GL_STENCIL_TEST);
//	}
//
//	void GLHelper::SetBlend(bool choice)
//	{
//		if (choice)
//			glEnable(GL_BLEND);
//		else
//			glDisable(GL_BLEND);
//	}
//
//	void GLHelper::SetFaceCull(bool choice)
//	{
//		if (choice)
//			glEnable(GL_CULL_FACE);
//		else
//			glDisable(GL_CULL_FACE);
//	}
//
//	void GLHelper::SetMultisample(bool choice)
//	{
//		if (choice)
//			glEnable(GL_MULTISAMPLE);
//		else
//			glDisable(GL_MULTISAMPLE);
//	}
//
//	void GLHelper::SetDepthFunc(GLenum depthFunc)
//	{
//		glDepthFunc(depthFunc);
//	}
//
//	void GLHelper::SetStencilFunc(GLenum testFunc, int stencilFragValue, unsigned int stencilBitmask)
//	{
//		glStencilFuncSeparate(GL_FRONT_AND_BACK, testFunc, stencilFragValue, stencilBitmask);
//	}
//
//	void GLHelper::SetStencilOp(GLenum stencilFailOperation, GLenum depthFailOperation, GLenum depthPassOperation)
//	{
//		glStencilOpSeparate(GL_FRONT_AND_BACK, stencilFailOperation, depthFailOperation, depthPassOperation);
//	}
//
//	void GLHelper::SetStencilWriteMask(unsigned int bitmask)
//	{
//		glStencilMaskSeparate(GL_FRONT_AND_BACK, bitmask);
//	}
//
//	void GLHelper::SetBlendFunc(GLenum src, GLenum dst)
//	{
//		glBlendFunc(src, dst);
//	}
//
//	void GLHelper::SetCullFace(GLenum faceToCull)
//	{
//		glCullFace(faceToCull);
//	}
//
//	void GLHelper::SwitchShader(unsigned int shaderID)
//	{
//	}
//}