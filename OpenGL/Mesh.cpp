#include "Mesh.h"
#include "GameController.h"
#include <OBJ_Loader.h>

Mesh::~Mesh()
{
    glDeleteBuffers(1, &vertexBuffer);
    glDeleteBuffers(1, &indexBuffer);

    delete diffuseTexture;
    delete specularTexture;

    if (instanceData != nullptr)
    {
        delete instanceData;
    }
}

void Mesh::Create(json::JSON& jsonData)
{
    M_ASSERT(jsonData.hasKey("Shader"), "Shader is required");
    shader = GameController::GetInstance().GetShader(jsonData["Shader"].ToString().c_str());

    if (jsonData.hasKey("Position")) LoadVec3(jsonData, "Position", position);
    if (jsonData.hasKey("RotationRate")) rotationRate = Get(jsonData, "RotationRate").ToFloat();
    if (jsonData.hasKey("Scale")) LoadVec3(jsonData, "Scale", scale);

    if (jsonData.hasKey("LightDirection")) LoadVec3(jsonData, "LightDirection", lightDirection);
    lightDirection = glm::normalize(lightDirection);

    if (jsonData.hasKey("LightColor")) LoadVec3(jsonData, "LightColor", lightColor);
    if (jsonData.hasKey("AmbientColor")) LoadVec3(jsonData, "AmbientColor", ambientColor);
    if (jsonData.hasKey("SpecularColor")) LoadVec3(jsonData, "SpecularColor", specularColor);
    if (jsonData.hasKey("SpecularStrength")) specularStrength = Get(jsonData, "SpecularStrength").ToFloat();

    //if (jsonData.hasKey("LightType")) lightType = Get(jsonData, "LightType").ToString();

    if (jsonData.hasKey("PointLightconstant")) pointLightconstant = Get(jsonData, "PointLightconstant").ToFloat();
    if (jsonData.hasKey("PointLightlinear")) pointLightlinear = Get(jsonData, "PointLightlinear").ToFloat();
    if (jsonData.hasKey("PointLightquadratic")) pointLightquadratic = Get(jsonData, "PointLightquadratic").ToFloat();

    if (jsonData.hasKey("SpotLightconeAngle")) spotLightconeAngle = Get(jsonData, "SpotLightconeAngle").ToFloat();
    if (jsonData.hasKey("SpotLightfalloff")) spotLightfalloff = Get(jsonData, "SpotLightfalloff").ToFloat();

    /*vertexData = {
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, -1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f
    };*/

    M_ASSERT(jsonData.hasKey("Model"), "Model file is required");
    LoadOBJ(jsonData["Model"].ToString());

    diffuseTexture = new Texture();
    if (diffuseMap.size() > 0) diffuseTexture->LoadTexture(diffuseMap.c_str());

    specularTexture = new Texture();
    if (specularMap.size() > 0) specularTexture->LoadTexture(specularMap.c_str());

    normalTexture = new Texture();
    if (normalMap.size() > 0) normalTexture->LoadTexture(normalMap.c_str());

    if (enableNormalMaps)
    {
        vertexStride += 6;
    }

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (jsonData.hasKey("InstanceCount")) instanceCount = jsonData["InstanceCount"].ToInt();
    enableInstancing = instanceCount > 0 ? true : false;

    if (enableInstancing)
    {
        glGenBuffers(1, &instanceBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer);

        srand(glfwGetTime());
        instanceData = new glm::mat4[instanceCount];
        glm::mat4* instanceMat = instanceData;
        for (unsigned int i = 0; i < instanceCount; i++)
        {
            *instanceMat = glm::mat4(1.0f);
            *instanceMat = glm::translate(*instanceMat, glm::vec3(-20 + rand() % 40, -10 + rand() % 20, -10 + rand() % 20));

            instanceMat++;
        }
        glBufferData(GL_ARRAY_BUFFER, instanceCount * sizeof(glm::mat4), instanceData, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    //indexData = {
    //    2,0,3,2,1,0
    //};

    //glGenBuffers(1, &indexBuffer);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(float), indexData.data(), GL_STATIC_DRAW);
}

void Mesh::BindAttributes()
{
#pragma region Set Vertices
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glEnableVertexAttribArray(shader->GetAttrVertices());
    glVertexAttribPointer(
        shader->GetAttrVertices(),
        3,
        GL_FLOAT,
        GL_FALSE,
        vertexStride * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(shader->GetAttrNormals());
    glVertexAttribPointer(
        shader->GetAttrNormals(),
        3,
        GL_FLOAT,
        GL_FALSE,
        vertexStride * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(shader->GetAttrTexCoords());
    glVertexAttribPointer(
        shader->GetAttrTexCoords(),
        2,
        GL_FLOAT,
        GL_FALSE,
        vertexStride * sizeof(float),
        (void*)(6 * sizeof(float))
    );

    glVertexAttrib2fv(shader->GetAttrTexTranslation(), glm::value_ptr(texTranslation));

#pragma region Bind Instancing Data
    if (enableInstancing)
    {
        glBindBuffer(GL_ARRAY_BUFFER, instanceBuffer); // Bind the vertex buffer

        // Set attribute pointers for instance matrix (4 times vec4)
        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix());
        glVertexAttribPointer(shader->GetAttrInstanceMatrix(),
            4, GL_FLOAT, GL_FALSE,  // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)0); // instance buffer offset

        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix() + 1);
        glVertexAttribPointer(shader->GetAttrInstanceMatrix() + 1,
            4, GL_FLOAT, GL_FALSE,  // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)(sizeof(glm::vec4))); // instance buffer offset

        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix() + 2);
        glVertexAttribPointer(shader->GetAttrInstanceMatrix() + 2,
            4, GL_FLOAT, GL_FALSE,  // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)(2 * sizeof(glm::vec4))); // instance buffer offset

        glEnableVertexAttribArray(shader->GetAttrInstanceMatrix() + 3);
        glVertexAttribPointer(shader->GetAttrInstanceMatrix() + 3,
            4, GL_FLOAT, GL_FALSE,  // size (4 components), type, normalized?
            sizeof(glm::mat4), // stride
            (void*)(3 * sizeof(glm::vec4))); // instance buffer offset

        glVertexAttribDivisor(shader->GetAttrInstanceMatrix(), 1);
        glVertexAttribDivisor(shader->GetAttrInstanceMatrix() + 1, 1);
        glVertexAttribDivisor(shader->GetAttrInstanceMatrix() + 2, 1);
        glVertexAttribDivisor(shader->GetAttrInstanceMatrix() + 3, 1);
    }
#pragma endregion

#pragma region Set Normal Map
    if (enableNormalMaps)
    {
        glEnableVertexAttribArray(shader->GetAttrTangents());
        glVertexAttribPointer(shader->GetAttrTangents(),
            3, GL_FLOAT, GL_FALSE,
            vertexStride * sizeof(float),
            (void*)(8 * sizeof(float)));
        glEnableVertexAttribArray(shader->GetAttrBitangents());
        glVertexAttribPointer(shader->GetAttrBitangents(),
            3, GL_FLOAT, GL_FALSE,
            vertexStride * sizeof(float),
            (void*)(11 * sizeof(float)));
    }
#pragma endregion

}

void Mesh::SetShaderVariables(glm::mat4 _pv, const std::list<Mesh*>& _lights)
{
    shader->SetMat4("World", world);
    shader->SetMat4("WVP", _pv * world);
    shader->SetVec3("CameraPosition", cameraPosition);
    shader->SetInt("EnableInstancing", enableInstancing);
    shader->SetInt("EnableNormalMaps", enableNormalMaps);

    M_ASSERT((_lights.size() <= 4), "Diffuse Shader only supports 4 lights");
    shader->SetInt("numLights", _lights.size());
    shader->SetVec3("lightColor", lightColor);
    int i = 0;
    for (auto& light : _lights)
    {
        shader->SetVec3(Concat("light[", i, "].position").c_str(), light->GetPosition());
        shader->SetVec3(Concat("light[", i, "].direction").c_str(), light->GetLightDirection());

        shader->SetVec3(Concat("light[", i, "].ambientColor").c_str(), light->GetAmbientColor());
        shader->SetVec3(Concat("light[", i, "].diffuseColor").c_str(), light->GetLightColor());
        shader->SetVec3(Concat("light[", i, "].specularColor").c_str(), light->GetSpecularColor());

        shader->SetFloat(Concat("light[", i, "].constant").c_str(), light->GetPointLightConstant());
        shader->SetFloat(Concat("light[", i, "].linear").c_str(), light->GetPointLightLinear());
        shader->SetFloat(Concat("light[", i, "].quadratic").c_str(), light->GetPointLightQuadratic());

        shader->SetFloat(Concat("light[", i, "].coneAngle").c_str(), glm::radians(light->GetConeAngle()));
        shader->SetFloat(Concat("light[", i, "].falloff").c_str(), light->GetFalloff());

        i++;
    }

    shader->SetFloat("material.specularStrength", specularStrength);
    shader->SetTextureSampler("material.diffuseTexture", GL_TEXTURE0, 0, diffuseTexture->GetTexture());
    shader->SetTextureSampler("material.specularTexture", GL_TEXTURE1, 1, specularTexture->GetTexture());
    shader->SetTextureSampler("material.normalTexture", GL_TEXTURE2, 2, normalTexture->GetTexture());
}

void Mesh::CalculateTransform()
{
    world = glm::translate(glm::mat4(1.0f), position);
    world = glm::rotate(world, rotation.y, glm::vec3(0, 1, 0));
    world = glm::rotate(world, rotation.x, glm::vec3(1, 0, 0));
    world = glm::rotate(world, rotation.z, glm::vec3(0, 0, 1));
    world = glm::scale(world, scale);
}

void Mesh::CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent)
{
    // calculate tangent/bitangent vectors of both triangles
    objl::Vector3 edge1 = _vertices[1].Position - _vertices[0].Position;
    objl::Vector3 edge2 = _vertices[2].Position - _vertices[0].Position;
    objl::Vector2 deltaUV1 = _vertices[1].TextureCoordinate - _vertices[0].TextureCoordinate;
    objl::Vector2 deltaUV2 = _vertices[2].TextureCoordinate - _vertices[0].TextureCoordinate;

    float f = 1.0f / (deltaUV1.X * deltaUV2.Y - deltaUV2.X * deltaUV1.Y);

    _tangent.X = f * (deltaUV2.Y * edge1.X - deltaUV1.Y * edge2.X);
    _tangent.Y = f * (deltaUV2.Y * edge1.Y - deltaUV1.Y * edge2.Y);
    _tangent.Z = f * (deltaUV2.Y * edge1.Z - deltaUV1.Y * edge2.Z);

    _bitangent.X = f * (-deltaUV2.X * edge1.X + deltaUV1.X * edge2.X);
    _bitangent.Y = f * (-deltaUV2.X * edge1.Y + deltaUV1.X * edge2.Y);
    _bitangent.Z = f * (-deltaUV2.X * edge1.Z + deltaUV1.X * edge2.Z);
}

void Mesh::Render(glm::mat4 _wvp, const std::list<Mesh*>& _lights, int count)
{
    glUseProgram(shader->GetProgramID());

    CalculateTransform();
    SetShaderVariables(_wvp, _lights);
    BindAttributes();

    if (enableInstancing)
    {
        glDrawArraysInstanced(GL_TRIANGLES, 0, vertexData.size() / vertexStride, count);
    }
    else
    {
        glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / vertexStride);
    }

    glDrawArrays(GL_TRIANGLES, 0, vertexData.size() / vertexStride);
    glDisableVertexAttribArray(shader->GetAttrVertices());
    glDisableVertexAttribArray(shader->GetAttrNormals());
    glDisableVertexAttribArray(shader->GetAttrTexCoords());
    glDisableVertexAttribArray(shader->GetAttrTexTranslation());
    if (enableInstancing)
    {
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix());
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix() + 1);
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix() + 2);
        glDisableVertexAttribArray(shader->GetAttrInstanceMatrix() + 3);
    }
}

