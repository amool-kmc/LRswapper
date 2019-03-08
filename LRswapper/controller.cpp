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
				// �p�����[�^�[��ǉ�
				// output gain
				RangeParameter* Lvolume = new RangeParameter(STR16("Lvolume"), L_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);
				RangeParameter* Rvolume = new RangeParameter(STR16("Rvolume"), L_VOLUME_TAG, STR16(""), -20.0f, 10.0f, 0.0f);

				//pan
				RangeParameter* Lpan = new RangeParameter(STR16("Lpan"), L_VOLUME_TAG, STR16(""), -1.0f, 1.0f, -1.0f);
				RangeParameter* Rpan = new RangeParameter(STR16("Rpan"), L_VOLUME_TAG, STR16(""), -1.0f, 1.0f, 1.0f);


				// �ȉ��ŗL�̏����������{�B
				
			}

			
			result = kResultTrue;
			return result;
		}


	}
}