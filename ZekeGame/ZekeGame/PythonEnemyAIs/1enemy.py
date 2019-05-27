import CppBridge as cb

def Brain(num,team):
	cb.init(num,team)
    me = cb.GetMe()
	if me.ID == cb.FairyID:
		if me.MP >= 5:
			mon = cb.GetBuddyLowHPMonster()
			cb.Recovery(mon)
	cb.End()
