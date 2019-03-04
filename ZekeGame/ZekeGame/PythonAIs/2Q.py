#coding: utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    me = cb.GetMe()
    if me.ID == cb.UmataurID:
        mon = cb.GetEnemyNeerMonster()
        cb.Defense(mon)
        cb.Chase(mon)
        cb.Attack(mon)
    elif me.ID == cb.FairyID:
        if me.MP >= 5:
            mon = cb.GetBuddyLowHPMonster()
            cb.Recovery(mon)

    cb.End()