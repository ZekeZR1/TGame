#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	cb.addAction(me,SendGame.DEF_Buff)
	cb.addAction(me,SendGame.GUARDIAN)
	mon = cb.GetEnemyHighATKMonster()
	cb.addAction(mon,SendGame.CHASE)
	cb.addAction(me,SendGame.ATK_Buff)
	mon = cb.GetNeerEnemyMonster()
	cb.addAction(mon,SendGame.ATTACK)
	cb.End()