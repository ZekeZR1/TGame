#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain():
    cb.Init()
#ここから
    me = cb.GetMe()#meに自分を代入。
    cb.Guardian(me); #敵の攻撃を自分に集める。
    cb.Defense(me); #ディフェンス。
#ここに間に処理をかく。
    cb.End()
