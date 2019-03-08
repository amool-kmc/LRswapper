// include original file
#include "tag.h"
#include "fuidlist.h"
#include "controller.h"


namespace Steinberg {
	namespace Vst {


		// クラス初期化関数
		tresult PLUGIN_API MyVSTController::initialize(FUnknown* context)
		{
			// 継承元クラスの初期化
			tresult result = EditController::initialize(context);
			if (result == kResultTrue)
			{
				// パラメーターを追加
				// output gain
				RangeParameter* Lvolume = new RangeParameter(STR16("Lvolume"), L_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);
				RangeParameter* Rvolume = new RangeParameter(STR16("Rvolume"), L_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);

				//pan
				RangeParameter* Lpan = new RangeParameter(STR16("Lpan"), L_VOLUME_TAG, STR16(""), -1.0f, 1.0f, -1.0f);
				RangeParameter* Rpan = new RangeParameter(STR16("Rpan"), L_VOLUME_TAG, STR16(""), -1.0f, 1.0f, 1.0f);


				// 以下固有の初期化を実施。
				
			}

			
			result = kResultTrue;
			return result;
		}


	}
}