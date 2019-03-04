// include VST3 SDK
#include "public.sdk/source/vst/vstaudioeffect.h"


namespace Steinberg {
	namespace Vst {

		// ===================================================================================
		// 音声信号を処理するProcessorクラス
		// ===================================================================================
		class MyVSTProcessor : public AudioEffect
		{
		public:
			// 初期化関数
			tresult PLUGIN_API initialize(FUnknown* context);

			// バス構成
			tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

			// 音声信号処理関数
			tresult PLUGIN_API process(ProcessData& data);

			// 自作VST Processorクラスのインスタンスを作成するための関数
			static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
		};


	}
}