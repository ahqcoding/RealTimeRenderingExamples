#pragma once

#include <assert.h>
#include <cmath>
namespace RTR {
	template<typename T>
	class Vector4 {
	public:
		T x;
		T y;
		T z;
		T w;

		Vector4()
			: x(0)
			, y(0)
			, z(0)
			, w(0)
		{

		}

		Vector4(T _x, T _y, T _z, T _w)
			: x(_x)
			, y(_y)
			, z(_z)
			, w(_w)
		{

		}

		T& operator[](size_t i) {
			assert(i >= 0 && i <= 3);
			return i == 0 ? x : i == 1 ? y : i == 2 ? z : w;
		}

		Vector4 operator+(const Vector4& v) {
			return Vector4(x + v.x, y + v.y, z + v.z, w + v.w);
		}

		Vector4 operator-(const Vector4& v) {
			return Vector4(x - v.x, y - v.y, z - v.z, w - v.w);
		}

		Vector4 operator*(const Vector4& v) {
			return Vector4(x * v.x, y * v.y, z * v.z, w * v.w);
		}

		Vector4 operator/(const Vector4& v) {
			assert(v.x != 0 && v.y != 0 && v.z != 0);
			return Vector4(x / v.x, y / v.y, z / v.z, w / v.z);
		}
		Vector4 operator*(T s) {
			return Vector4(x * s, y * s, z * s, w * s);
		}

		Vector4 operator/(T s) {
			assert(s != 0);
			T s_1 = 1.0 / s;
			return (*this) * s_1;

		}

	};

	typedef Vector4<float> Vector4f;
}
