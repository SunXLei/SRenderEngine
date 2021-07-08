#include "./LightManager.h"

namespace sre
{
	LightManager::LightManager()
	{
		InitBasicLights();
	}

	LightManager::~LightManager()
	{
	}

	void LightManager::BindCurrentLights(Shader* shader)
	{
		shader->SetUniform("numDirPointSpotLights", glm::ivec3(mDirectionalLights.size(), mPointLights.size(), mSpotLights.size()));

		for (int i = 0; i < mDirectionalLights.size(); i++)
			mDirectionalLights[i].SetupUniforms(shader, i);

		for (int i = 0; i < mSpotLights.size(); i++)
			mSpotLights[i].SetupUniforms(shader, i);

		for (int i = 0; i < mPointLights.size(); i++)
			mPointLights[i].SetupUniforms(shader, i);
	}

	void LightManager::AddDirectionalLight(const DirectionalLight& directionalLight)
	{
		mDirectionalLights.push_back(directionalLight);
	}

	void LightManager::AddPointLight(const PointLight& pointLight)
	{
		mPointLights.push_back(pointLight);
	}

	void LightManager::AddSpotLight(const SpotLight& spotLight)
	{
		mSpotLights.push_back(spotLight);
	}

	const glm::vec3& LightManager::GetDirectionalLightDirection(unsigned int index)
	{
		return mDirectionalLights[index].mLightDir;
	}

	void LightManager::InitBasicLights()
	{
		// Setup some lights for the scene
		DirectionalLight directionalLight1(2.0f, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, -0.3f));
		AddDirectionalLight(directionalLight1);

		//SpotLight spotlight1(100.0f, glm::vec3(1.0f, 1.0f, 1.0f), 50.0f, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), glm::cos(glm::radians(12.5f)), glm::cos(glm::radians(15.0f)));
		//AddSpotLight(spotlight1);

		//PointLight pointLight1(10.0f, glm::vec3(1.0f, 0.0f, 1.0f), 30.0f, glm::vec3(120.0f, 84.0f, 122.0f));
		//AddPointLight(pointLight1);

		//PointLight pointLight2(10.0f, glm::vec3(1.0f, 0.25f, 0.0f), 30.0f, glm::vec3(120.0f, 77.0f, 100.0f));
		//AddPointLight(pointLight2);
	}
}