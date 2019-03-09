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
				// パラメーターを作成
				// output gain
				RangeParameter* Lvolume = new RangeParameter(STR16("Lvolume"), L_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);
				RangeParameter* Rvolume = new RangeParameter(STR16("Rvolume"), R_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);

				//pan
				RangeParameter* Lpan = new RangeParameter(STR16("Lpan"), L_PAN_TAG, STR16(""), -100.0f, 100.0f, -100.0f);
				RangeParameter* Rpan = new RangeParameter(STR16("Rpan"), R_PAN_TAG, STR16(""), -100.0f, 100.0f, 100.0f);


				// 上で作成したパラメーターを追加
				parameters.addParameter(Lvolume);
				parameters.addParameter(Rvolume);
				parameters.addParameter(Lpan);
				parameters.addParameter(Rpan);
				// 以下固有の初期化を実施。
				
			}

			
			result = kResultTrue;
			return result;
		}

		// ===================================================================================
		// processorクラスの状態を読み込む関数
		// ===================================================================================
		tresult PLUGIN_API MyVSTController::setComponentState(IBStream* state)
		{

			tresult res;

			// 保存されているデータを読み込む
			// 保存されているデータが複数ある場合はstate->readを繰り返す
			ParamValue Lvolume, Rvolume, Lpan, Rpan;
			res = state->read(&Lvolume, sizeof(ParamValue));
			res = state->read(&Rvolume, sizeof(ParamValue));
			res = state->read(&Lpan, sizeof(ParamValue));
			res = state->read(&Rpan, sizeof(ParamValue));
			if (res != kResultOk)
			{
				// 読込に失敗した場合はkResultFalseを返す。
				return kResultFalse;
			}

			// 読み込まれたデータをパラメータに反映する
			// 反映するデータは0.0～1.0の範囲にしておく
			Lvolume = plainParamToNormalized(L_VOLUME_TAG, Lvolume);
			setParamNormalized(L_VOLUME_TAG, Lvolume);
			Rvolume = plainParamToNormalized(R_VOLUME_TAG, Rvolume);
			setParamNormalized(R_VOLUME_TAG, Rvolume);
			Lpan = plainParamToNormalized(L_PAN_TAG, Lpan);
			setParamNormalized(L_PAN_TAG, Lpan);
			Rpan = plainParamToNormalized(R_PAN_TAG, Rpan);
			setParamNormalized(R_PAN_TAG, Rpan);

			// 関数の処理に問題がなければkResultOkを返す
			return kResultOk;
		}

	}
}