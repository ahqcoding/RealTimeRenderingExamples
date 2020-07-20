#pragma once

#include <string>
#include <cassert>
#include "Vector3.h"
namespace RTR {

	class Mat3
	{
	public:
		Vector3f rows[3];

		Mat3(const Mat3& m)
		{
			rows[0] = m.rows[0];
			rows[1] = m.rows[1];
			rows[2] = m.rows[2];
		}

		Vector3f& operator[](size_t i) {
			assert(i >= 0 && i < 3);
			return rows[i];
		}

		Vector3f operator*(const Vector3f& v) {
			float x = rows[0].dot(v);
			float y = rows[1].dot(v);
			float z = rows[2].dot(v);
			return Vector3f(x, y, z);
		}


	};
}


