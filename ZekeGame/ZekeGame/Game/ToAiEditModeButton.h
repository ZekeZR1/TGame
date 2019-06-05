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
	CVector3 pos = { -600, 240,0 };
	CVector3 tar = CVector3::Zero();
	Fade* m_fade = nullptr;
	bool fade = false;
	GameObject* m_scene = nullptr;
};

