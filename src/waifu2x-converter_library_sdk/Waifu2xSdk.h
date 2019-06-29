#pragma once

#include <string>

#using <System.dll>
#using <System.Drawing.dll>

using namespace System::Diagnostics;
using namespace System::Threading;

#ifndef WAIFU2XCLR_H__
#define WAIFU2XCLR_H__

public enum class E_Process { cpu, gpu };	// �ϊ��������[�h
public enum class E_Noise_Level{ level1, level2 };	// �m�C�Y�������x��

public ref class Waifu2xSDK : public System::EventArgs {
	//Thread^ trdReceiveStdOut;

public:

	// �R���X�g���N�^
	Waifu2xSDK(void);

	// �f�X�g���N�^
	~Waifu2xSDK(void);


	/*
	// �C�x���g�̐ݒ�
	delegate void OnProgressHandler(System::String ^ Message);
	static event OnProgressHandler^ OnProgress;
	*/

	// �G���[���b�Z�[�W�̎擾
	System::String ^ GetErrorMessage();

	// �R���o�[�g����
	bool Convert(System::Drawing::Bitmap ^ input_bitmap, System::Drawing::Bitmap ^ %output_bitmap, int jobs, double scale_ratio, E_Noise_Level noise_level, E_Process process);
	bool Convert(System::String ^ input_file, System::String ^ output_file, int jobs, double scale_ratio, E_Noise_Level noise_level, E_Process process);

internal:
	// �W���o�͂̉����
	//delegate void DelegateRecieveHandler(Object ^, DataReceivedEventArgs ^);
	//static void RecieveHandler(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e);

private:
	/*
	void ReceiveStdOut();
	static void RecieveHandler(System::Object^ sender, System::Diagnostics::DataReceivedEventArgs^ e);
	*/
	
};

#endif 