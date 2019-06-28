#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	if(me.HP <= 20)
		mon = cb.GetEnemyNeerMonster()
		cb.addAction(mon,SendGame.ESCAPE)
		cb.addAction(me,SendGame.HEAL)
	mon = cb.GetEnemyHighATKMonster()
	cb.addAction(mon,SendGame.FIRE)
	mon = cb.GetBuddyLowHPMonster()
	cb.addAction(mon,SendGame.HEAL)
	cb.End()