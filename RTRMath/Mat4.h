#pragma once
#include "Vector4.h"
#include "Vector3.h"
#include "Mat3.h"
#include <iostream>

#define RTR_PI 3.1415926
namespace RTR {
	class Mat4 {
	public:
		Mat4() {
			initIdentity();
		}

		Mat4(float v00, float v01, float v02, float v03,
			float v10, float v11, float v12, float v13,
			float v20, float v21, float v22, float v23,
			float v30, float v31, float v32, float v33)
		{
			rows[0] = Vector4f(v00, v01, v02, v03);
			rows[1] = Vector4f(v10, v11, v12, v13);
			rows[2] = Vector4f(v20, v21, v22, v23);
			rows[3] = Vector4f(v30, v31, v32, v33);
		}


		Vector4f& operator[](size_t i) {
			
			assert(i >= 0 && i < 4);
			return rows[i];
		}

		const Vector4f& operator[](const size_t i) const {
			assert(i >= 0 && i < 4);
			return rows[i];
		}

		Mat4 operator*(const Mat4& m) {
			Mat4 ret;
			
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					ret[i][j] = 0;
					for (int k = 0; k < 4; k++) {
						ret[i][j] += rows[i][k] * m[k][j];
					}
	
				}
			}
			return ret;
		}

		Vector4f operator*(const Vector4f& v) {
			float x = rows[0].dot(v);
			float y = rows[1].dot(v);
			float z = rows[2].dot(v);
			float w = rows[3].dot(v);
			return Vector4f(x, y, z, w);
		}

		Mat4 transpose() {
			Mat4 ret;
			for (int i = 0; i < 4; i++) {		
				float v0 = rows[0][i];
				float v1 = rows[1][i];
				float v2 = rows[2][i];
				float v3 = rows[3][i];
				ret.rows[i] = Vector4f(v0, v1, v2, v3);
			}
			return ret;
		}

		static Mat4 Translation(Vector3f& v) {
			Mat4 ret;
			ret[0][3] = v.x;
			ret[1][3] = v.y;
			ret[2][3] = v.z;
			return ret;
		}

		static Mat4 RotationX(float radians) {
			Mat4 ret;
			ret[1][1] = cos(radians);
			ret[1][2] = -sin(radians);
			ret[2][1] = sin(radians);
			ret[2][2] = cos(radians);
			return ret;
		}

		static Mat4 RotationY(float radians) {
			Mat4 ret;
			ret[0][0] = cos(radians);
			ret[0][2] = sin(radians);
			ret[2][0] = -sin(radians);
			ret[2][2] = cos(radians);
			return ret;
		}

		static Mat4 RotationZ(float radians) {
			Mat4 ret;
			ret[0][0] = cos(radians);
			ret[0][1] = -sin(radians);
			ret[1][0] = sin(radians);
			ret[1][1] = cos(radians);
			return ret;
		}

		static Mat4 Rotation(Vector3f& axis, float angle)
		{
			float radians = angle * RTR_PI / 180;
			Mat4 ret;
			axis = axis.normal();
			float s = sin(radians);
			float c = cos(radians);
			float oc = 1.0 - c;
			return  Mat4(oc * axis.x * axis.x + c, oc * axis.x * axis.y - axis.z * s, oc * axis.z * axis.x + axis.y * s, 0.0,
				oc * axis.x * axis.y + axis.z * s, oc * axis.y * axis.y + c, oc * axis.y * axis.z - axis.x * s, 0.0,
				oc * axis.z * axis.x - axis.y * s, oc * axis.y * axis.z + axis.x * s, oc * axis.z * axis.z + c, 0.0,
				0.0, 0.0, 0.0, 1.0);
		}

		static Mat4 Scale(Vector3f& scale)
		{
			Mat4 ret;
			ret[0][0] = scale[0];
			ret[1][1] = scale[1];
			ret[2][2] = scale[2];
			return ret;
		}

		static Mat4 Ortho(float l, float r, float t, float b, float n, float f) {
			assert(r != l &&  t != b && n != f);
			Mat4 ret;
			float qrl = 1.0f / (r - l);
			float qtb = 1.0f / (r - b);
			float qnf = 1.0f / (n - f);
			ret[0][0] = 2 * qrl;
			ret[1][1] = 2 * qtb;
			ret[2][2] = 2 * qnf;
			ret[0][3] = -(r + l) * qrl;
			ret[1][3] = -(t + b) * qtb;
			ret[2][3] = -(n + f) * qnf;
			return ret;
		}

		static Mat4 Perspective(float fov, float aspect, float n, float f) {
			assert(fov > 0);
			Mat4 ret;
			float s = tan(fov / 2.0f * RTR_PI / 180.0f);
			assert(s != 0);
			assert(n != f);
			s = 1 / s;
			float qnf = 1.0f / (n - f);
			ret[0][0] = s / aspect;
			ret[1][1] = s;
			ret[2][2] = (f + n)  * qnf;
			ret[3][3] = 0;
			ret[3][2] = -1;
			ret[2][3] = 2 * f * n * qnf;
			
			return ret;
		}

		static Mat4 viewport(float width, float height) {
			Mat4 ret;
			ret[0][0] = width / 2.f;
			ret[0][3] = (width - 1) * 0.5;
			ret[1][1] = height / 2.f;
			ret[1][3] = (height - 1) * 0.5;
			return ret;
		}
		
		static Mat3 normalMatrix(Mat4& m) {
			Mat3 ret;
			for (int i = 0; i < 3; i++) {
				for (int j = 0; j < 3; j++) {
					ret[i][j] = m[j][i];
				}
			}
			return ret;
		}


	private:

		Vector4f rows[4];
		void initIdentity() {
			rows[0][0] = 1.0f;
			rows[1][1] = 1.0f;
			rows[2][2] = 1.0f;
			rows[3][3] = 1.0f;
		}
	};

}

