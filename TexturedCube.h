#pragma once
#include "AGameObject.h"
#include "Camera.h"
#include"Texture.h"

#include <vector>

class TexturedCube : public AGameObject
{
public:
	TexturedCube(string name, void* shaderByteCode, size_t sizeShader);
	//Cube(vector<Vertex> v1, vector<Vertex> v2, string name, void* shaderByteCode, size_t sizeShader);
	~TexturedCube();

	void update(float deltaTime) override;
	void draw(int width, int height) override;
	void setAnimSpeed(float speed);

	Texture* myTexture;
	ID3D11SamplerState* samplerState;

	//vector<Vertex> getVertexList();
private:
	float speed = 4.0f;
	float deltaTime = 0;
	Matrix4x4 m_world_matrix;
	//vector<Vertex> vertex_list_copy;
};

