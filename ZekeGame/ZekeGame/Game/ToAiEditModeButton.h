#pragma once
class Fade;
class ToAiEditModeButton : public GameObject
{
public:
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
	void SetTarget(CVector3 t) {
		tar = t;
	}
	void SetCurrentScene(GameObject* scene) {
		m_scene = scene;
	}
	bool isFading() {
		return fade;
	}
private:
	SpriteRender* sp = nullptr;
	const CVector3 defpos = { -650, 240,0 };
	const CVector3 selpos = { -640, 240,0 };
	const CVector3 deffpos = { -615, 330,0 };
	const CVector3 selfpos = { -615 + 10, 330,0 };
	CVector3 tar = CVector3::Zero();
	Fade* m_fade = nullptr;
	bool fade = false;
	GameObject* m_scene = nullptr;
	FontRender* m_font = nullptr;
};

