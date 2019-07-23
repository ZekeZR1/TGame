#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから
    
    me = cb.GetMe()#meに自分を代入。
    target = cb.GetEnemyHighATKMonster()#一番攻撃力の高いてきをtargetに代入。
    target2 = cb.GetEnemyNeerMonster()#一番近くにいるモンスターをtarget2に代入。


    if(me.HP <= 20):#自分のHPが20以下のとき。
        cb.Escape(target2) #target2から逃げる。
    elif (me.HP < 50):#自分のHPが50より小さい時
        cb.Defense(target2)#ディフェンス。
    else: #上の2つの条件のどちらにも当てはまらない時。
        cb.Attack(target)#targetに攻撃。

#ここに間に処理をかく。
    cb.End()
