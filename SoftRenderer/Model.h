#pragma once
#include <RTRMath.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Drawable.h"
#include "Texture.h"
namespace RTR {
	class Application;
	class Model: public Drawable
	{
	public:
		void load(const std::string& filename);
		void setApplication(Application* a) {
			app = a;
		}
		Vector3f normal(int iface, int nthvert) {
			return normals[faces[iface][nthvert][2]];
		}
		Vector3f vert(int iface, int nthvert) {
			return vertices[faces[iface][nthvert][0]];
		}

		Vector2f texCoord(int iface, int nthvert) {
			return texCoords[faces[iface][nthvert][1]];
		}



		// Inherited via Drawable
		virtual void draw() override;


		std::vector<Vector3f> vertices;
		std::vector<Vector2f> texCoords;
		std::vector<Vector3f> normals;
		std::vector<std::vector<Vector3i>> faces;

		Texture diffuseTexture;

		Application* app;
	};
}

