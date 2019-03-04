// include VST3 SDK
#include "public.sdk/source/vst/vstaudioeffect.h"


namespace Steinberg {
	namespace Vst {

		// ===================================================================================
		// �����M������������Processor�N���X
		// ===================================================================================
		class MyVSTProcessor : public AudioEffect
		{
		public:
			// �������֐�
			tresult PLUGIN_API initialize(FUnknown* context);

			// �o�X�\��
			tresult PLUGIN_API setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts);

			// �����M�������֐�
			tresult PLUGIN_API process(ProcessData& data);

			// ����VST Processor�N���X�̃C���X�^���X���쐬���邽�߂̊֐�
			static FUnknown* createInstance(void*) { return (IAudioProcessor*)new MyVSTProcessor(); }
		};


	}
}