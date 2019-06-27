
import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.gameData.init(num,team)
    
    mon = cb.GetNeerMonster()
    cb.Leave(mon)


    cb.End()
    return 0
