#include "Cube.h"
#include "Application.h"
namespace RTR {
	Cube::Cube(float side) :
        TriangleMesh()
	{
		float side2 = side / 2.0f;
        std::vector<float> p = {
            // Front
            -side2, -side2, side2, side2, -side2, side2, side2,  side2, side2,  -side2,  side2, side2,
            // Right
            side2, -side2, side2, side2, -side2, -side2, side2,  side2, -side2, side2,  side2, side2,
            // Back
            -side2, -side2, -side2, -side2,  side2, -side2, side2,  side2, -side2, side2, -side2, -side2,
            // Left
            -side2, -side2, side2, -side2,  side2, side2, -side2,  side2, -side2, -side2, -side2, -side2,
            // Bottom
            -side2, -side2, side2, -side2, -side2, -side2, side2, -side2, -side2, side2, -side2, side2,
            // Top
           -side2,  side2, side2, side2,  side2, side2, side2,  side2, -side2, -side2,  side2, -side2
        };

        std::vector<unsigned int> i = {
            0,1,2,0,2,3,
            4,5,6,4,6,7,
            8,9,10,8,10,11,
            12,13,14,12,14,15,
            16,17,18,16,18,19,
            20,21,22,20,22,23
        };

        init(&p, &i);
	}

    void Cube::draw() {
        
        for (std::size_t i = 0; i < vertices.size() / 3 - 2; i += 3) {

            Vertex triangle[3];
           
            for (int j = 0; j < 3; j++) {
                unsigned int ind = indices[i + j];
                triangle[j].position = Vector4f(vertices[ind * 3], vertices[ind * 3 + 1], vertices[ind * 3 + 2], 1.0f);
                app->getShader()->vertex(triangle[j], j);
               
            }

            app->getRaster()->rasterizeTriangle(app->getShader()->vertexs);
        }
    }
}
