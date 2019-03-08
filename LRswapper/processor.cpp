// include original file
#include "fuidlist.h"
#include "processor.h"
#include "controller.h"


namespace Steinberg {
	namespace Vst {


		// ===================================================================================
		// �N���X�������֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::initialize(FUnknown* context)
		{
			// �p�����N���X������
			tresult result = AudioEffect::initialize(context);
			if (result == kResultTrue)
			{
				// ���͂Əo�͂�ݒ�
				addAudioInput(STR16("AudioInput"), SpeakerArr::kStereo);
				addAudioOutput(STR16("AudioOutput"), SpeakerArr::kStereo);

				// ���̑��̏�����

				
			}


			
			return result;
		}

		// ===================================================================================
		// �o�X�\�������߂�֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::setBusArrangements(SpeakerArrangement* inputs, int32 numIns, SpeakerArrangement* outputs, int32 numOuts)
		{
			//�o�X�\��
			if (numIns == 1 && numOuts == 1 && inputs[0] == SpeakerArr::kStereo && outputs[0] == SpeakerArr::kStereo)
			{
				return AudioEffect::setBusArrangements(inputs, numIns, outputs, numOuts);
			}

			// �Ή����Ă��Ȃ��o�X�\���̏ꍇ�AkResultFalse��Ԃ��B
			return kResultFalse;
		}

		// ===================================================================================
		// �����M������������֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::process(ProcessData& data)
		{
			// �p�����[�^�[�ύX���̏���
			if (data.inputParameterChanges != NULL) {
				// ���̓p�����[�^�[���擾
				int32 paramChangeCount = data.inputParameterChanges->getParameterCount();

				// ���̓p�����[�^�[����������
				for (int32 i = 0; i < paramChangeCount; i++) {
					// �ύX�p�����[�^�[�̎�ނ̏��L���[
					IParamValueQueue* queue = data.inputParameterChanges->getParameterData(i);

					if (queue != NULL) {
						// �p�����[�^�[tag�擾
						int32 tag = queue->getParameterId();
						// �ύX��
						int32 valueCgangeCount = queue->getPointCount();

						// �p�����[�^�[�̒l�ƃI�t�Z�b�g
						ParamValue value;
						int32 sampleOffset;

						// �Ō�̒l�̂ݎ擾����
						if (queue->getPoint(valueCgangeCount - 1, sampleOffset, value)) {
							// tag���Ƃ̒l�n���A����(���̂܂ܓn������K�i�����ꂽ�܂�)
							switch (tag)
							{
							case L_VOLUME_TAG:
								Lvolume = value;
								break;
							case R_VOLUME_TAG:
								Rvolume = value;
								break;
							case L_PAN_TAG:
								Lpan = -(value - 1); // 0~1
							case R_PAN_TAG:
								Rpan = value; // 0~1
							}
						}
					}
				}
			}
			// ���́E�o�̓o�b�t�@�̃|�C���^
			Sample32* inL = data.inputs[0].channelBuffers32[0];
			Sample32* inR = data.inputs[0].channelBuffers32[1];
			Sample32* outL = data.outputs[0].channelBuffers32[0];
			Sample32* outR = data.outputs[0].channelBuffers32[1];

			// numSamples�Ŏ������T���v�����A��������������
			for (int32 i = 0; i < data.numSamples; i++)
			{
				Sample32 inLoutL, inLoutR, inRoutL, inRoutR;
				inLoutL = Lpan * inL[i];
				inLoutR = -(Lpan - 1) * inL[i];
				inRoutL = -(Rpan - 1)*inR[i];
				inRoutR = Rpan * inR[i];

				outL[i] = inLoutL + inRoutL;
				outR[i] = inLoutR + inRoutR;
			}

			
			return kResultTrue;
		}

	}
} 