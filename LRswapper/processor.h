// include VST3 SDK
#include "public.sdk/source/vst/vstaudioeffect.h"
#include "pluginterfaces/vst/ivstparameterchanges.h"
#include "pluginterfaces/base/ibstream.h"

namespace Steinberg {
	namespace Vst {

		// ===================================================================================
		// �����M������������Processor�N���X
		// ===================================================================================
		class MyVSTProcessor : public AudioEffect
		{
		protected:
			ParamValue Lvolume;
			ParamValue Rvolume;
			ParamValue Lpan;
			ParamValue Rpan;
		public:
			// �R���X�g���N�^
			MyVSTProcessor();

			// �������֐�
			tresult PLUGIN_API initialize(FUnknown* context);

			// �o�X�\��
			tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

			// processor�N���X�̏�Ԃ̓ǂݍ��݁A�ۑ�
			tresult PLUGIN_API setState(IBStream* state);
			tresult PLUGIN_API getState(IBStream* state);

			// �����M�������֐�
			tresult PLUGIN_API process(ProcessData& data);

			// ����VST Processor�N���X�̃C���X�^���X���쐬���邽�߂̊֐�
			static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
		};


	}
}