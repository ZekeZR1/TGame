#pragma once
class NetworkLogic;
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

	//繋がっているんだ♪ 僕らはいつも以心伝心♪ 二人の声つなぐテレパシー♪
	bool isConect();

	//何か来ているか。
	bool isHang();
private:
	NetworkLogic* m_network = nullptr;			//NetworkLogicのインスタンス
	LoadBalancingListener* m_LBL = nullptr;		//LoadBalancingListenerのインスタンス
};