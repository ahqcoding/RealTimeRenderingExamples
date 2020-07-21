#include "Model.h"
#include "Application.h"
void RTR::Model::load(const std::string& filename)
{
    std::ifstream in;
    in.open(filename + ".obj", std::ifstream::in);
    if (in.fail()) return;
    std::string line;
    while (!in.eof()) {
        std::getline(in, line);
        std::istringstream iss(line.c_str());
        char trash;
        if (!line.compare(0, 2, "v ")) {
            iss >> trash;
            Vector3f v;
            for (int i = 0; i < 3; i++) iss >> v[i];
            vertices.push_back(v);
        }
        else if (!line.compare(0, 3, "vn ")) {
            iss >> trash >> trash;
            Vector3f n;
            for (int i = 0; i < 3; i++) iss >> n[i];
            normals.push_back(n);
        }
        else if (!line.compare(0, 3, "vt ")) {
            iss >> trash >> trash;
            Vector2f uv;
            for (int i = 0; i < 2; i++) iss >> uv[i];
            texCoords.push_back(uv);
        }
        else if (!line.compare(0, 2, "f ")) {
            std::vector<Vector3i> f;
            Vector3i tmp;
            iss >> trash;
            while (iss >> tmp[0] >> trash >> tmp[1] >> trash >> tmp[2]) {
                for (int i = 0; i < 3; i++) tmp[i]--; // in wavefront obj all indices start at 1, not zero
                f.push_back(tmp);
            }
            faces.push_back(f);
        }
    }
    std::cerr << "# v# " << vertices.size() << " f# " << faces.size() << " vt# " << texCoords.size() << " vn# " << normals.size() << std::endl;
    diffuseTexture.load(filename + "_diffuse.tga");

}

void RTR::Model::draw()
{
    Vertex triangle[3];
    Vector4f points[3];
    app->getShader()->textures.insert(std::make_pair("diffuse", &diffuseTexture));
    for (std::size_t f = 0; f < faces.size(); f++) {
        for (std::size_t n = 0; n < 3; n++) {
            triangle[n].position = vert(f, n);
            triangle[n].uv = texCoord(f, n);
            triangle[n].normal = normal(f, n);
            points[n] = app->getShader()->vertex(triangle[n], n);
        }
        app->getRaster()->rasterizeTriangle(points);
    }
}
