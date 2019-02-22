#pragma once

enum Target
{
	tNone,
	me = 100,
	buddy,
	enemy,
};
enum What
{
	wNone,
	hp = 200,
	mp,
	state = 300,
	action = 400,
};
enum BL
{
	bNone,
	big = 210,
	little
};
enum Num
{
	nNone,
	n1 = 220,
	n10,
	n30,
	n50,
	n70,
	n90,
	n100
};

enum State
{
	sNone,
	doku = 310,
	bili,
};

enum Action
{
	aNone,
	attack = 410,
	leave,
	chase,
	defence,
	recovery,
	ex1,
	ex2,
};

struct VisualScriptOrder
{
	Target target = tNone;
	What what = wNone;
	BL bl = bNone;
	Num num = nNone;
	State state = sNone;
	Action action = aNone;
};
typedef std::vector<VisualScriptOrder> VisualScriptLine;

class Monster;
class VisualScriptAI
{
public:
	VisualScriptAI();
	~VisualScriptAI();
	void Run();
	bool whatHP(Target target, BL bl, Num num, Monster* &mon,Target old);
	bool whatMP(Target target, BL bl, Num num, Monster* &mon, Target old);
	bool whatState(Target target, State state, Monster* &mon, Target old);
	void whatAction(Target target, Action action);
	void whatAction(Monster* target, Action action);
private:
	std::vector<VisualScriptLine> m_vsLines;
	Monster* m_me = nullptr;
};