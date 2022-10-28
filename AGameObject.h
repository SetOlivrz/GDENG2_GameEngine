#pragma once
#include <string>
#include "Vector3D.h"
#include "Matrix4x4.h"

using namespace std;

class VertexShader;
class PixelShader;
class AGameObject
{
public:
	AGameObject(string name);
	~AGameObject();

	virtual void update(float deltaTime) = 0;
	virtual void draw(int width, int height) = 0;

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	void setScale(float x, float y, float z);
	void setScale(Vector3D rot);
	Vector3D getLocalPosition();
	Vector3D getLocalRotation();

	Vector3D getLocalScale();


	string getName();


	_declspec(align(16)) //make CBData a size of 16-bytes.
		struct Constant {
		Matrix4x4 worldMatrix;
		Matrix4x4 viewMatrix;
		Matrix4x4 projMatrix;
		//unsigned int m_time; //size of only 4 bytes. this won't align in GPU device because device requires 16 bytes.
		float m_time;
	};

	struct Vertex {
		Vector3D position;
		Vector3D color;
		Vector3D color2;
	};

protected:
	string name;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
	Matrix4x4 localMatrix;

};