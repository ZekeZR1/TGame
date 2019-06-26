
import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    mon = cb.GetEnemyLowHPMonster()
    me = cb.GetMe()
    cb.Leave(mon)
    if me.MP >= 20:
        cb.Fire(mon)
    cb.Leave(mon)
    cb.End()
