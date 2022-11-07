#include "SceneCameraHandler.h"
#include "EngineTime.h"

SceneCameraHandler* SceneCameraHandler::sharedInstance = NULL;

SceneCameraHandler* SceneCameraHandler::getInstance()
{
    return sharedInstance;
}

void SceneCameraHandler::initialize()
{
    sharedInstance = new SceneCameraHandler();
}

void SceneCameraHandler::destroy()
{
    delete sharedInstance;
}

void SceneCameraHandler::update()
{
    this->sceneCamera->update(EngineTime::getDeltaTime());
}

Matrix4x4 SceneCameraHandler::getSceneCameraViewMatrix()
{
    return this->sceneCamera->getVMatrix();
}

Matrix4x4 SceneCameraHandler::getSceneCameraWorldCamMatrix()
{
    return this->sceneCamera->getViewMatrix();
}

Camera* SceneCameraHandler::getSceneCamera()
{
    return this->sceneCamera;
}

void SceneCameraHandler::SetSceneCamera(Camera* objCamera)
{
    if (sceneCamera)
    this->sceneCamera->setCameraStatus(false);
    this->sceneCamera = objCamera;
    this->sceneCamera->setCameraStatus(true);
}

SceneCameraHandler::SceneCameraHandler()
{
    this->sceneCamera = new Camera("SceneCamera");

}

SceneCameraHandler::~SceneCameraHandler()
{
    delete this->sceneCamera;
}
