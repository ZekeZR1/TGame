#coding: utf-8
#ダンジョン８

import CppBridge as cb

def Brain(num,team):
	cb.init(num,team)

	me = cb.GetMe()
	tar = cb.FindEnemy(cb.SemdGame.Uma)
	are = cb.FindEnemy(cb.SemdGame.Armor)
	boo = cb.FindEnemy(cb.SemdGame.book)


	#アーマー
	if me.ID == cb.SendGame.Armor:

		if  me.HP < 60
			cb.addAction(me,cb.SendGame.DEF_Buff)

		if  me.HP > 30			
		    if tar != None
            	cb.addAction(tar,cb.SendGame.enBuffAtc)

        if  cb.SendGame.Uma.Attack >= 30 and me.Defence >= 24
            cb.addAction(me,cb.SendGame.DEFENSE)


    elif me.ID == cb.SendGame.Uma:

    	if  boo != None
    	cb.addAction(boo,cb.SendGame.enTackle)

		if  me.MP >= 20
			cb.addAction(cb.GetEnemyLowHPMonster(),cb.SendGame.enTackle)	

        if  me.MP >= 15
            cb.addAction(cb.GetEnemyHighHPMonster(),cb.SendGame.enChase)
            cb.addAction(cb.GetEnemyHighHPMonster(),cb.SendGame.enMajinken)

        if  me.MP < 15
            cb.addAction(cb.GetEnemyLowHPMonster(),cb.SendGame.enChase)    
            cb.addAction(cb.GetEnemyLowHPMonster(),cb.SendGame.enAtack)    

    elif me.ID == cb.SendGame.Yose:

    	if  me.HP <= 40
    	    cb.addAction(cb.GetNeerMonster(),cb.SendGame.enLeave)
    	    cb.addAction(me,cb.SendGame.enRecovery)

    	if  me.HP > 40
            if  cb.SendGame.Uma.HP <= 50  and  cb.SendGame.Armor.HP >= 40
            	if tar != None
                	cb.addAction(tar,cb.SendGame.enRecovery)

            if  cb.SendGame.Armor.HP <= 60
            	if are != None
            		cb.addAction(are,cbSendGame.enRecovery)

            if  cb.SendGame.Uma.HP > 50  and  cb.SendGame.Armor.HP > 60
                if  me.MP >= 40 
                	cb.AddAction(cb.GetEnemyLowHPMonster(),cb.SandGame.enFire) 

    
	cb.End()