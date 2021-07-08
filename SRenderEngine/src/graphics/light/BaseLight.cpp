#include "./BaseLight.h"

namespace sre
{
	BaseLight::BaseLight(float intensity, const glm::vec3& lightColor):
		mIntensity(intensity), mLightColor(lightColor)
	{

	}

	BaseLight::~BaseLight()
	{
	}
}