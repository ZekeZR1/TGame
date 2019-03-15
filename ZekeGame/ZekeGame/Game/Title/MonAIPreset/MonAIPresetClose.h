#pragma once

class MonAIPresetOpen;
class MonAIPresetClose :public GameObject
{
public:
	//des
	~MonAIPresetClose();

	//Start
	bool Start();

	//‰Šú‰»ŠÖ”
	void init(MonAIPresetOpen* mapo);

	//update
	void Update();
private:
	SpriteRender* m_button = nullptr;
	FontRender* m_font = nullptr;

	MonAIPresetOpen* mapo = nullptr;
};