#coding: utf-8
#ダンジョン８
import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    me = cb.GetMe()
    kuri = cb.FindEnemy(cb.SendGame.Chris)
    red = cb.FindEnemy(cb.SendGame.RedHead)
    gob = cb.FindEnemy(cb.SendGame.Goblin)

    if me.ID == cb.SendGame.kuri:
        if me.MP >= 30
            cb.addAction(cb.GetEnemyHighATKMonster,cb.SendGame.Blizzard)

        if me.MP < 30
            cb.addAction(cb.GetEnemyLowHPMonster,cb.SendGame.CHASE)
            cb.addAction(cb.GetEnemyLowHPMonster,cb.SendGame.ATTACK)

    if me.ID == cb.SendGame.red:
        if me.MP >= 30
            cb.addAction(cb.GetEnemyLowHPMonster,cb.SendGame.Thunder)

        if me.MP < 30
            cb.addAction(cb.GetEnemyLowHPMonster,cb.SendGame.CHASE)
            cb.addAction(cb.GetEnemyLowHPMonster,cb.SendGame.ATTACK)

    if me.ID == cb.SendGame.gob:
        if me.MP >= 20
            cb.AddAction(cb.GetEnemyHighATKMonster.cb.SendGame.Poison)

        if me.MP < 20
            cb.addAction(cb.GetEnemyLowHPMonster,cb.SendGame.CHASE)
            cb.addAction(cb.GetEnemyLowHPMonster,cb.SendGame.ATTACK)