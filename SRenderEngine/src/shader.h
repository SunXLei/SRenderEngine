#pragma once
#include <string>

#include "glad/glad.h"
#include "glm/glm.hpp"

class Shader
{
public:
	Shader(const char *vertexPath, const char *fragmentPath);
	~Shader();

	void Bind();
	void UnBind();

	void SetBool(const std::string &name, bool value) const;
	void SetInt(const std::string &name, int value) const;
	void SetFloat(const std::string &name, float value) const;
	void SetVec2(const std::string &name, glm::vec2 &value) const;
	void SetVec2(const std::string &name, float x, float y) const;
	void SetVec3(const std::string &name, const glm::vec3 &value) const;
	void SetVec3(const std::string &name, float x, float y, float z) const;
	void SetVec4(const std::string &name, glm::vec4 &value) const;
	void SetVec4(const std::string &name, float x, float y, float z, float w) const;
	void SetMat2(const std::string &name, const glm::mat2 &mat) const;
	void SetMat3(const std::string &name, const glm::mat3 &mat) const;
	void SetMat4(const std::string &name, const glm::mat4 &mat) const;

private:
	void CheckCompileErrors(GLuint shader, std::string type);

public:
	unsigned int m_ShaderID;
};