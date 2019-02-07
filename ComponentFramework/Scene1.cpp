#include <GL/glew.h>
#include <SDL.h>
#include <iostream>
#include "MMath.h"
#include "Window.h"
#include "Shader.h"
#include "Scene1.h"
#include "SceneEnvironment.h"
#include "Trackball.h"

#include "ObjLoader.h"

using namespace GAME;
using namespace MATH;


Scene1::Scene1(Window& windowRef) :Scene(windowRef) {

}


bool Scene1::OnCreate() {

	camera = nullptr;
	projectionMatrix.loadIdentity();
	modelViewMatrix.loadIdentity();
	normalMatrix.loadIdentity();
	float aspect = float(windowPtr->getWidth() / float(windowPtr->getHeight()));

	projectionMatrix = MMath::perspective(45.0f, aspect, 0.75f, 100.0f);

	skyboxVec.push_back(new SkyBox("posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg"));
	skyboxVec[0]->OnCreate();
	/// Load Assets: as needed 
	if (addModel("cube.obj") == false) {
		return false;
	}


	/// Create a shader with attributes
	SceneEnvironment::getInstance()->setLight(Vec3(0.0f, 3.0f, 7.0f));

	OnResize(windowPtr->getWidth(), windowPtr->getHeight());
	return true;
}


bool GAME::Scene1::addModel(const char* filename)
{
	mirrorVec.push_back(new MirrorObj(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	mirrorVec[mirrorVec.size() - 1]->OnCreate();
	mirrorVec[0]->setPos(Vec3(-3.0f, 0.0f, 0.0f));

	if (mirrorVec[mirrorVec.size() - 1]->LoadMesh(filename) == false) {
		return false;
	}

	fireVec.push_back(new FireObj(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 0.0f, 0.0f)));
	fireVec[fireVec.size() - 1]->OnCreate();
	fireVec[0]->setPos(Vec3(3.0f, 0.0f, 0.0f));

	if (fireVec[fireVec.size() - 1]->LoadMesh(filename) == false) {
		return false;
	}
	return true;
}

void Scene1::OnResize(int w_, int h_) {
	windowPtr->setWindowSize(w_, h_);
	glViewport(0, 0, windowPtr->getWidth(), windowPtr->getHeight());
	if (camera) delete camera;
	camera = new Camera(w_, h_, Vec3(0.0f, 0.0f, 10.0f));
	Camera::currentCamera = camera;
	Trackball::getInstance()->setWindowDimensions(windowPtr->getWidth(), windowPtr->getHeight());
}

void Scene1::Update(const float deltaTime) {
	for (Model* model : mirrorVec) {
		model->Update(deltaTime);
	}

	for (Model* model : fireVec) {
		model->Update(deltaTime);
	}
}

void Scene1::Render() const {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	skyboxVec[0]->Render(projectionMatrix, modelViewMatrix);

	/// Draw your scene here
	for (Model* model : mirrorVec) {
		model->Render();
	}

	for (Model* model : fireVec) {
		model->Render();
	}

	SDL_GL_SwapWindow(windowPtr->getSDLWindow());

}

void Scene1::HandleEvents(const SDL_Event& SDLEvent) {
	if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Trackball::getInstance()->onLeftMouseDown(SDLEvent.button.x, SDLEvent.button.y);
	}
	else if (SDLEvent.type == SDL_EventType::SDL_MOUSEBUTTONUP) {
		Trackball::getInstance()->onLeftMouseUp(SDLEvent.button.x, SDLEvent.button.y);
	}
	else if (SDLEvent.type == SDL_EventType::SDL_MOUSEMOTION &&
		SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
		Trackball::getInstance()->onMouseMove(SDLEvent.button.x, SDLEvent.button.y);
	}

}

Scene1::~Scene1() {
	OnDestroy();
}

void Scene1::OnDestroy() {
	/// Cleanup Assets
	if (camera) delete camera;
	for (MirrorObj* model : mirrorVec) {
		if (model) delete model;
	}

	for (FireObj* model : fireVec) {
		if (model) delete model;
	}

	for (SkyBox* model : skyboxVec) {
		if (model) delete model;
	}

}
