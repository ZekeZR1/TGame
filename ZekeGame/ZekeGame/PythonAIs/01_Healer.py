#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから
    target = cb.GetBuddyLowHPMonster()#一番HPの低い味方をtargetに代入。
    cb.Heal(target); #ターゲットを回復。
#ここに間に処理をかく。
    cb.End()
