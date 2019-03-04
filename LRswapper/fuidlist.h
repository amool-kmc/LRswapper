// VST3 SDKのインクルードファイル
#include "pluginterfaces\base\funknown.h"

// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {

		// FUIDの生成
		static const FUID ProcessorUID(0x486B751C, 0x0A344B8D, 0x9D2AE919, 0x93501757);

	}
} // namespace SteinbergとVstの終わり