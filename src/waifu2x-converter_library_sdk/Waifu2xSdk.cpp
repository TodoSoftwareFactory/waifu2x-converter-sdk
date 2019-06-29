#include "Waifu2xSdk.h"
#include "w2xconv.h"

#include <string>
#include <msclr\marshal_cppstd.h>
#include <stdio.h>
#include <windows.h>
#include <iostream>

#using <System.dll>
#using <System.Drawing.dll>

using namespace msclr::interop;
using namespace System::Runtime::InteropServices;
using namespace System;
using namespace System::Drawing;
using namespace System::Diagnostics;
using namespace System::Threading;
using namespace System::ComponentModel;

char *strErrorMessage = "";

/*
HANDLE hStdOutReadPipe, hStdOutWritePipe , hDupStdOutReadPipe;
bool bolThredEnableFlag;
*/

/// <summary>
/// コンストラクタ
/// </summary>
Waifu2xSDK::Waifu2xSDK(){

	/*
	// 標準出力を横取りするよう設定
	// http://dobon.net/vb/bbs/log3-38/23206.html
	// http://7ujm.net/C++/pipe.html
	// http://www.ne.jp/asahi/hishidama/home/tech/c/windows/CreatePipe.html
	SECURITY_ATTRIBUTES objAttributes;
	objAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	objAttributes.lpSecurityDescriptor = NULL;
	objAttributes.bInheritHandle = TRUE;

	//HANDLE hStdOutReadPipe, hStdOutWritePipe;// , hDupStdOutReadPipe;

	CreatePipe(&hStdOutReadPipe, &hStdOutWritePipe, &objAttributes, 0);
	SetStdHandle(STD_OUTPUT_HANDLE, hStdOutWritePipe);
	DuplicateHandle(GetCurrentProcess(), hStdOutReadPipe, GetCurrentProcess(), &hDupStdOutReadPipe, 0, false, DUPLICATE_SAME_ACCESS);

	bolThredEnableFlag = true;
	trdReceiveStdOut = gcnew Thread(gcnew ThreadStart(this, &Waifu2xSDK::ReceiveStdOut));
	trdReceiveStdOut->IsBackground = true;
	trdReceiveStdOut->Start();

	//FILE* fp_out = freopen("E:\work\result.txt", "w", stdout);
	//std::cout << "test" << std::endl;
	//fclose(fp_out);
	*/

}

/// <summary>
/// デストラクタ
/// </summary>
Waifu2xSDK::~Waifu2xSDK(){
	/*
	bolThredEnableFlag = false;
	//fclose(fp_out);
	*/
}

/*
/// <summary>
/// 標準出力の受信
/// </summary>
void Waifu2xSDK::ReceiveStdOut(){
	
	do
	{
		//System::IO::FileStream^ fs = gcnew System::IO::FileStream(hDupStdOutReadPipe, System::IO::FileAccess::Read);

		
		//DWORD dwByte;
		//
		//FlushFileBuffers(hDupStdOutReadPipe);
		//char str[1024];
		//ReadFile(hDupStdOutReadPipe, str, sizeof(str), &dwByte, NULL);
		//str[dwByte] = '\0';
		//
		//System::String ^strMessage = gcnew String(str);
		//if (strMessage->Length > 0){
		//	System::Diagnostics::Debug::WriteLine(strMessage);
		//}
		

	} while (bolThredEnableFlag);

	//System::Diagnostics::Debug::WriteLine(str,);

	//System::String^ str = "";
}
*/

/// <summary>
/// 最後に起きたエラーのメッセージを取得
/// </summary>
/// <returns>エラーメッセージ</returns>
System::String ^ Waifu2xSDK::GetErrorMessage(){
	return marshal_as<System::String ^>(strErrorMessage);
}

