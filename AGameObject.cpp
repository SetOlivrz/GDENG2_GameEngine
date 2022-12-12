#include "AGameObject.h"

AGameObject::AGameObject(string name)
{
	this->name = name;
	this->localRotation = Vector3D(0,0,0);
	this->localPosition = Vector3D(0, 0, 0);
	this->localScale = Vector3D(1, 1, 1);
}

AGameObject::~AGameObject()
{
}

void AGameObject::draw(int width, int height)
{
}

void AGameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void AGameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

void AGameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void AGameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}


void AGameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void AGameObject::setScale(Vector3D rot)
{
	this->localScale = rot;
}



Vector3D AGameObject::getLocalPosition()
{
	return this->localPosition;
}

Vector3D AGameObject::getLocalRotation()
{
	return this->localRotation;
}

Vector3D AGameObject::getLocalScale()
{
	return this->localScale;
}


string AGameObject::getName()
{
	return this->name;
}

void AGameObject::attachComponent(AComponent* component)
{
	this->componentList.push_back(component);
	component->attachOwner(this);
}

void AGameObject::detachComponent(AComponent* component)
{
	int index = -1;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i] == component) {
			index = i;
			break;
		}
	}
	if (index != -1) {
		this->componentList.erase(this->componentList.begin() + index);
	}
}

AComponent* AGameObject::findComponentByName(String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name) {
			return this->componentList[i];
		}
	}

	return NULL;
}

AComponent* AGameObject::findComponentOfType(AComponent::ComponentType type, String name)
{
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getName() == name && this->componentList[i]->getType() == type) {
			return this->componentList[i];
		}
	}

	return NULL;
}

vector<AComponent*> AGameObject::getComponentsOfType(AComponent::ComponentType type)
{
	vector<AComponent*>  foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

vector<AComponent*>  AGameObject::getComponentsOfTypeRecursive(AComponent::ComponentType type)
{
	vector<AComponent*>  foundList;
	for (int i = 0; i < this->componentList.size(); i++) {
		if (this->componentList[i]->getType() == type) {
			foundList.push_back(this->componentList[i]);
		}
	}

	return foundList;
}

void AGameObject::updateLocalMatrix()
{
	//setup transformation matrix for drawing.
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();  translationMatrix.setTranslation(this->getLocalPosition());
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->getLocalScale());
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	//rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	rotMatrix *= zMatrix;
	rotMatrix *= yMatrix;
	rotMatrix *= xMatrix;

	allMatrix *= scaleMatrix;
	allMatrix *= rotMatrix;
	allMatrix *= translationMatrix;


	//allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	//allMatrix = allMatrix.multiplyTo(translationMatrix);
	this->localMatrix = allMatrix;
}

void AGameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; 
	newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);
	
	transMatrix *= newMatrix;
	scaleMatrix *= transMatrix;
	
	this->localMatrix = scaleMatrix;
}
