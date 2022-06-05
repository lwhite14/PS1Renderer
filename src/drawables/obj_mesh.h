#pragma once

#include "triangle_mesh.h"
#include <glad/glad.h>
#include "aabb.h"

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <memory>


class ObjMesh : public TriangleMesh {
private:
    bool drawAdj;

public:
    static ObjMesh* Load(const char* fileName, bool center = false, bool genTangents = false);
    static ObjMesh* LoadWithAdjacency(const char* fileName, bool center = false);

    void Render() override;

protected:
    ObjMesh();

    Aabb bbox;

    // Helper classes used for loading
    class GlMeshData 
    {
    public:
        std::vector <GLfloat> points;
        std::vector <GLfloat> normals;
        std::vector <GLfloat> texCoords;
        std::vector <GLuint> faces;
        std::vector <GLfloat> tangents;

        void Clear() 
        {
            points.clear();
            normals.clear();
            texCoords.clear();
            faces.clear();
            tangents.clear();
        }
        void Center(Aabb& bbox);
        void ConvertFacesToAdjancencyFormat();
    };

    class ObjMeshData 
    {
    public:
        class ObjVertex 
        {
        public:
            int pIdx;
            int nIdx;
            int tcIdx;

            ObjVertex() 
            {
                pIdx = -1;
                nIdx = -1;
                tcIdx = -1;
            }

            ObjVertex(std::string& vertString, ObjMeshData* mesh);
            std::string str() 
            {
                return std::to_string(pIdx) + "/" + std::to_string(tcIdx) + "/" + std::to_string(nIdx);
            }
        };

        std::vector <glm::vec3> points;
        std::vector <glm::vec3> normals;
        std::vector <glm::vec2> texCoords;
        std::vector <ObjVertex> faces;
        std::vector <glm::vec4> tangents;

        ObjMeshData() { }

        void GenerateNormalsIfNeeded();
        void GenerateTangents();
        void Load(const char* fileName, Aabb& bbox);
        void ToGlMesh(GlMeshData& data);
    };
};
