#coding: utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    mon = cb.FindEnemyMonster(cb.FairyID)
    if mon == None:
        mon = cb.FindEnemyMonster(cb.UmataurID)
    
    cb.Chase(mon)
    cb.Attack(mon)

    cb.End()
