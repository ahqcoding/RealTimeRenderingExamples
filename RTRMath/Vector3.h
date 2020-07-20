#pragma once
#include <assert.h>
#include <cmath>

namespace RTR {
	template<typename T>
	class Vector3 {
	public:
		T x;
		T y;
		T z;
		Vector3()
			: x(0)
			, y(0)
			, z(0)
		{

		}

		Vector3(T _x, T _y, T _z)
			: x(_x)
			, y(_y)
			, z(_z) 
		{

		}

		T& operator[](size_t i) {
			assert(i == 0 || i == 1 || i == 2);
			return i == 0 ? x : i == 1 ? y : z;
		}

		Vector3 operator+(const Vector3& v) {
			return Vector3(x + v.x, y + v.y, z + v.z);
		}

		Vector3 operator-(const Vector3& v) {
			return Vector3(x - v.x, y - v.y, z - v.z);
		}

		Vector3 operator*(const Vector3& v) {
			return Vector3(x * v.x, y * v.y, z * v.z);
		}

		Vector3 operator/(const Vector3& v) {
			assert(v.x != 0 && v.y != 0 && v.z != 0);
			return Vector3(x / v.x, y / v.y, z / v.z);
		}
		Vector3 operator*(T s) {
			return Vector3(x * s, y * s, z * s);
		}

		Vector3 operator/(T s) {
			assert(s != 0);
			T s_1 = 1.0 / s;
			return (*this) * s_1;

		}
	
		T dot(const Vector3& v) {
			return x * v.x + y * v.y + z * v.z;
		}

		Vector3 cross(const Vector3& v) {
			T _x = y * v.z - z * v.y;
			T _y = z * v.x - x * v.z;
			T _z = x * v.y - y * v.x;
			return Vector3(_x, _y, _z);
		}

		float lengthSqr() {
			return x * x + y * y + z * z;
		}

		float length() {
			return sqrt(lengthSqr());
		}

		Vector3 normal() {
			assert(lengthSqr() > 0);
			return (*this) / length();
		}
	};

	typedef Vector3<float> Vector3f;
	typedef Vector3<int> Vector3i;
}


