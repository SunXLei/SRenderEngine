#pragma once

#include <string>
#include <unordered_map>

#include "./Texture.h"

namespace sre
{
	class TextureLoader
	{
	public:
		// TODO: HDR loading
		static Texture* load2DTexture(std::string &path, TextureSettings *settings = nullptr);
		//static Cubemap* loadCubemapTexture(const std::string &right, const std::string &left, const std::string &top, const std::string &bottom, const std::string &back, const std::string &front, CubemapSettings *settings = nullptr);


		static void DestroyCachedTexture();
	private:
		static std::unordered_map<std::string, Texture*> mTextureCache;

	};
}