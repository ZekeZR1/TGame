#pragma once

//データを送ったり受け取ったりするクラス
class ExchangeData
{
public:
	//初期化
	ExchangeData();

	/*
	モンスターのデータを送る
	arg:
		num:	何番目のモンスターか
		monid:モンスターのID
	*/
	void sendMonData(int num, int monID);

	//lblに文字列を送る
	//file: 送る文字列
	void sendData(const char* file);
private:
	NetworkLogic* m_network = nullptr;			//NetworkLogicのインスタンス
	LoadBalancingListener* m_LBL = nullptr;		//LoadBalancingListenerのインスタンス
};