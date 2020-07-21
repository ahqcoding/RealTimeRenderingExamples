#include "Rasterizer.h"
#include "Application.h"
#include <algorithm>
namespace RTR {
	void Rasterizer::rasterizeTriangle(Vector4f* vertices)
	{
		Mat4 viewport = Mat4::viewport(app->getWidth(), app->getHeight());
		for (int n = 0; n < 3; n++) {
			vertices[n].x /= vertices[n].w;
			vertices[n].y /= vertices[n].w;
			vertices[n].z /= vertices[n].w;
			vertices[n].x = (vertices[n].x + 1) / 2 * app->getWidth();
			vertices[n].y = (1 - vertices[n].y) / 2 * app->getHeight();
			
		}

		

		Vector3f v1 = Vector3f(vertices[0].x, vertices[0].y, vertices[0].z);
		Vector3f v2 = Vector3f(vertices[1].x, vertices[1].y, vertices[1].z);
		Vector3f v3 = Vector3f(vertices[2].x, vertices[2].y, vertices[2].z);
		Vector3f faceNormal = (v2 - v1).cross(v3 - v1);
		if (faceNormal.z > 0) {
			return;
		}

		Vector2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
		Vector2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
		Vector2f clamp(app->getWidth() - 1, app->getHeight() - 1);
		Vector2f triangles[3];
		for (int i = 0; i < 3; i++) {
			triangles[i] = Vector2f(vertices[i].x, vertices[i].y);
		}
		for (int i = 0; i < 3; i++) {
			bboxmin.x = std::max(0.f, std::min(bboxmin.x, triangles[i].x));
			bboxmin.y = std::max(0.f, std::min(bboxmin.y, triangles[i].y));
			bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, triangles[i].x));
			bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, triangles[i].y));
		}

		Vector2i p;
		for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++) {
			for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++) {
				Vector3f bc_screen = barycentric(triangles, Vector2f(p.x, p.y));
				if (bc_screen.x < 0 || bc_screen.x > 1 || bc_screen.y < 0 || bc_screen.y > 1
					|| bc_screen.z < 0 || bc_screen.z > 1) continue;
				float z = 0;
				Vector3f bc_clip = Vector3f(bc_screen.x / vertices[0].w, bc_screen.y / vertices[1].w, bc_screen.z / vertices[2].w);
				bc_clip = bc_clip / (bc_clip.x + bc_clip.y + bc_clip.z);
				Vector4f color = app->getShader()->fragment(bc_clip);
				
				for (int i = 0; i < 3; i++)  z += vertices[i][2] * bc_clip[i];
				if (app->getWindow()->getFrameBuffer()->getDepth(p.x, p.y) > z) {
					app->getWindow()->getFrameBuffer()->setDepth(p.x, p.y, z);
					app->getWindow()->getFrameBuffer()->setColor(p.x, p.y, color[3] * 255, color[2] * 255, color[1] * 255, color[0] * 255);
				}

			}
		}
	}

	Vector3f Rasterizer::barycentric(Vector2f* pts, Vector2f p)
	{
		Vector2f v0 = pts[1] - pts[0];
		Vector2f v1 = pts[2] - pts[0];
		Vector2f v2 = p - pts[0];
		float d00 = v0.dot(v0);
		float d01 = v0.dot(v1);
		float d11 = v1.dot(v1);
		float d20 = v2.dot(v0);
		float d21 = v2.dot(v1);
		float denom = d00 * d11 - d01 * d01;
		float v = (d11 * d20 - d01 * d21) / denom;
		float w = (d00 * d21 - d01 * d20) / denom;
		float u = 1.0f - v - w;
		return Vector3f(u, v, w);
	}

}
