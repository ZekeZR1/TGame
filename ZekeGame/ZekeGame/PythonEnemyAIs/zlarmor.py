#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	me = cb.GetMe()
	cb.addAction(me,SendGame.DEF_Buff)
	cb.addAction(me,SendGame.GUARDIAN)
	mon = cb.GetBuddyNeerMonster()
	cb.addAction(mon,SendGame.ATK_Buff)
	mon = cb.GetEnemyHighATKMonster()
	cb.addAction(mon,SendGame.CHASE)
	cb.addAction(me,SendGame.ATK_Buff)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.ATTACK)
	cb.End()
