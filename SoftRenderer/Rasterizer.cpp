#include "Rasterizer.h"
#include "Application.h"
#include <algorithm>
#include "Vertex.h"
namespace RTR {
	void Rasterizer::rasterizeTriangle(Vertex* vetexs)
	{
		
		for (int n = 0; n < 3; n++) {
			vetexs[n].position.x /= vetexs[n].position.w;
			vetexs[n].position.y /= vetexs[n].position.w;
			vetexs[n].position.z /= vetexs[n].position.w;
			vetexs[n].position.x = (vetexs[n].position.x + 1) / 2 * app->getWidth();
			vetexs[n].position.y = (1 - vetexs[n].position.y) / 2 * app->getHeight();
			
		}
		Vector3f v1 = Vector3f(vetexs[0].position.x, vetexs[0].position.y, vetexs[0].position.z);
		Vector3f v2 = Vector3f(vetexs[1].position.x, vetexs[1].position.y, vetexs[1].position.z);
		Vector3f v3 = Vector3f(vetexs[2].position.x, vetexs[2].position.y, vetexs[2].position.z);
		
		Vector3f faceNormal = (v2 - v1).cross(v3 - v1);
		if (faceNormal.z > 0) {
			return;
		}

		Vector2f bboxmin(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
		Vector2f bboxmax(-std::numeric_limits<float>::max(), -std::numeric_limits<float>::max());
		Vector2f clamp(app->getWidth() - 1, app->getHeight() - 1);
		Vector2f triangles[3];
		for (int i = 0; i < 3; i++) {
			triangles[i] = Vector2f(vetexs[i].position.x, vetexs[i].position.y);
		}
		for (int i = 0; i < 3; i++) {
			bboxmin.x = std::max(0.f, std::min(bboxmin.x, triangles[i].x));
			bboxmin.y = std::max(0.f, std::min(bboxmin.y, triangles[i].y));
			bboxmax.x = std::min(clamp.x, std::max(bboxmax.x, triangles[i].x));
			bboxmax.y = std::min(clamp.y, std::max(bboxmax.y, triangles[i].y));
		}

		Vector2i p;
		Vector3f bc_clip;
		Vector3f bc_screen;
		Vector4f color;
		float z;
		for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++) {
			for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++) {
				bc_screen = this->barycentric(triangles, Vector2f(p.x, p.y));
				if (bc_screen.x < 0 || bc_screen.x > 1 || bc_screen.y < 0 || bc_screen.y > 1
					|| bc_screen.z < 0 || bc_screen.z > 1) continue;
				z = 0;
				bc_clip = Vector3f(bc_screen.x / vetexs[0].position.w, bc_screen.y / vetexs[1].position.w, bc_screen.z / vetexs[2].position.w);
				bc_clip = bc_clip / (bc_clip.x + bc_clip.y + bc_clip.z);
				color = app->getShader()->fragment(bc_clip);
				
				for (int i = 0; i < 3; i++)  z += vetexs[i].position.z * bc_clip[i];
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
