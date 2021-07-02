#pragma once

#include <vector>
#include <string>

#include "./Mesh.h"

namespace sre
{
	class Model
	{
	public:
		Model(const std::string& path);
		~Model();

	private:
		void LoadModel(const std::string& path);
		void ProcessNode();
		Mesh ProcessMesh();

	private:
		std::vector<Mesh> mMeshes;
		std::string mDirectory;
	};
}