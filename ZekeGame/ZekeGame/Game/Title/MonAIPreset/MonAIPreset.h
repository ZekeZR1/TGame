#pragma once


class MonAIPreset :public GameObject
{
public:
	bool Start();
	void Update();

private:
	FontRender* m_fonts[6] = {nullptr};
	SpriteRender* m_prsp[6] = { nullptr };

	FontRender* m_fclose = nullptr;
};