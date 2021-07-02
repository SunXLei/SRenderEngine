#include "shader.h"

#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char *vertexPath, const char *fragmentPath)
{
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vertexFile; 
	std::ifstream fragmentFile;

	// ensure ifstream can throw exceptions when exact bit is set
	vertexFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fragmentFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		// open files
		vertexFile.open(vertexPath);
		fragmentFile.open(fragmentPath);

		// read files and close
		std::stringstream vertexStream, fragmentStream;
		vertexStream << vertexFile.rdbuf();
		fragmentStream << fragmentFile.rdbuf();
		vertexFile.close();
		fragmentFile.close();

		// convert to string
		vertexCode = vertexStream.str();
		fragmentCode = fragmentStream.str();

		//std::cout << vertexCode << std::endl;
		//std::cout << fragmentCode << std::endl;
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_NOTSUCCESFULLY_READ" << std::endl;
	}

	const char *vertexSource = vertexCode.c_str();
	const char *fragmentSource = fragmentCode.c_str();

	// compile shaders
	unsigned int vertex, fragment;
	
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexSource, NULL);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentSource, NULL);
	glCompileShader(fragment);
	CheckCompileErrors(fragment, "FRAGMENT");

	m_ShaderID = glCreateProgram();
	glAttachShader(m_ShaderID, vertex);
	glAttachShader(m_ShaderID, fragment);
	glLinkProgram(m_ShaderID);
	CheckCompileErrors(m_ShaderID, "PROGRAM");
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

void Shader::Bind()
{
	glUseProgram(m_ShaderID);
}

void Shader::UnBind()
{
	glUseProgram(0);
}

void Shader::SetBool(const std::string &name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), (int)value);
}

void Shader::SetInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_ShaderID, name.c_str()), value);
}

void Shader::SetVec2(const std::string &name, glm::vec2 &value) const
{
	glUniform2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec2(const std::string &name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y);
}

void Shader::SetVec3(const std::string &name, const glm::vec3 &value) const
{
	glUniform3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y, z);
}

void Shader::SetVec4(const std::string &name, glm::vec4 &value) const
{
	glUniform4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, &value[0]);
}

void Shader::SetVec4(const std::string &name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_ShaderID, name.c_str()), x, y, z, w);
}

void Shader::SetMat2(const std::string &name, const glm::mat2 &mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_ShaderID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::CheckCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog 
				<< "\n -- --------------------------------------------------- -- " << std::endl;
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog 
					<< "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
}

