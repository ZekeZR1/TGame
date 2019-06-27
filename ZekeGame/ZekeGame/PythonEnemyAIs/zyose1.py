#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.ESCAPE)
	mon = cb.GetEnemyHighATKMonster()
	c.addAction(mon,SendGame.FIRE)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.ESCAPE)
	mon = cb.GetBuddyLowHPMonster()
	cb.addAction(mon,SendGame.HEAL)
	cb.End()	