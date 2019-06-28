#coding: utf-8

import PythonAIs.CppBridge as cb
import os

def Brain(num,team):
    cb.init(num,team)

    with open("C:/py/path.txt","w") as f:
        f.writelines(__file__)
        f.writelines(os.getcwd())
    cb.End()
    return 1
