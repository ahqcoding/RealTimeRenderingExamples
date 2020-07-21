#pragma once
#include <RTRMath.h>
namespace RTR {
	class Application;
	class Rasterizer
	{
	public:
		Rasterizer() {

		}
		void init(Application* a) {
			app = a;
		}

		void rasterizeTriangle(Vector4f* vertices);

		Vector3f barycentric(Vector2f* pts, Vector2f p);

	private:
		Application* app;
	};
}


