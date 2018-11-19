#include "stdafx.h"
#include "Game.h"
#include "GameCamera.h"
#include "GameData.h"


#include "PythonBridge/PythonBridge.h"
#include "Monster/MonsterActionManeger.h"
#include "Monster/Monsters/TestMons.h"

Game::Game()
{
}


Game::~Game()
{
	DeleteGO(m_model);
	DeleteGO(m_sprite);
	Engine::IEngine().DestroyNetworkSystem();
}

bool Game::Start() {
	PythonBridge* pb = NewGO<PythonBridge>(0, "PB");
	ss = new StageSetup();

	NewGO<MonsterActionManeger>(0, "MAM");
	m_model = NewGO<SkinModelRender>(0, "model");
	m_model->Init(L"Assets/modelData/map.cmo");
	m_model->SetPosition(CVector3::Zero());


	//Animation Test
	/*m_ringo = NewGO<SkinModelRender>(0, "ringo");
	m_animationClips[0].Load(L"Assets/modelData/move.tka");
	m_ringo->Init(L"Assets/modelData/ringochan.cmo", m_animationClips, 1, enFbxUpAxisZ);
	m_ringo->SetPosition(CVector3::Zero());
	m_ringo->InitAnimation(m_animationClips, 1);
	m_ringo->PlayAnimation(1);*/

	//m_ringo.Init(L"Assets/modelData/ringochan.cmo");
	//m_ringo.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	//m_animationClips[0].Load(L"Assets/modelData/move.tka");
	//m_animationClips[0].SetLoopFlag(true);
	//m_animation.Init(m_ringo, m_animationClips, 0);
	//
	//TODO : ringo animation test
	m_ringo.Init(L"Assets/modelData/unityChan.cmo",enFbxUpAxisY);
	m_ringo.UpdateWorldMatrix(CVector3::Zero(), CQuaternion::Identity(), CVector3::One());
	m_animationClips[0].Load(L"Assets/modelData/walk.tka");
	m_animationClips[0].SetLoopFlag(true);
	m_animation.Init(
		m_ringo,
		m_animationClips,
		2);	
	//
	/*TestMons* tm = NewGO<TestMons>(0, "monster");
	tm->Setnum(1);
	tm->SetpyFile("testBrain1");

	TestMons* tm2 = NewGO<TestMons>(0, "monster");
	tm2->Setpos({ 600,0,600 });

	TestMons* tm3 = NewGO<TestMons>(0, "monster");
	tm3->Setpos({ -600,0,650 });
	tm3->Setnum(2);*/

	//pb->pbInit();

	/*m_sprite = NewGO<SpriteRender>(0,"sprite");
	m_sprite->Init(L"Assets/Sprite/Test.dds", 500.f, 500.f);
	m_sprite->SetPosition(CVector3::Zero());*/

	Engine::IEngine().CreateNetworkSystem();

	camera = new GameCamera;

	return true;
}
void Game::Update() {
	//AnimationTest
	m_animation.Play(0,1.0f);
	m_animation.Update(1.f / 30.f);
	
	m_ringo.GetSkeleton();
	m_ringo.UpdateWorldMatrix(CVector3::Zero(),CQuaternion::Identity(),CVector3::One());
	if (m_animation.IsPlaying()) {
		assert(true);
	}
	//
	static CVector3 pos = CVector3::Zero();
	if (g_pad[0].IsPress(enButtonDown)) {
		pos.x += 50.0f;
	}
	m_model->SetPosition(pos);
	camera->SetTarget(CVector3::Zero());
	camera->SetPosition({ 0.0f, 350.0f, 1000.0f });
	camera->Update();
}

void Game::Render() {
	m_ringo.Draw();
}

void Game::PostRender() {
}