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
    return this->sceneCamera->getViewMatrix();
}

Matrix4x4 SceneCameraHandler::getSceneCameraWorldCam()
{
    return this->sceneCamera->getWorldCamMatrix();
}

Camera* SceneCameraHandler::getSceneCamera()
{
    return this->sceneCamera;
}

SceneCameraHandler::SceneCameraHandler()
{
    this->sceneCamera = new Camera("SceneCamera");
}
SceneCameraHandler::~SceneCameraHandler()
{
    delete this->sceneCamera;
}
