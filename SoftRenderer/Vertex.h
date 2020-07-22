#pragma once
#include <RTRMath.h>

namespace RTR {
	struct  Vertex
	{
		Vector4f position;
		Vector3f normal;
		Vector2f uv;

		Vector3f viewPos;
	};
}
