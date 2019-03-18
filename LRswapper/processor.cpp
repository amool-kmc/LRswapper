// include original file
#include "fuidlist.h"
#include "processor.h"
#include "controller.h"


namespace Steinberg {
	namespace Vst {

		// =================================================================================
		// コンストラクタ
		// =================================================================================
		MyVSTProcessor::MyVSTProcessor()
			// パラメーターの初期値
			:Lvolume(0.0f), Rvolume(0.0f), Lpan(-100.0f), Rpan(100.0f)
		{
			// コントローラーのFUIDを設定
			setControllerClass(ControllerUID);
		}

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

		// ===================================================================================
		// バス構成を決める関数
		// ===================================================================================
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
		// 状態を読み込む関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::setState(IBStream* state)
		{
			// 保存データを読み込む
			// 保存データが複数ある場合はstate->readを繰り返す
			tresult res;
			res = state->read(&Lvolume, sizeof(ParamValue));
			res = state->read(&Rvolume, sizeof(ParamValue));
			res = state->read(&Lpan, sizeof(ParamValue));
			res = state->read(&Rpan, sizeof(ParamValue));
			if (res != kResultOk)
			{
				// 読込に失敗した場合はkResultFalseを返す。
				return kResultFalse;
			}

			return kResultOk;
		}

		// ===================================================================================
		// 状態を保存する関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::getState(IBStream* state)
		{
			// データを保存する
			// 保存したいデータが複数ある場合はstate->writeを繰り返す。
			state->write(&Lvolume, sizeof(ParamValue));
			state->write(&Rvolume, sizeof(ParamValue));
			state->write(&Lpan, sizeof(ParamValue));
			state->write(&Rpan, sizeof(ParamValue));

			// 関数の処理に問題がなければkResultOkを返す
			return kResultOk;
		}

		// ===================================================================================
		// 音声信号を処理する関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
		{
			// パラメーター変更時の処理
			if (data.inputParameterChanges != NULL) {
				// 入力パラメーター数取得
				int32 paramChangeCount = data.inputParameterChanges->getParameterCount();

				// 入力パラメーター数だけ処理
				for (int32 i = 0; i < paramChangeCount; i++) {
					// 変更パラメーターの種類の情報キュー
					IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);

					if (queue != NULL) {
						// パラメーターtag取得
						int32 tag = queue->getParameterId();
						// 変更回数
						int32 valueCgangeCount = queue->getPointCount();

						// パラメーターの値とオフセット
						ParamValue value;
						int32 sampleOffset;

						// 最後の値のみ取得する
						if (queue->getPoint(valueCgangeCount - 1, sampleOffset, value) == kResultTrue) {
							// tagごとの値渡し、処理(そのまま渡したら規格化されたまま)読み書きを考えるとパラメーターの値に戻すべきか
							switch (tag)
							{
							case L_VOLUME_TAG:
								Lvolume = value * 30 - 20; // -20~10
								break;
							case R_VOLUME_TAG:
								Rvolume = value * 30 - 20; // -20~10
								break;
							case L_PAN_TAG:
								Lpan = value * 200 - 100; // -100~100
								break;
							case R_PAN_TAG:
								Rpan = value * 200 - 100; // -100~100
								break;
							}
						}
					}
				}
			}
			// 入力・出力バッファのポインタ
			Sample32* inL = data.inputs[0].channelBuffers32[0];
			Sample32* inR = data.inputs[0].channelBuffers32[1];
			Sample32* outL = data.outputs[0].channelBuffers32[0];
			Sample32* outR = data.outputs[0].channelBuffers32[1];

			// numSamplesで示されるサンプル分、音声を処理する
			for (int32 i = 0; i < data.numSamples; i++)
			{
				Sample32 inLoutL, inLoutR, inRoutL, inRoutR;
				inLoutR = ((Lpan + 100) / 200) * inL[i];
				inLoutL = -((Lpan + 100) / 200 - 1) * inL[i];
				inRoutL = -((Rpan + 100) / 200 - 1) * inR[i];
				inRoutR = ((Rpan + 100) / 200) * inR[i];

				outL[i] = ((Lvolume + 20) / 20) * (inLoutL + inRoutL);
				outR[i] = ((Rvolume + 20) / 20) * (inLoutR + inRoutR);
			}

			
			return kResultTrue;
		}

	}
} 