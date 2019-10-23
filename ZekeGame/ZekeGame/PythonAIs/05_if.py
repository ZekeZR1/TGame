#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから

    me = cb.GetMe()#meに自分を代入。
    target = cb.GetEnemyHighATKMonster()#一番攻撃力の高いてきをtargetに代入。

    if(me.HP <= 50):#自分のHPが５０以下のとき。
        cb.Defense(target)#HPが５０以下のときガードする。
        
    cb.Attack(target)#target2に攻撃。

#ここに間に処理をかく。
    cb.End()
