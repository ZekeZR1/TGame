#pragma once

class SuperMonsterSelect :public GameObject
{
public:
	virtual bool Start() override { return true; };
	virtual void Update() override {};
	virtual void PostRender() override {};

	virtual std::vector<std::string> GetFiles() { return std::vector<std::string>(); };

};