#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから
    target = cb.GetBuddyHighATKMonster()#一番攻撃力の高い味方をtargetに代入。
    target2 = cb.GetBuddyFarMonster() #一番遠い味方のモンスターをtarget2に代入。
    
    cb.ATK_Buff(target) #targetの高い味方の攻撃力を上げる。
    cb.DEF_Buff(target2) #target2の防御力を上げる。
#ここに間に処理をかく。
    cb.End()
