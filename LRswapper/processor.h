// include VST3 SDK
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/base/ibstream.h"

namespace Steinberg {
	namespace Vst {

		// ===================================================================================
		// 音声信号を処理するProcessorクラス
		// ===================================================================================
		class MyVSTProcessor : public AudioEffect
		{
		protected:
			ParamValue Lvolume;
			ParamValue Rvolume;
			ParamValue Lpan;
			ParamValue Rpan;
		public:
			// コンストラクタ
			MyVSTProcessor();

			// 初期化関数
			tresult PLUGIN_API initialize(FUnknown* context);

			// バス構成
			tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

			// processorクラスの状態の読み込み、保存
			tresult PLUGIN_API setState(IBStream* state);
			tresult PLUGIN_API getState(IBStream* state);

			// 音声信号処理関数
			tresult PLUGIN_API process(ProcessData& data);

			// 自作VST Processorクラスのインスタンスを作成するための関数
			static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
		};


	}
}