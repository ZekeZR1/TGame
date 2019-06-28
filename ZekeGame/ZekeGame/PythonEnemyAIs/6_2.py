#coding:utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    if me.ID == cb.SendGame.Yose:
        LHP = cb.GetBuddyLowHPMonster()
        if LHP.HP <= 30 or (LHP.ID == cb.SendGame.Kikyo and LHP.HP < 50):
            cb.SendGame.addAction(LHP.num,cb.SendGame.HEAL)
            cb.SendGame.addAction(LHP.num,cb.SendGame.HEAL)
            cb.SendGame.addAction(LHP.num,cb.SendGame.ESCAPE)
        else:
            tar = cb.GetEnemyFarMonster()
            cb.SendGame.addAction(tar.num,cb.SendGame.FIRE)
            #cb.SendGame.addAction(LHP.num,cb.SendGame.CHASE)
        
    elif me.ID == cb.SendGame.Kikyo:
        if me.MP <= 50:
            cb.SendGame.addAction(me.num,cb.SendGame.MP_Heal)
        tar = cb.GetEnemyNeerMonster()
        cb.SendGame.addAction(tar.num,cb.SendGame.SUPER_BEAM)
        
    else:
        tar = cb.GetEnemyFarMonster()
        if me.MP > 20:
            cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        elif meMP > 15:
            cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
            cb.SendGame.addAction(tar.num,cb.SendGame.Majinken)
        cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        

    cb.End()
