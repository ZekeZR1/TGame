#pragma once


struct VisualAIState
{
	std::string file;
	int num = 0;
	CVector4 col = CVector4::White;
	int mark = 0;
};



class VisualAIOpen
{
public:
	//visualAIÇäJÇ≠
	static std::vector<VisualAIState> openVAs();

	static CVector4 Red()
	{
		return mRed;
	}
	static CVector4 Blu()
	{
		return mBlu;
	}
	static CVector4 Yel()
	{
		return mYel;
	}
	static CVector4 Whi()
	{
		return mWhi;
	}

	static const wchar_t* getMark(int m)
	{
		switch (m)
		{
		case 0:
			return L"Assets/sprite/aimk_attack.dds";
		case 1:
			return L"Assets/sprite/aimk_defense.dds";
		case 2:
			return L"Assets/sprite/aimk_heal.dds";
		case 3:
			return L"Assets/sprite/aimk_magic.dds";
		}
	}

private:
	static CVector4 mRed;	//ê‘
	static CVector4 mBlu;	//ê¬
	static CVector4 mYel;	//â©
	static CVector4 mWhi;	//îí
};

