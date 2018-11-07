#pragma once
class TestListener : public CListener
{
public:
	TestListener();
	~TestListener();
private:
	virtual void writeString(const ExitGames::Common::JString& str);
	virtual bool anyKeyPressed() const;
	virtual void onLibClosed();
private:
	ExitGames::Common::JString lastString;
};

