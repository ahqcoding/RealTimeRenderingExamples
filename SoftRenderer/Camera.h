#pragma once
#include <RTRMath.h>
namespace RTR {
	class Camera
	{
	public:
		Camera(Vector3f o, Vector3f t, Vector3f up);

		Mat4 getMat4() {
			Mat4 ret;
			
			ret[0][0] = u.x;
			ret[0][1] = u.y;
			ret[0][2] = u.z;
			ret[0][3] = - u.dot(origin);
			ret[1][0] = v.x;
			ret[1][1] = v.y;
			ret[1][2] = v.z;
			ret[1][3] = - v.dot(origin);
			ret[2][0] = -w.x;
			ret[2][1] = -w.y;
			ret[2][2] = -w.z;
			ret[2][3] = w.dot(origin);
			return ret;
		}

		Vector3f origin;
		Vector3f u, v, w;
	};
}


