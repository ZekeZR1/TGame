#coding:utf-8

import CppBridge as cb

def Brain():
    cb.Init()
    me = cb.GetMe()
    pos = me.position
    pos.x += 300
    pos.z += 1000
    cb.SendGame.Move(pos.x,pos.z)
    cb.End()
