#pragma once

#include <vector>
#include <string>

#include "./Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>

namespace sre
{
	class Model
	{
	public:
		Model(const std::string& path);
		Model(const Mesh &mesh);
		Model(const std::vector<Mesh> &meshes);
		~Model();

		void Draw(Shader *shader, bool isUseMaterial) const;

	private:
		void LoadModel(const std::string& path);

		void ProcessNode(aiNode *node, const aiScene *scene);
		Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
		Texture* LoadMaterialTexture(aiMaterial *mat, aiTextureType type, bool isSRGB);

	private:
		std::vector<Mesh> mMeshes;
		std::string mDirectory;
	};
}