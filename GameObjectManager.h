#pragma once
#include "AGameObject.h"
class GameObjectManager
{
private:
	GameObjectManager();
	~GameObjectManager();
private:
	int width = 0;
	int height = 0;
public:
	vector<bool> selectedObjList;
	vector<AGameObject*> objList;
	vector<AGameObject*> mergedObjList;
	bool merge;
	bool instantiate;
	AGameObject* selectedObject = nullptr;
public:
	static GameObjectManager* get();
public:
	void updateObjects();
	void initialize();
	void createPhysicsCube();
	void createCube();
	void createCube(string name, string type, string rbType, Vector3D position, Vector3D scale, Vector3D rotation);
	void createPlane(string name, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation);
	void createSphere(string name, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation);
	void createCapsule(string name, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation);
	void createPhysicsSphere();
	void createPhysicsCapsule();
	void createPhysicsCubes();
	void createPlane();
	void changePosition(int i, float x, float y, float z);
	void mergeSelected();
	void instantiateMergedActor(int i);
	void enableBox(int index, bool isEnable);
	void changeBoxScale(int i, float x, float y, float z);
	vector<AGameObject*> getAllObjects();
	void selectObject(AGameObject* obj);
	void createObjectFromFile(string name, string type, string hasRigid, string rbType, Vector3D position, Vector3D scale, Vector3D rotation);
private:
	void initalizePlayerStart();

	void* shaderByteCode = nullptr;
	size_t sizeShader = 0;
};

