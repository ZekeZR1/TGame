
import importlib

def execute(num,team,file):
    try:
        mod = importlib.import_module(file)
        mod.Brain(num,team)
    except:
        import sys
        import os
        from datetime import datetime

        path = __file__
        path = path[:path.rfind("\\")] + "/error.log"
        with open(path,"a") as file:
            etuple = sys.exc_info()
            file.write("---ERROR---\n")
            time = datetime.now().strftime('%Y/%m/%d %H:%M:%S')
            file.write(time+"\n")
            file.write("MonsterNum:"+str(num)+"\n")
            file.write("MonsterTeam:"+str(team)+"\n")
            file.write(str(etuple[0])+"\n")
            file.write(str(etuple[1])+"\n")
            file.write(str(etuple[2])+"\n\n")
        return 0
    return 1
