#pragma once

#include "Drawable.h"
#include <RTRMath.h>
#include <vector>
#include <memory>
namespace RTR {
	class Application;
	class TriangleMesh : public Drawable
	{
	public:
		TriangleMesh() {

		}
		// Inherited via Drawable
		virtual void draw() override;
		virtual void setApplication(Application* a) {
			app = a;
		}
		void init(std::vector<float>* verts, std::vector<unsigned int>* ins);
	protected:
		
		std::vector<float> vertices;
		std::vector<unsigned int> indices;

		Application* app;
	};
}


