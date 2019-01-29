
import importlib

def execute(num,team,file):
    mod = importlib.import_module(file)
    try:
        mod.Brain(num,team)
    except:
        pass
    return 1
