#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから
    target = cb.GetEnemyHighHPMonster()#一番攻撃力の高い敵をtargetに代入。     
    cb.Attack(target)#targetに攻撃。

#ここに間に処理をかく。
    cb.End()
