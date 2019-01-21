#include "stdafx.h"
#include "GameCamera.h"
#include "Game/GameCamera2D.h"
#include "Game/GameCursor.h"
#include "TestScene.h"
#include "TestScene2.h"


TestScene::TestScene()
{
}


TestScene::~TestScene()
{
	DeleteGO(m_skinModel);
	DeleteGO(m_cur);
	DeleteGO(m_sp1);
	DeleteGO(m_sp2);
	DeleteGO(m_font);
	delete m_camera;
	DeleteGO(m_2dcamera);
}


bool TestScene::Start() {
	m_skinModel = NewGO<SkinModelRender>(0, "model");
	m_skinModel->Init(L"Assets/modelData/Test.cmo");
	m_skinModel->SetPosition(CVector3::Zero());
	//IGameObjectManager().AddShadowCaster(&m_skinModel->GetSkinModel());
	//m_skinModel->SetFbxUpAxis(enFbxUpAxisY);
	//CQuaternion r = CQuaternion::Identity();
	//r.SetRotationDeg(CVector3::AxisX(), 90.f);
	//m_skinModel->SetRotation(r);
	m_camera = new GameCamera;
	m_2dcamera = new GameCamera2D;
	m_camera->SetTarget(CVector3::Zero());
	CVector3 ppp = CVector3::Zero();
	ppp.z -= 3.f;

	/*m_bg = NewGO<SkinModelRender>(0, "bg");
	m_bg->Init(L"Assets/modelData/testtt.cmo");
	m_bg->SetPosition(CVector3::Zero());*/
	m_camera->SetPosition(ppp);
	m_camera->Update();
	//m_2dcamera->Update();

	m_cur = NewGO<GameCursor>(0, "cur");
	m_sp1 = NewGO<SpriteRender>(1, "sp1");
	m_sp1->Init(L"Assets/Sprite/PriTest1.dds", 300.f, 300.f);
	m_sp1->SetPosition(CVector3::Zero());
	m_sp2 = NewGO<SpriteRender>(2, "sp2");
	m_sp2->Init(L"Assets/Sprite/PriTest2.dds", 300.f, 300.f);
	m_font = NewGO<FontRender>(5, "font");
	m_font->Init(L"Test", CVector2::Zero(), 0, CVector4::White, 1.f, { 0.5f, 0.5 });
	return true;
}


void TestScene::Update() {
	if (g_pad[0].IsPress(enButtonLeft)) {
		pos.y += 10.f;
	}
	if (g_pad[0].IsPress(enButtonRight)) {
		pos.y -= 10.f;
	}
	pos.x -= g_pad[0].GetLStickXF() * 10.f;
	pos.z -= g_pad[0].GetLStickYF() * 10.f;
	CVector4 col = { 0.5f,0.5f,0.5f,1.f };
	static float n = 0.5f;
	if (g_pad[0].IsPress(enButtonRB2)) {
		n += 0.05f;
	}
	if (g_pad[0].IsPress(enButtonLB2)) {
		n -= 0.05f;
	}
	col.x = min(2.f, n);
	col.x = max(0.5f, n); 
	col.y = min(2.f, n);
	col.y = max(0.5f, n);
	col.z = min(2.f, n);
	col.z = max(0.5f, n);

	CQuaternion addrot;
	float y = -g_pad[0].GetRStickXF();
	addrot.SetRotationDeg(CVector3::AxisY(), y);
	m_rot.Multiply(addrot);
	m_skinModel->SetPosition(pos);
	CVector3 addedPos = pos;
	addedPos.x += 50.f;
	m_skinModel->SetRotation(m_rot);
	m_skinModel->SetDirLigColor(col,0);
	m_skinModel->SetDirLigColor(col,1);
	m_skinModel->SetDirLigColor(col,2);
	char nyan[256];
	int no = Mouse::GetMouseNotch();
	sprintf_s(nyan, "1...%d\n", no);
	OutputDebugStringA(nyan);

	int nn = Mouse::GetMouseNotch();
	sprintf_s(nyan, "2...%d\n", nn);
	OutputDebugStringA(nyan);

	m_camera->Update();

	if (g_pad[0].IsTrigger(enButtonA)) {
		DeleteGO(this);
		NewGO<TestScene2>(0,"TestScene2");
	}
}

void TestScene::PostRender() {
}