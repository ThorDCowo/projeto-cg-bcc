#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Vertex {
    float x, y, z;
};

struct Face {
    int v1, v2, v3;
};

std::vector<Vertex> vertices;
std::vector<Face> faces;
std::vector<std::pair<int, int>> edges;

void ReadOBJ(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Erro ao abrir o arquivo " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;

        if (token == "v") {
            Vertex vertex;
            iss >> vertex.x >> vertex.y >> vertex.z;
            vertices.push_back(vertex);
        } else if (token == "f") {
            Face face;
            std::string vertexIndices;
            std::getline(iss, vertexIndices);

            std::istringstream indicesStream(vertexIndices);
            std::string index;
            int count = 0;
            while (indicesStream >> index) {
                std::istringstream indexStream(index);
                std::string vertexIndexStr;
                std::getline(indexStream, vertexIndexStr, '/');
                int vertexIndex = std::stoi(vertexIndexStr) - 1;

                if (count == 0) {
                    face.v1 = vertexIndex;
                } else if (count == 1) {
                    face.v2 = vertexIndex;
                } else if (count == 2) {
                    face.v3 = vertexIndex;
                }

                count++;
            }

            faces.push_back(face);
        }
    }

    file.close();
}

void BuildEdges() {
    for (const auto& face : faces) {
        edges.emplace_back(face.v1, face.v2);
        edges.emplace_back(face.v2, face.v3);
        edges.emplace_back(face.v3, face.v1);
    }
}

int main2() {
    std::string filename = "C:\\Users\\rht11\\OneDrive\\Documentos\\Workspace\\projeto-cg-bcc\\data\\charizard\\charizard.obj";
    ReadOBJ(filename);
    BuildEdges();

    for (const auto& edge : edges) {
        std::cout << "Aresta: " << edge.first << " - " << edge.second << std::endl;
    }

    return 0;
}