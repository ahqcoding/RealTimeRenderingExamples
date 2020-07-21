#include "Camera.h"

RTR::Camera::Camera(Vector3f o, Vector3f target, Vector3f up)
	:origin(o)
{

	w = (target - o).normal();
	u = w.cross(up).normal();
	v = u.cross(w);
}
