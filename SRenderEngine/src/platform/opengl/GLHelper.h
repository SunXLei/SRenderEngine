//#pragma once
//
//#include "./glad/glad.h"
//
//namespace sre
//{
//	class GLHelper
//	{
//	public:
//		static GLHelper* Instance();
//		~GLHelper();
//
//		void SetDepthTest(bool choice);
//		void SetStencilTest(bool choice);
//		void SetBlend(bool choice);
//		void SetFaceCull(bool choice);
//		void SetMultisample(bool choice);
//
//		void SetDepthFunc(GLenum depthFunc);
//		void SetStencilFunc(GLenum testFunc, int stencilFragValue, unsigned int stencilBitmask);
//		void SetStencilOp(GLenum stencilFailOperation, GLenum depthFailOperation, GLenum depthPassOperation);
//		void SetStencilWriteMask(unsigned int bitmask);
//		void SetBlendFunc(GLenum src, GLenum dst);
//		void SetCullFace(GLenum faceToCull);
//
//		void SwitchShader(unsigned int shaderID);
//
//	private:
//		GLHelper();
//		static GLHelper* sInstance;
//	};
//}