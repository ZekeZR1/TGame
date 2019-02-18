
import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    mon = cb.GetEnemyHighHP()

    cb.Leave(mon)
    cb.Fire(mon)
    cb.Defense(mon)
    cb.End()
