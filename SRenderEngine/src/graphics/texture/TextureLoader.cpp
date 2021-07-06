#define STB_IMAGE_IMPLEMENTATION
#include "./TextureLoader.h"

#include <iostream>

#include "./stb_image.h"

namespace sre
{
	std::unordered_map<std::string, Texture*> TextureLoader::mTextureCache;

	Texture* TextureLoader::Load2DTexture(const std::string& path, TextureSettings* settings)
	{
		// check the cache
		auto iter = mTextureCache.find(path);
		if (iter != mTextureCache.end()) 
			return iter->second;
		

		// load texture
		int width, height, numComponents;
		std::cout << path << "\n";
		unsigned char *data = stbi_load(path.c_str(), &width, &height, &numComponents, 0);
		if (!data) 
		{
			std::cout <<"TEXTURE LOAD FAIL - path:"<< path<<"\n";
			stbi_image_free(data);
			return nullptr;
		}

		GLenum dataFormat;
		switch (numComponents) 
		{
			case 1: dataFormat = GL_RED;  break;
			case 3: dataFormat = GL_RGB;  break;
			case 4: dataFormat = GL_RGBA; break;
		}

		// use the specified of default settings to initialize texture
		Texture *texture = nullptr;
		if (settings != nullptr) 
			texture = new Texture(*settings);
		else 
			texture = new Texture();
		texture->Generate2DTexture(width, height, dataFormat, GL_UNSIGNED_BYTE, data);

		mTextureCache.insert(std::pair<std::string, Texture*>(path, texture));
		stbi_image_free(data);

		return mTextureCache[path];
	}

	void TextureLoader::DestroyCachedTexture()
	{
		for (auto &item : mTextureCache)
			delete item.second;
		
	}
}