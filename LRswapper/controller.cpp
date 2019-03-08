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
				RangeParameter* Rvolume = new RangeParameter(STR16("Rvolume"), L_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);

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


	}
}