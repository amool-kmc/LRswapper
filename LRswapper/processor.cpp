// 自作VST用のインクルードファイル
#include "fuidlist.h"
#include "processor.h"


namespace Steinberg {
	namespace Vst {


		// ===================================================================================
		// クラス初期化関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
		{
			// 継承元クラス初期化
			tresult result = AudioEffect::initialize(context);
			if (result == kResultTrue)
			{
				// 入力と出力を設定
				addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
				addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

				// その他の初期化

				
			}


			
			return result;
		}

		tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
		{
			//バス構成
			if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
			{
				return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
			}

			// 対応していないバス構成の場合、kResultFalseを返す。
			return kResultFalse;
		}

		// ===================================================================================
		// 音声信号を処理する関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
		{
			// 入力・出力バッファのポインタをわかりやすい変数に格納
			// inputs[]、outputs[]はAudioBusの数だけある(addAudioInput()、addAudioOutput()で追加した分だけ)
			// 今回はAudioBusは1つだけなので 0 のみとなる
			// channelBuffers32は32bit浮動小数点型のバッファで音声信号のチャンネル数分ある
			// モノラル(kMono)なら 0 のみで、ステレオ(kStereo)なら 0(Left) と 1(Right) となる
			Sample32* inL = data.inputs[0].channelBuffers32[0];
			Sample32* inR = data.inputs[0].channelBuffers32[1];
			Sample32* outL = data.outputs[0].channelBuffers32[0];
			Sample32* outR = data.outputs[0].channelBuffers32[1];

			// numSamplesで示されるサンプル分、音声を処理する
			for (int32 i = 0; i < data.numSamples; i++)
			{
				outL[i] = inL[i];
				outR[i] = inR[i];
			}

			
			return kResultTrue;
		}

	}
} 