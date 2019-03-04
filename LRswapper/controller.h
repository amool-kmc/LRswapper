// include VST3 SDK file
#include "public.sdk/source/vst/vsteditcontroller.h"


// include original file
#include "tag.h"


// VST3�쐬�ɕK�v�Ȗ��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {


		// ===================================================================================
		// Controller�N���X
		// ===================================================================================
		class MyVSTController : public EditController
		{
		public:
			// �N���X�������֐�
			tresult PLUGIN_API initialize(FUnknown* context);

			// ����Controller�N���X�̃C���X�^���X���쐬���邽�߂̊֐�
			static FUnknown* createInstance(void*) { return (IEditController*)new MyVSTController(); }

		};


	}
}