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
/// �R���X�g���N�^
/// </summary>
Waifu2xSDK::Waifu2xSDK(){

	/*
	// �W���o�͂�����肷��悤�ݒ�
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
/// �f�X�g���N�^
/// </summary>
Waifu2xSDK::~Waifu2xSDK(){
	/*
	bolThredEnableFlag = false;
	//fclose(fp_out);
	*/
}

/*
/// <summary>
/// �W���o�͂̎�M
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
/// �Ō�ɋN�����G���[�̃��b�Z�[�W���擾
/// </summary>
/// <returns>�G���[���b�Z�[�W</returns>
System::String ^ Waifu2xSDK::GetErrorMessage(){
	return marshal_as<System::String ^>(strErrorMessage);
}

/// <summary>
/// waife2x-converter��p���ĉ摜�̃R���o�[�g���������s
/// </summary>
/// <param name="input_bitmap">�ϊ�����摜�̃r�b�g�}�b�v�f�[�^</param>
/// <param name="output_bitmap">�ϊ����ꂽ�摜�̃r�b�g�}�b�v�f�[�^�i�[��</param>
/// <param name="jobs">�v���O�������ŏ����𕪊����鐔 (default:4)</param>
/// <param name="scale_ratio">�g��{�� (default:2.0)</param>
/// <param name="noise_level">�m�C�Y�������x�� Level1��������Level2 (default:1)</param>
/// <param name="process">�����Ɏg���v���Z�b�T�[ cpu:CPU���g���ĕϊ� gpu:CUDA(GPU)���g���ĕϊ� (default:gpu)</param>
/// <returns>True:���� False:���s</returns>
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
			strErrorMessage = "24Bit��Bitmap���w�肵�Ă��������B";
			return false;
		}


		int src_w = input_bitmap->Width;
		int src_h = input_bitmap->Height;


		// �摜�̓ǂݍ���
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


		// �i�[�̈�̍쐬
		array<unsigned char> ^ bmpDstBytes = gcnew array<unsigned char>((src_w * scale_ratio) * (src_h * scale_ratio) * 3);
		pin_ptr <unsigned char> pDst = &bmpDstBytes[0];
		for (size_t i = 0; i < bmpDstBytes->Length; i++)
		{
			bmpDstBytes[i] = '\0';
		}
		
		size_t dst_size = (src_w * scale_ratio) * 3; //bmpDstBytes->Length;

		
		// Waifu-2x �ݒ�
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
				// �摜�̏o��
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

		FormatMessage(				//�G���[�\��������쐬
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
/// waife2x-converter��p���ĉ摜�̃R���o�[�g���������s
/// </summary>
/// <param name="input_file">�ϊ�����摜�̃t���p�X</param>
/// <param name="output_file">�ϊ����ꂽ�摜�̃t���p�X�i�t�@�C�����E�g���q�܂ށj</param>
/// <param name="jobs">�v���O�������ŏ����𕪊����鐔 (default:4)</param>
/// <param name="scale_ratio">�g��{�� (default:2.0)</param>
/// <param name="noise_level">�m�C�Y�������x�� Level1��������Level2 (default:1)</param>
/// <param name="process">�����Ɏg���v���Z�b�T�[ cpu:CPU���g���ĕϊ� gpu:CUDA(GPU)���g���ĕϊ� (default:gpu)</param>
/// <returns>True:���� False:���s</returns>
bool Waifu2xSDK::Convert(System::String ^ input_file, System::String ^ output_file, int jobs, double scale_ratio, E_Noise_Level noise_level, E_Process process) {
	bool bolResult = false;

	struct W2XConv *srcW2XConv = NULL;
	int intResult;

	try{
		//�W���o�͂�����肷��悤�ݒ�
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

		FormatMessage(				//�G���[�\��������쐬
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
/// �W���o�͂̉����
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




