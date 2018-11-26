#include "stdafx.h"
#include "CFONT.h"



CFONT::CFONT()
{
	pSpriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	pSpriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
}


CFONT::~CFONT()
{
	delete pSpriteBatch;
	delete pSpriteFont;
}

void CFONT::Init(
	const wchar_t* text,
	CVector3 pos,
	CVector3 scale,
	CVector4 color
) {
	wcscpy(m_text, text);
	m_pos = pos;
	m_scale = scale;
	m_color = color;
}


void CFONT::Init(
	wchar_t text[256],
	CVector3 pos,
	CVector3 scale,
	CVector4 color
	) {
	wcscpy(m_text, text);
	m_pos = pos;
	m_scale = scale;
	m_color = color;
}


void CFONT::Update() {

}

void CFONT::Draw() {
	pSpriteBatch->Begin();
	pSpriteFont->DrawString(pSpriteBatch, (L"%s",m_text), DirectX::XMFLOAT2(m_pos.x, m_pos.y), m_color);
	pSpriteBatch->End();
}


CFont::CFont()
{
	m_spriteBatch = new DirectX::SpriteBatch(g_graphicsEngine->GetD3DDeviceContext());
	m_spriteFont = new DirectX::SpriteFont(g_graphicsEngine->GetD3DDevice(), L"Assets/font/myfile.spritefont");
	//m_spriteBatch = g_graphicsEngine->GetSpriteBatch();
	//m_spriteFont = g_graphicsEngine->GetSpriteFont();
	m_scaleMat.MakeScaling(
		{
			g_graphicsEngine->GetFrameBufferWidth() / static_cast<float>(g_graphicsEngine->Get2DSpaceScreenWidth()),
			g_graphicsEngine->GetFrameBufferHeight() / static_cast<float>(g_graphicsEngine->Get2DSpaceScreenHeight()),
			1.0f
		}
	);
}
CFont::~CFont()
{
}

void CFont::Begin()
{
	m_spriteBatch->Begin();
}
void CFont::End()
{
	m_spriteBatch->End();
}
void CFont::Draw(
	wchar_t const* text,
	const CVector2& position,
	const CVector4& color,
	float rotation,
	float scale,
	CVector2 pivot)
{
	Begin();
	pivot.y = 1.0f - pivot.y;
	CVector2 pos = position;
	float frameBufferHalfWidth = g_graphicsEngine->Get2DSpaceScreenWidth() * 0.5f;
	float frameBufferHalfHeight = g_graphicsEngine->Get2DSpaceScreenHeight() * 0.5f;
	pos.x += frameBufferHalfWidth;
	pos.y = -pos.y + frameBufferHalfHeight;

	m_spriteFont->DrawString(
		m_spriteBatch,
		text,
		pos.vec,
		color,
		rotation,
		DirectX::XMFLOAT2(pivot.x, pivot.y),
		scale
	);
	End();
}