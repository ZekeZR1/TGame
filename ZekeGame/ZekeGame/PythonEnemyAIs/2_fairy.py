#coding: utf-8

import CppBridge as cb

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,2)
	mon = cb.GetBuddyNeerMonster()
	cb.addAction(mon,7)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,4)
	cb.End()