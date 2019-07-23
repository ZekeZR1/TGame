#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから

    target = cb.GetEnemyNeerMonster()#一番攻撃力の近い敵をtargetに代入。
    cb.ATK_Debuff(target) #targetの攻撃力を下げる。
    
#ここに間に処理をかく。
    cb.End()
