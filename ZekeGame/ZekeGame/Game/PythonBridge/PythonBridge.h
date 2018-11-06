#pragma once

class PythonBridge
{
public:
	void SetVec1(CVector3 v)
	{
		g_vec1 = v;
	}
	CVector3 GetVec1()
	{
		return g_vec1;
	}
private:
};

static CVector3 g_vec1;