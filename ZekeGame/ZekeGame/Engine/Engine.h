#pragma once
class Engine : Noncopyable
{
private:
	Engine();
	~Engine();
public:
	void Init(HINSTANCE, HINSTANCE, LPWSTR, int);
	void Final();
	void GameRoop();
	static Engine& GetInstance() {
		static Engine* instance = nullptr;
		if (instance != nullptr) {
			instance = new Engine;
		}
		return *instance;
	}

private:
	void Update();
	void Release();
public:
	static inline Engine& IEngine()
	{
		return Engine::GetInstance();
	}
	void CreateNetworkSystem();
	void DestroyNetworkSystem();
	void SetMouseNotch(int);
};