std::string Mesh::Concat(const std::string& _s1, int _index, const std::string& _s2)
{
    std::string index = std::to_string(_index);
    return (_s1 + index + _s2);
}

void Mesh::LoadVec3(json::JSON& jsonData, const char* name, glm::vec3& vec)
{
    json::JSON& data = Get(jsonData, name);

    vec.x = Get(data, "r").ToFloat() ? Get(data, "r").ToFloat() : Get(data, "x").ToFloat();
    vec.y = Get(data, "g").ToFloat() ? Get(data, "g").ToFloat() : Get(data, "y").ToFloat();
    vec.z = Get(data, "b").ToFloat() ? Get(data, "b").ToFloat() : Get(data, "z").ToFloat();
}

void Mesh::LoadOBJ(const std::string& _filename)
{
    objl::Loader loader;

    M_ASSERT(loader.LoadFile(_filename) == true, "Failed to load mesh");

    for (auto& currentMesh : loader.LoadedMeshes)
    {
        std::vector<objl::Vector3> tangents;
        std::vector<objl::Vector3> bitangents;
        std::vector<objl::Vertex> triangle;
        objl::Vector3 tangent;
        objl::Vector3 bitangent;
        for (unsigned int j = 0; j < currentMesh.Vertices.size(); j += 3)
        {
            triangle.clear();
            triangle.push_back(currentMesh.Vertices[j]);
            triangle.push_back(currentMesh.Vertices[j + 1]);
            triangle.push_back(currentMesh.Vertices[j + 2]);
            CalculateTangents(triangle, tangent, bitangent);
            tangents.push_back(tangent);
            bitangents.push_back(bitangent);
        }

        for (unsigned int j = 0; j < currentMesh.Vertices.size(); j++)
        {
            vertexData.push_back(currentMesh.Vertices[j].Position.X);
            vertexData.push_back(currentMesh.Vertices[j].Position.Y);
            vertexData.push_back(currentMesh.Vertices[j].Position.Z);
            vertexData.push_back(currentMesh.Vertices[j].Normal.X);
            vertexData.push_back(currentMesh.Vertices[j].Normal.Y);
            vertexData.push_back(currentMesh.Vertices[j].Normal.Z);
            vertexData.push_back(currentMesh.Vertices[j].TextureCoordinate.X);
            vertexData.push_back(currentMesh.Vertices[j].TextureCoordinate.Y);
        
            if (loader.LoadedMaterials[0].map_bump != "")
            {
                int index = j / 3;
                vertexData.push_back(tangents[index].X);
                vertexData.push_back(tangents[index].Y);
                vertexData.push_back(tangents[index].Z);
                vertexData.push_back(bitangents[index].X);
                vertexData.push_back(bitangents[index].Y);
                vertexData.push_back(bitangents[index].Z);
            }
        }
    }

    std::string mapKd = loader.LoadedMaterials[0].map_Kd;
    if (mapKd != "")
    {
        diffuseMap = "../Assets/Textures/" + RemoveFolder(mapKd);
    }

    std::string mapKs = loader.LoadedMaterials[0].map_Kd;
    if (mapKs != "")
    {
        specularMap = "../Assets/Textures/" + RemoveFolder(mapKs);
    }

    std::string mapBump = loader.LoadedMaterials[0].map_bump;
    if (mapBump != "")
    {
        enableNormalMaps = true;
        normalMap = "../Assets/Textures/" + RemoveFolder(mapBump);
    }
}

std::string Mesh::RemoveFolder(std::string& _map)
{
    const size_t last_slash_idx = _map.find_last_of("\\/");

    if (std::string::npos != last_slash_idx)
    {
        _map.erase(0, last_slash_idx + 1);
    }

    return _map;
}