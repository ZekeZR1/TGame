#coding:utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    
    if me.ID == cb.SendGame.Armor:
        cb.SendGame.addAction(0,cb.SendGame.GUARDIAN)

    elif me.ID == cb.SendGame.Uma:
        tar = cb.GetEnemyFarMonster()
        if me.MP >= 20:
            cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)

    elif me.ID == cb.SendGame.Yose:
        lm = cb.GetBuddyLowHPMonster()
        if lm.HP <= 20:
            cb.SendGame.addAction(lm.num,cb.SendGame.HEAL)
            cb.SendGame.addAction(lm.num,cb.SendGame.HEAL)
            uma = cb.FindBuddyMonster(cb.SendGame.Uma)
            if uma != None:
                cb.SendGame.addAction(uma.ID,cb.SendGame.CHASE)
            else:
                cb.SendGame.addAction(uma.ID,cb.SendGame.ESCAPE)
            return
        arm = cb.FindBuddyMonster(cb.SendGame.Armor)
        if arm != None:
            tar = None
            len = 9999999999
            for m in cb.gameData.Enemys:
                l = (arm.position - m.position).Lenght()
                if l < len:
                    tar = m
                    len = l
            cb.SendGame.addAction(tar.num,cb.SendGame.FIRE)
        else:
            tar = cb.GetEnemyFarMonster()
            cb.SendGame.addAction(tar.num,cb.SendGame.FIRE)
        

    cb.End()
