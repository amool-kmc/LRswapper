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
				parameters.addParameter(STR16("param1"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, L_VOLUME_TAG);
				parameters.addParameter(STR16("param1"), STR16("..."), 0, 1, ParameterInfo::kCanAutomate, R_VOLUME_TAG);


				// �ȉ��ŗL�̏����������{�B
				
			}

			
			result = kResultTrue;
			return result;
		}


	}
}