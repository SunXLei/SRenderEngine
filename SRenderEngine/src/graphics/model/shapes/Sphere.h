#pragma once

#include "../Mesh.h"

namespace sre
{

	class Sphere : public Mesh
	{
	public:
		Sphere(int xSegments = 30, int ySegments = 30);
		~Sphere();
	};

}