/// <summary>
/// waife2x-converterを用いて画像のコンバート処理を実行
/// </summary>
/// <param name="input_bitmap">変換する画像のビットマップデータ</param>
/// <param name="output_bitmap">変換された画像のビットマップデータ格納先</param>
/// <param name="jobs">プログラム内で処理を分割する数 (default:4)</param>
/// <param name="scale_ratio">拡大倍率 (default:2.0)</param>
/// <param name="noise_level">ノイズ除去レベル Level1もしくはLevel2 (default:1)</param>
/// <param name="process">処理に使うプロセッサー cpu:CPUを使って変換 gpu:CUDA(GPU)を使って変換 (default:gpu)</param>
/// <returns>True:成功 False:失敗</returns>
bool Waifu2xSDK::Convert(System::Drawing::Bitmap ^ input_bitmap, System::Drawing::Bitmap ^ %output_bitmap, int jobs, double scale_ratio, E_Noise_Level noise_level, E_Process process){
	bool bolResult = false;

	struct W2XConv *srcW2XConv = NULL;
	int intResult;

	try{
		/*
		Process ^p = Process::GetCurrentProcess();
		p->OutputDataReceived += gcnew DataReceivedEventHandler(RecieveHandler);
		*/

		if (input_bitmap->PixelFormat != System::Drawing::Imaging::PixelFormat::Format24bppRgb){
			strErrorMessage = "24BitのBitmapを指定してください。";
			return false;
		}


		int src_w = input_bitmap->Width;
		int src_h = input_bitmap->Height;


		// 画像の読み込み
		array<unsigned char> ^ bmpSrcBytes = gcnew array<unsigned char>(src_w * src_h * 3);
		pin_ptr <unsigned char> pSrc = &bmpSrcBytes[0];

		int intPointer = 0;
		for (size_t y = 0; y < src_h; y++)
		{
			for (size_t x = 0; x < src_w; x++)
			{
				Color clrSrc = input_bitmap->GetPixel(x, y);
				bmpSrcBytes[intPointer] = clrSrc.R;
				intPointer++;
				bmpSrcBytes[intPointer] = clrSrc.G;
				intPointer++;
				bmpSrcBytes[intPointer] = clrSrc.B;
				intPointer++;
			}
		}
				
		size_t src_size = src_w * 3; //bmpSrcBytes->Length;


		// 格納領域の作成
		array<unsigned char> ^ bmpDstBytes = gcnew array<unsigned char>((src_w * scale_ratio) * (src_h * scale_ratio) * 3);
		pin_ptr <unsigned char> pDst = &bmpDstBytes[0];
		for (size_t i = 0; i < bmpDstBytes->Length; i++)
		{
			bmpDstBytes[i] = '\0';
		}
		
		size_t dst_size = (src_w * scale_ratio) * 3; //bmpDstBytes->Length;

		
		// Waifu-2x 設定
		int intNoiseLevel = 1;
		if (noise_level == E_Noise_Level::level1){
			intNoiseLevel = 1;
		}
		else if (noise_level == E_Noise_Level::level2){
			intNoiseLevel = 2;
		}

		W2XConvGPUMode objConvGPUMode = W2XCONV_GPU_AUTO;
		if (process == E_Process::cpu){
			objConvGPUMode = W2XCONV_GPU_DISABLE;
		}
		else if (process == E_Process::gpu){
			objConvGPUMode = W2XCONV_GPU_AUTO;
		}

		srcW2XConv = w2xconv_init(objConvGPUMode, jobs, 1);
		intResult = w2xconv_load_models(srcW2XConv, "models_rgb");

		if (intResult >= 0){

			intResult = w2xconv_convert_rgb(srcW2XConv, pDst, dst_size, pSrc, src_size, src_w, src_h, intNoiseLevel, scale_ratio, 512);

			if (intResult >= 0){
				// 画像の出力
				output_bitmap = gcnew System::Drawing::Bitmap(input_bitmap->Width * scale_ratio, input_bitmap->Height * scale_ratio, System::Drawing::Imaging::PixelFormat::Format24bppRgb);
				int intPointer = 0;
				
				for (size_t y = 0; y < output_bitmap->Height; y++)
				{
					for (size_t x = 0; x < output_bitmap->Width; x++)
					{
						unsigned char R = bmpDstBytes[intPointer];
						intPointer++;
						unsigned char G = bmpDstBytes[intPointer];
						intPointer++;
						unsigned char B = bmpDstBytes[intPointer];
						intPointer++;

						Color clrDst = Color::FromArgb(R, G, B);
						output_bitmap->SetPixel(x, y, clrDst);
					}
				}

				bolResult = true;
			}
			else{
				strErrorMessage = w2xconv_strerror(&srcW2XConv->last_error);
			}
		}
		else{
			strErrorMessage = w2xconv_strerror(&srcW2XConv->last_error);
		}


		pSrc = nullptr;
		pDst = nullptr;

	}
	catch (...) {
		LPVOID lpMsgBuf;

		FormatMessage(				//エラー表示文字列作成
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);

		strErrorMessage = (char*)lpMsgBuf;

	}
	finally{
		if (srcW2XConv != NULL){
			w2xconv_fini(srcW2XConv);
		}
	}

	return bolResult;
}

