
import importlib

def execute(num,team,file):
    mod = importlib.import_module(file)
    mod.Brain(num,team)
    return 1
