#pragma once
#include "Vector4.h"
#include "Vector3.h"
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
			assert(i > -1 && i < 4);
			return rows[i];
		}



		static Mat4 Translation(const Vector3f& v) {
			Mat4 ret;
			ret[0][3] = v.x;
			ret[1][3] = v.y;
			ret[2][3] = v.z;
			return ret;
		}

		static Mat4 RotationX(const float& radians) {
			Mat4 ret;
			ret[1][1] = cos(radians);
			ret[1][2] = -sin(radians);
			ret[2][1] = sin(radians);
			ret[2][2] = cos(radians);
			return ret;
		}

		static Mat4 RotationY(const float& radians) {
			Mat4 ret;
			ret[0][0] = cos(radians);
			ret[0][2] = sin(radians);
			ret[2][0] = -sin(radians);
			ret[2][2] = cos(radians);
			return ret;
		}

		static Mat4 RotationZ(const float& radians) {
			Mat4 ret;
			ret[0][0] = cos(radians);
			ret[0][1] = -sin(radians);
			ret[1][0] = sin(radians);
			ret[1][1] = cos(radians);
			return ret;
		}

		static Mat4 Rotation(Vector3f& axis, const float& radians)
		{
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

