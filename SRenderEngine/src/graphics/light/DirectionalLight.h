#pragma once

#include "./BaseLight.h"
#include "./graphics/Shader.h"
#include "./glm/glm.hpp"

namespace sre
{
	class LightManager;

	class DirectionalLight : public BaseLight
	{
		friend LightManager;
	public:
		DirectionalLight(float intensity, const glm::vec3& lightColor, const glm::vec3& lightDir);
		virtual ~DirectionalLight();

		virtual void SetupUniforms(Shader* shader, int currentLightIndex) override;

	private:
		glm::vec3 mLightDir;
	};
}