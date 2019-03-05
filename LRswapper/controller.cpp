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
				parameters.addParameter(STR16("param1"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, L_VOLUME_TAG);
				parameters.addParameter(STR16("param1"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, R_VOLUME_TAG);


				// 以下固有の初期化を実施。
				
			}

			
			result = kResultTrue;
			return result;
		}


	}
}