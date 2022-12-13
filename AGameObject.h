#pragma once
#include <string>
#include "Vector2D.h"
#include "Vector3D.h"
#include "Matrix4x4.h"

#include "TVertexBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "ConstantBuffer.h"

#include "VertexShader.h"
#include "PixelShader.h"

#include "AComponent.h"
#include "reactphysics3d/reactphysics3d.h"
#include "PhysicsComponent.h"

#include"Prerequisites.h"
#include <vector>

using namespace std;
using namespace reactphysics3d;


//class VertexShader;
//class PixelShader;
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

	string gameObjectType;
	bool hasRigidBody = false;
	string rbType;


	typedef string String;
	//typedef std::vector<AComponent*>; ComponentList;

	void attachComponent(AComponent* component);
	void detachComponent(AComponent* component);

	AComponent* findComponentByName(String name);
	AComponent* findComponentOfType(AComponent::ComponentType type, String name);
	vector<AComponent*> getComponentsOfType(AComponent::ComponentType type);
	vector<AComponent*> getComponentsOfTypeRecursive(AComponent::ComponentType type);

	void updateLocalMatrix();

	void setLocalMatrix(float matrix[16]);
	bool isSelected = false;

	PhysicsComponent* physicsComponent = nullptr;



public:

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

	struct TVertex {
		Vector3D position;
		Vector2D texcoord;
	};

protected:
	string name;
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;
	Matrix4x4 localMatrix;

	vector<AComponent*> componentList;

	VertexBuffer* vertexBuffer;
	TVertexBuffer* tVertexBuffer;
	IndexBuffer* indexBuffer;
	ConstantBuffer* constantBuffer;

	VertexShader* vertexShader;
	PixelShader* pixelShader;

	bool overwriteMatrix = false;


};