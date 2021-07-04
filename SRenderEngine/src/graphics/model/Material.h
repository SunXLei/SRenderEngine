#pragma once

#include "./graphics/texture/Texture.h"
#include "./graphics/Shader.h"

namespace sre
{
	class Material
	{
	public:
		Material(Texture *albedoMap = nullptr, Texture *normalMap = nullptr, Texture *metallicMap = nullptr, Texture *roughnessMap = nullptr,
			Texture *ambientOcclusionMap = nullptr);
		~Material();

		void BindMaterial(Shader *shader) const;

		inline void SetAlbedoMap(Texture *texture) { mAlbedoMap = texture; }
		inline void SetNormalMap(Texture *texture) { mNormalMap = texture; }
		inline void SetMetallicMap(Texture *texture) { mMetallicMap = texture; }
		inline void SetRoughnessMap(Texture *texture) { mRoughnessMap = texture; }
		inline void SetAmbientOcclusionMap(Texture *texture) { mAOMap = texture; }

	private:
		// TODO: remember to release this texture inside or outside
		Texture *mAlbedoMap;
		Texture *mNormalMap;
		Texture *mMetallicMap;
		Texture *mRoughnessMap;
		Texture *mAOMap;

	};
}