/// <summary>
/// waife2x-converterを用いて画像のコンバート処理を実行
/// </summary>
/// <param name="input_file">変換する画像のフルパス</param>
/// <param name="output_file">変換された画像のフルパス（ファイル名・拡張子含む）</param>
/// <param name="jobs">プログラム内で処理を分割する数 (default:4)</param>
/// <param name="scale_ratio">拡大倍率 (default:2.0)</param>
/// <param name="noise_level">ノイズ除去レベル Level1もしくはLevel2 (default:1)</param>
/// <param name="process">処理に使うプロセッサー cpu:CPUを使って変換 gpu:CUDA(GPU)を使って変換 (default:gpu)</param>
/// <returns>True:成功 False:失敗</returns>
bool Waifu2xSDK::Convert(System::String ^ input_file, System::String ^ output_file, int jobs, double scale_ratio, E_Noise_Level noise_level, E_Process process) {
	bool bolResult = false;

	struct W2XConv *srcW2XConv = NULL;
	int intResult;

	try{
		//標準出力を横取りするよう設定
		/*
		System::Diagnostics::Debug::WriteLine("OutputLog:On");
		Process ^p = Process::GetCurrentProcess();
		p->StartInfo->RedirectStandardOutput = true;
		p->OutputDataReceived += gcnew DataReceivedEventHandler(RecieveHandler);
		*/

		/*
		SECURITY_ATTRIBUTES objAttributes;
		objAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
		objAttributes.lpSecurityDescriptor = NULL;
		objAttributes.bInheritHandle = TRUE;

		HANDLE hStdOutReadPipe, hStdOutWritePipe;// , hDupStdOutReadPipe;
		
		CreatePipe(&hStdOutReadPipe, &hStdOutWritePipe, &objAttributes, 0);
		SetStdHandle(STD_OUTPUT_HANDLE, hStdOutWritePipe);
		DuplicateHandle(GetCurrentProcess(), hStdOutReadPipe, GetCurrentProcess(), &hDupStdOutReadPipe, 0, false, DUPLICATE_SAME_ACCESS);
		*/

		marshal_context ^ context = gcnew marshal_context();
		const char* dst_path = context->marshal_as<const char*>("""" + output_file + """");
		const char* src_path = context->marshal_as<const char*>("""" + input_file + """");

		int intNoiseLevel = 1;
		if (noise_level == E_Noise_Level::level1){
			intNoiseLevel = 1;
		}
		else if (noise_level == E_Noise_Level::level2){
			intNoiseLevel = 2;
		}

		W2XConvGPUMode objConvGPUMode = W2XCONV_GPU_AUTO;
		if (process == E_Process::cpu){
			objConvGPUMode = W2XCONV_GPU_DISABLE;
		}
		else if (process == E_Process::gpu){
			objConvGPUMode = W2XCONV_GPU_AUTO;
		}

		srcW2XConv = w2xconv_init(objConvGPUMode, jobs, 1);
		
		intResult = w2xconv_load_models(srcW2XConv, "models_rgb");

		if (intResult >= 0){

			intResult = w2xconv_convert_file(srcW2XConv, dst_path, src_path, intNoiseLevel, scale_ratio, 512);

			if (intResult >= 0){
				bolResult = true;
			}
			else{
				strErrorMessage = w2xconv_strerror(&srcW2XConv->last_error);
			}
		}
		else{
			strErrorMessage = w2xconv_strerror(&srcW2XConv->last_error);
		}
	}
	catch (...) {
		LPVOID lpMsgBuf;

		FormatMessage(				//エラー表示文字列作成
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL, GetLastError(), 
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf, 0, NULL);

		strErrorMessage = (char*)lpMsgBuf;

	}
	finally{
		if (srcW2XConv != NULL){
			w2xconv_fini(srcW2XConv);
		}
	}
	return bolResult;
}

/*
/// <summary>
/// 標準出力の横取り
/// </summary>
void Waifu2xSDK::RecieveHandler(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e){
	if (!System::String::IsNullOrEmpty(e->Data))
	{
		//OnProgress(e->Data);
		System::Diagnostics::Debug::WriteLine(e->Data);

		System::String^ str = "";
	}
}
*/




