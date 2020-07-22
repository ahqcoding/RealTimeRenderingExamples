#pragma once
#include <RTRMath.h>
#include <algorithm>
#include "Vertex.h"
#include "Texture.h"
#include <string>
#include <map>
namespace RTR {
	class Shader
	{
	public:
		Mat4 mvp;
		Mat3 normalMatrix;
		Mat4 modelViewMatrix;
		Vertex vertexs[3];
		std::map<std::string, Texture*> textures;
		
		virtual void vertex(Vertex& vertex, int index) = 0;
		virtual Vector4f fragment(Vector3f& bar) = 0;
	};

	class BlinnPhongShader : public Shader {
	public:
		virtual void vertex(Vertex& vertex, int index) override {
			vertexs[index].normal = normalMatrix * vertex.normal;
			vertexs[index].uv = vertex.uv;
			Vector4f tempPos = modelViewMatrix * Vector4f(vertex.position[0],
				vertex.position[1], vertex.position[2], 1.0f);
			vertexs[index].viewPos = Vector3f(tempPos[0], tempPos[1], tempPos[2]);
			vertexs[index].position =  mvp * Vector4f(vertex.position[0], vertex.position[1], vertex.position[2], 1.0);
		}

		virtual Vector4f fragment(Vector3f& bar) {
			
			Vector2f texCoord = vertexs[0].uv * bar[0] + vertexs[1].uv * bar[1] + vertexs[2].uv * bar[2];
			Vector3f viewPos = vertexs[0].viewPos * bar[0] + vertexs[1].viewPos * bar[1] + vertexs[2].viewPos * bar[2];
			Vector3f normal = vertexs[0].normal * bar[0] + vertexs[1].normal * bar[1] + vertexs[2].normal * bar[2];
			// temporary hard code light to vec3(0, 0, 0)
			Vector3f s = viewPos * -1;
			float sDotN = std::max(s.dot(normal), 0.0f);
			
			Vector4f diffuse = textures.at("diffuse")->getUV(texCoord.x, texCoord.y);
			Vector4f spec = Vector4f(0.0, 0.0, 0.0, 1.0);

			

			if (sDotN > 0.0) {

				// temporary har code camera pos (0, 0, 0);
				Vector3f v = s.normal();
				Vector3f h = (v + s).normal();
				spec = diffuse * pow(std::max(h.dot(normal), 0.0f), 128);
			}

			return diffuse + spec;
		}
	};
}


