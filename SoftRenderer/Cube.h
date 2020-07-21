#pragma once
#include "TriangleMesh.h"
namespace RTR {
	class Cube : public TriangleMesh
	{
	public:
		Cube(float size = 1.0f);

		virtual void draw() override;

		
	};
}


