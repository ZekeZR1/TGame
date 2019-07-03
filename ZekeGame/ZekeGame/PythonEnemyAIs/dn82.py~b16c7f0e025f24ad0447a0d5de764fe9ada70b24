#coding: utf-8
#ダンジョン８
import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    me = cb.GetMe()
    kuri = cb.FindEnemy(cb.SendGame.Chris)
    red = cb.FindEnemy(cb.SendGame.RedHead)
    gob = cb.FindEnemy(cb.SendGame.Goblin)

    if me.ID == cb.SendGame.Chris:
        if me.MP >= 30:
            tar = cb.GetEnemyHighATKMonster()
            cb.addAction(tar,cb.SendGame.Blizzard)

        if me.MP < 30:
            tar = cb.GetEnemyLowHPMonster()
            cb.addAction(tar,cb.SendGame.CHASE)
            cb.addAction(tar,cb.SendGame.ATTACK)

    if me.ID == cb.SendGame.RedHead:
        tar = cb.GetEnemyLowHPMonster()
        if me.MP >= 30:
            cb.addAction(tar,cb.SendGame.Thunder)

        if me.MP < 30:
            cb.addAction(tar,cb.SendGame.CHASE)
            cb.addAction(tar,cb.SendGame.ATTACK)

    if me.ID == cb.SendGame.Goblin:
        if me.MP >= 20:
            tar = cb.GetEnemyHighATKMonster()
            cb.addAction(tar,cb.SendGame.CHASE)
            cb.addAction(tar,cb.SendGame.Poison)

        if me.MP < 20:
            tar = cb.GetEnemyLowHPMonster()
            cb.addAction(tar,cb.SendGame.CHASE)
            cb.addAction(tar,cb.SendGame.ATTACK)
    cb.End()
