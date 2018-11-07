#pragma once

static Monster* g_mons[64];

class Monster;
class PythonBridge
{
public:
	void py_exe(Monster* meMons);
	CVector3 GetMonsVec(int num)
	{
		return g_mons[num]->Getpos();
	}
private:
};