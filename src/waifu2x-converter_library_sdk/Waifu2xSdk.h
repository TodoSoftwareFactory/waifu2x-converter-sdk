#pragma once

#include <string>

#using <System.dll>
#using <System.Drawing.dll>

using namespace System::Diagnostics;
using namespace System::Threading;

#ifndef WAIFU2XCLR_H__
#define WAIFU2XCLR_H__

public enum class E_Process { cpu, gpu };	// 変換処理モード
public enum class E_Noise_Level{ level1, level2 };	// ノイズ除去レベル

public ref class Waifu2xSDK : public System::EventArgs {
	//Thread^ trdReceiveStdOut;

public:

	// コンストラクタ
	Waifu2xSDK(void);

	// デストラクタ
	~Waifu2xSDK(void);


	/*
	// イベントの設定
	delegate void OnProgressHandler(System::String ^ Message);
	static event OnProgressHandler^ OnProgress;
	*/

	// エラーメッセージの取得
	System::String ^ GetErrorMessage();

	// コンバート処理
	bool Convert(System::Drawing::Bitmap ^ input_bitmap, System::Drawing::Bitmap ^ %output_bitmap, int jobs, double scale_ratio, E_Noise_Level noise_level, E_Process process);
	bool Convert(System::String ^ input_file, System::String ^ output_file, int jobs, double scale_ratio, E_Noise_Level noise_level, E_Process process);

internal:
	// 標準出力の横取り
	//delegate void DelegateRecieveHandler(Object ^, DataReceivedEventArgs ^);
	//static void RecieveHandler(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e);

private:
	/*
	void ReceiveStdOut();
	static void RecieveHandler(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e);
	*/
	
};

#endif 