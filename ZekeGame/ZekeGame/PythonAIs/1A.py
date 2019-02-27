#coding: utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    mon = cb.GetEnemyHighHPMonster()
    
    cb.Chase(mon)
    cb.Attack(mon)

    cb.End()
