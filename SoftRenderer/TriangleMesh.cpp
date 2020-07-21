#include "TriangleMesh.h"
#include "Application.h"
namespace RTR {
	void TriangleMesh::init(std::vector<float>* verts, 
		std::vector<unsigned int>* ins)
	{
		if (verts == nullptr || ins == nullptr)
		{
			return;
		}
		std::size_t i;
		for (i = 0; i < verts->size(); i++) {
			vertices.emplace_back(verts->at(i));
		}
		for (i = 0; i < ins->size(); i++) {
			indices.emplace_back(ins->at(i));
		}
	}

	void TriangleMesh::draw()
	{
		
		for (std::size_t i = 0; i < vertices.size()/3; i += 3) {
			
			
			Vertex triangle[3];
			Vector4f points[3];
			for (int j = 0; j < 3; j++) {
				unsigned int ind = indices[i + j];
				triangle[j].position = Vector3f(vertices[ind * 3], 
					vertices[ind * 3 + 1], 
					vertices[ind * 3 + 2]);
				points[j] = app->getShader()->vertex(triangle[j], j);
			}
			
			app->getRaster()->rasterizeTriangle(points);
		}
	}


}
