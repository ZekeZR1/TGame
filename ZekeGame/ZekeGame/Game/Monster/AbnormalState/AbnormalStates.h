#pragma once

class Monster;
class ACTEffectGrant;
class AbnormalStates
{
public:
	static void Poison(Monster* tar);
	static void Stan(Monster* tar);
	static void Burn(Monster* tar);
};