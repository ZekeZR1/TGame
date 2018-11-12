#pragma once
class NetIO : public NetworkLogicListener
{
public:
	NetIO();
	~NetIO();
	void start();
	void update(NetworkLogic*);
	void usage(void);
private:
	virtual void stateUpdate(State newState) {}
	NetworkLogic* mp_networkLogic;
	bool mExit = false;
};


