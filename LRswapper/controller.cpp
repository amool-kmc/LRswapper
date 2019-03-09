// include original file
#include "tag.h"
#include "fuidlist.h"
#include "controller.h"


namespace Steinberg {
	namespace Vst {


		// �N���X�������֐�
		tresult PLUGIN_API MyVSTController::initialize(FUnknown* context)
		{
			// �p�����N���X�̏�����
			tresult result = EditController::initialize(context);
			if (result == kResultTrue)
			{
				// �p�����[�^�[���쐬
				// output gain
				RangeParameter* Lvolume = new RangeParameter(STR16("Lvolume"), L_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);
				RangeParameter* Rvolume = new RangeParameter(STR16("Rvolume"), R_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);

				//pan
				RangeParameter* Lpan = new RangeParameter(STR16("Lpan"), L_PAN_TAG, STR16(""), -100.0f, 100.0f, -100.0f);
				RangeParameter* Rpan = new RangeParameter(STR16("Rpan"), R_PAN_TAG, STR16(""), -100.0f, 100.0f, 100.0f);


				// ��ō쐬�����p�����[�^�[��ǉ�
				parameters.addParameter(Lvolume);
				parameters.addParameter(Rvolume);
				parameters.addParameter(Lpan);
				parameters.addParameter(Rpan);
				// �ȉ��ŗL�̏����������{�B
				
			}

			
			result = kResultTrue;
			return result;
		}

		// ===================================================================================
		// processor�N���X�̏�Ԃ�ǂݍ��ފ֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTController::setComponentState(IBStream* state)
		{

			tresult res;

			// �ۑ�����Ă���f�[�^��ǂݍ���
			// �ۑ�����Ă���f�[�^����������ꍇ��state->read���J��Ԃ�
			ParamValue Lvolume, Rvolume, Lpan, Rpan;
			res = state->read(&Lvolume, sizeof(ParamValue));
			res = state->read(&Rvolume, sizeof(ParamValue));
			res = state->read(&Lpan, sizeof(ParamValue));
			res = state->read(&Rpan, sizeof(ParamValue));
			if (res != kResultOk)
			{
				// �Ǎ��Ɏ��s�����ꍇ��kResultFalse��Ԃ��B
				return kResultFalse;
			}

			// �ǂݍ��܂ꂽ�f�[�^���p�����[�^�ɔ��f����
			// ���f����f�[�^��0.0�`1.0�͈̔͂ɂ��Ă���
			Lvolume = plainParamToNormalized(L_VOLUME_TAG, Lvolume);
			setParamNormalized(L_VOLUME_TAG, Lvolume);
			Rvolume = plainParamToNormalized(R_VOLUME_TAG, Rvolume);
			setParamNormalized(R_VOLUME_TAG, Rvolume);
			Lpan = plainParamToNormalized(L_PAN_TAG, Lpan);
			setParamNormalized(L_PAN_TAG, Lpan);
			Rpan = plainParamToNormalized(R_PAN_TAG, Rpan);
			setParamNormalized(R_PAN_TAG, Rpan);

			// �֐��̏����ɖ�肪�Ȃ����kResultOk��Ԃ�
			return kResultOk;
		}

	}
}