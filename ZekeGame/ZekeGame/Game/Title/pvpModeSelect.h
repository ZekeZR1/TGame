#pragma once

class PvPModeSelect :public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void PostRender() override;
	void LoadFiles();
private:
	std::vector<std::string> files;
};