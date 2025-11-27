#pragma once

#ifndef _MESH_H_
#define _MESH_H_

#include "StandardIncludes.h"
#include "Texture.h"
#include "Shader.h"
#include "OBJ_Loader.h"

class Mesh
{
public:
	~Mesh();

	void SetPosition(glm::vec3 _position) { position = _position; }
	glm::vec3 GetPosition() { return position; }
	void SetScale(glm::vec3 _scale) { scale = _scale; }
	void SetRotation(glm::vec3 _rotation) { rotation = _rotation; }
	glm::vec3 GetRotation() { return rotation; }
	float GetRotationRate() { return rotationRate; }

	void SetLightColor(glm::vec3 _lightColor) { lightColor = _lightColor; }
	glm::vec3 GetLightColor() { return lightColor; }
	void SetLightDirection(glm::vec3 _lightDirection) { lightDirection = _lightDirection; }
	glm::vec3 GetLightDirection() { return lightDirection; }

	glm::vec3 GetAmbientColor() { return ambientColor; }
	glm::vec3 GetSpecularColor() { return specularColor; }
	float GetSpecularStrength() { return specularStrength; }

	float GetPointLightConstant() { return pointLightconstant; }
	float GetPointLightLinear() { return pointLightlinear; }
	float GetPointLightQuadratic() { return pointLightquadratic; }

	float GetConeAngle() { return spotLightconeAngle; }
	float GetFalloff() { return spotLightfalloff; }

	void SetCameraPosition(glm::vec3 _cameraPosition) { cameraPosition = _cameraPosition; };

	int GetInstanceCount() { return instanceCount; }

	void Create(json::JSON& jsonData);
	void CalculateTransform();
	void SetShader(Shader* _shader) { shader = _shader; };
	void Render(glm::mat4 _pv, const std::list<Mesh*>& _lights, int count = 0);

private:
	Shader* shader = nullptr;
	std::string diffuseMap = "";
	std::string specularMap = "";
	std::string normalMap = "";
	std::string lightType = "";
	Texture* diffuseTexture = nullptr;
	Texture* specularTexture = nullptr;
	Texture* normalTexture = nullptr;
	GLuint vertexBuffer = 0;
	GLuint indexBuffer = 0;
	GLuint instanceBuffer = 0;
	std::vector<GLfloat> vertexData;
	std::vector<GLubyte> indexData;

	int vertexStride = 8;
	int instanceCount = 0;
	bool enableNormalMaps = false;
	bool enableInstancing = false;
	glm::mat4* instanceData;

	glm::mat4 world = glm::mat4(1);
	glm::vec3 position{ 0.0f, 0.0f, 0.0f };
	glm::vec3 rotation{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale{ 1.0f, 1.0f, 1.0f };

	glm::vec3 lightDirection{ 0.0f, 0.0f, 0.0f };
	glm::vec3 lightColor{ 1.0f, 1.0f, 1.0f };
	glm::vec3 ambientColor{ 0.1f, 0.1f, 0.1f };
	glm::vec3 specularColor{ 0.1f, 0.1f, 0.1f };
	float specularStrength = 1.0f;
	float rotationRate = 0.0f;

	float pointLightconstant = 1.0f;
	float pointLightlinear = 0.0f;
	float pointLightquadratic = 0.0f;

	float spotLightconeAngle = 90.0f;
	float spotLightfalloff = 1.0f;

	glm::vec3 cameraPosition{ 0, 0, 0 };

	glm::vec2 texTranslation = glm::vec2(0.0);

	void LoadOBJ(const std::string& _file);
	void SetShaderVariables(glm::mat4 _pv, const std::list<Mesh*>& _lights);
	void BindAttributes();
	std::string Concat(const std::string& _s1, int _index, const std::string& _s2);
	std::string RemoveFolder(std::string& _map);
	void CalculateTangents(std::vector<objl::Vertex> _vertices, objl::Vector3& _tangent, objl::Vector3& _bitangent);

	void LoadVec3(json::JSON& jsonData, const char* name, glm::vec3& vec);
};

#endif

