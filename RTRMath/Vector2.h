#pragma once
#include <cassert>
#include <cmath>
namespace RTR {
	template<typename T>
	class Vector2 {
	public:
		T x;
		T y;

		Vector2()
			: x(0)
			, y(0)
		{

		}

		Vector2(T _x, T _y)
			: x(_x)
			, y(_y)
		{

		}

		T& operator[](size_t i) {
			assert(i == 0 || i == 1);
			return i == 0 ? x : y;
		}

		Vector2 operator+(const Vector2& v) {
			return Vector2(x + v.x, y + v.y);
		}

		Vector2 operator-(const Vector2& v) {
			return Vector2(x - v.x, y - v.y);
		}

		Vector2 operator*(const Vector2& v) {
			return Vector2(x * v.x, y * v.y);
		}

		Vector2 operator/(const Vector2& v) {
			assert(v.x != 0 && v.y != 0);
			return Vector2(x / v.x, y / v.y);
		}
		Vector2 operator*(T s) {
			return Vector2(x * s, y * s);
		}

		Vector2 operator/(T s) {
			assert(s != 0);
			T s_1 = 1.0 / s;
			return (*this) * s_1;

		}

		T dot(const Vector2& v) {
			return x * v.x + y * v.y;
		}

		double lengthSqr() {
			return x * x + y * y;
		}

		double length() {
			return sqrt(this->lengthSqr());
		}

		Vector2 normal() {
			assert(lengthSqr() > 0.0);
			return (*this) / length();
		}
	};
	
}