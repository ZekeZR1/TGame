#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから
    me = cb.GetMe()#meに自分を代入。
    target = cb.GetEnemyHighATKMonster()#一番攻撃力の高い敵をtargetに代入。
    target2 = cb.GetEnemyNeerMonster()#一番近くにいる敵をtarget2に代入。
    target3 = cb.GetEnemyHighHPMonster() #一番体力がある敵をtarget3に代入。

    if(me.HP <= 50):#自分のHPが５０以下のとき。
        cb.Escape(target2) #target2から逃げる。
    elif (me.HP <= 40):
        healer = cb.FindBuddyMonsterList(cb.Yose)
        cb.Chase(healer)
    else: #自分のHPが50より多い時(上の条件以外の時。
        cb.Attack(target)#targetに攻撃。

#ここまでの間に処理をかく。
    cb.End()
