#coding: utf-8
#ダンジョン８

import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    me = cb.GetMe()
    tar = cb.FindBuddyMonster(cb.SendGame.Uma)
    are = cb.FindBuddyMonster(cb.SendGame.Armor)
    boo = cb.FindBuddyMonster(cb.SendGame.Book)


    #アーマー
    if me.ID == cb.SendGame.Armor:

        if  me.HP < 60:
            cb.addAction(me,cb.SendGame.DEF_Buff)

        if tar != None:
            if  me.HP > 30:
                cb.addAction(tar,cb.SendGame.ATK_Buff)
        cb.addAction(me,cb.SendGame.GUARDIAN)


    elif me.ID == cb.SendGame.Uma:

        if  boo != None:
            cb.addAction(boo,cb.SendGame.TACKLE)

        if  me.MP >= 20:
            cb.addAction(cb.GetEnemyLowHPMonster(),cb.SendGame.TACKLE)	

        if  me.MP >= 15:
            cb.addAction(cb.GetEnemyHighHPMonster(),cb.SendGame.CHASE)
            cb.addAction(cb.GetEnemyHighHPMonster(),cb.SendGame.Majinken)

        if  me.MP < 15:
            cb.addAction(cb.GetEnemyLowHPMonster(),cb.SendGame.CHASE)    
            cb.addAction(cb.GetEnemyLowHPMonster(),cb.SendGame.ATTACK)    

    elif me.ID == cb.SendGame.Yose:

        if  me.HP <= 40:
            cb.addAction(cb.GetNeerMonster(),cb.SendGame.ESCAPE)
            cb.addAction(me,cb.SendGame.HEAL)

        if tar != None:
            if  me.HP > 40:
                if  tar.HP <= 50  and  are.HP >= 40:
                    cb.addAction(tar,cb.SendGame.HEAL)
        if are != None:
            if  are.HP <= 60:
                cb.addAction(are,cb.SendGame.HEAL)


        if  me.MP >= 40:
            cb.addAction(cb.GetEnemyLowHPMonster(),cb.SendGame.FIRE) 

    
    cb.End()
