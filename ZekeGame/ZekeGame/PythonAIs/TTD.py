#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    tar = cb.GetEnemyLowHPMonster()
    if me.ID == cb.SendGame.Goblin:
        cb.SendGame.addAction(tar.num,cb.SendGame.ATK_Debuff)
        cb.SendGame.addAction(tar.num,cb.SendGame.Poison)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        pass
    elif me.ID == cb.SendGame.Kikyo:
        cb.SendGame.addAction(tar.num,cb.SendGame.SUPER_BEAM)
        lm = cb.GetBuddyLowMPMonster()
        cb.SendGame.addAction(lm.num,cb.SendGame.MP_Heal)
        pass
    elif me.ID == cb.SendGame.RedHead:
        if len(cb.gameData.Enemys) != 0:
            cb.SendGame.addAction(tar.num,cb.SendGame.Thunder)
            cb.SendGame.addAction(tar.num,cb.SendGame.Ignite)
        else:
            cb.SendGame.addAction(0,cb.SendGame.ESCAPE)
            cb.SendGame.addAction(tar.num,cb.SendGame.Thunder)
        pass
    cb.End()
