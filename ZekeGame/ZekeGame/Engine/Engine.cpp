#include "stdafx.h"
#include "Engine.h"
#include "Engine/FPSCounter.h"
#include "GameCamera.h"

CFPSCounter* FPS = nullptr;
GameCamera* camera = nullptr;
NetworkLogic* m_network = nullptr;
CListener* m_listener = nullptr;

Engine::Engine()
{
}


Engine::~Engine()
{
}

void Engine::Init(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//SetCurrentDirectory("Resource");
	InitWindow(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");
	GameObjectManager().Init(32);
	FPS = new CFPSCounter(10);
	//camera = new GameCamera;
}

void Engine::Release() {
	delete g_graphicsEngine;
	delete camera;
	delete FPS;
}

void Engine::Update() {
	for (auto& pad : g_pad) {
		pad.Update();
	}

	if (m_network != nullptr) {
		m_network->update();
		m_listener->writeString(m_network->getStateString());
	}

	GameObjectManager().Execute();
	//camera->Update();
	//output frame late to debug message
	char message[256];
	float fps = FPS->GetFPS();
	sprintf_s(message, "%f\n", fps);
	OutputDebugStringA(message);
}

void Engine::CreateNetworkSystem(CListener* listener) {
	if (m_network != nullptr) {
		m_network = new NetworkLogic(listener);
		m_listener = listener;
	}
}

void Engine::DestroyNetworkSystem() {
	if (m_network != nullptr) {
		delete m_network;
		m_network = nullptr;
		m_listener = nullptr;
	}
}

void Engine::GameRoop() {
	while (DispatchWindowMessage()) {
		Update();
	}
}

void Engine::Final() {
	Release();
}

