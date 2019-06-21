#coding: utf-8

import CppBridge as cb

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,18)
	mon = cb.GetBuddyNeerMonster()
	cb.addAction(mon,3)
	mon = cb.GetBuddyNeerMonster()
	cb.addAction(mon,8)
	mon = cb.GetBuddyNeerMonster()
	cb.addAction(mon,1)
	cb.End()