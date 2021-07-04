#include "./Material.h"

#include "./graphics/texture/TextureLoader.h"

namespace sre
{

	Material::Material(Texture * albedoMap, Texture * normalMap, Texture * metallicMap, Texture * roughnessMap, Texture * ambientOcclusionMap):
		mAlbedoMap(albedoMap), mNormalMap(normalMap),
		mMetallicMap(metallicMap), mRoughnessMap(roughnessMap),
		mAOMap(ambientOcclusionMap)
	{
	}

	Material::~Material()
	{
	}

	void Material::BindMaterial(Shader * shader) const
	{
		// shader need to be bound outside before binding the material textures

		// Texture unit 0 is reserved for the shadowmap
		// Texture unit 1 is reserved for the irradianceMap used for indirect diffuse IBL
		// Texture unit 2 is reserved for the prefilterMap
		// Texture unit 3 is reserved for the brdfLUT
		int currentTextureUnit = 4;

		shader->SetUniform("material.texture_albedo", currentTextureUnit);
		if (mAlbedoMap) 
			mAlbedoMap->bind(currentTextureUnit++);
		else 
		{ }
			//TextureLoader::GetDefaultAlbedo()->bind(currentTextureUnit++);

		shader->SetUniform("material.texture_normal", currentTextureUnit);
		if (mNormalMap) 
			mNormalMap->bind(currentTextureUnit++);
		else 
		{ }
			//TextureLoader::GetDefaultNormal()->bind(currentTextureUnit++);

		shader->SetUniform("material.texture_metallic", currentTextureUnit);
		if (mMetallicMap) 
			mMetallicMap->bind(currentTextureUnit++);
		else 
		{ }
			//TextureLoader::getDefaultMetallic()->bind(currentTextureUnit++);

		shader->SetUniform("material.texture_roughness", currentTextureUnit);
		if (mRoughnessMap) 
			mRoughnessMap->bind(currentTextureUnit++);
		else 
		{ }
			//TextureLoader::getDefaultRoughness()->bind(currentTextureUnit++);

		shader->SetUniform("material.texture_ao", currentTextureUnit);
		if (mAOMap) 
			mAOMap->bind(currentTextureUnit++);
		else 
		{ }
			//TextureLoader::getDefaultAO()->bind(currentTextureUnit++);


		//shader->SetUniform("material.texture_displacement", currentTextureUnit);
		//if (mDisplacementMap)
		//{
		//	shader->SetUniform("hasDisplacement", true);
		//	shader->SetUniform("minMaxDisplacementSteps", glm::vec2(mParallaxMinSteps, mParallelMaxSteps));
		//	shader->SetUniform("parallaxStrength", mParallaxStrength);
		//	mDisplacementMap->bind(currentTextureUnit++);
		//}
		//else 
		//	shader->SetUniform("hasDisplacement", false);
	}
}