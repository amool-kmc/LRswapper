// include original file
#include "fuidlist.h"
#include "processor.h"
#include "controller.h"


namespace Steinberg {
	namespace Vst {

		// =================================================================================
		// �R���X�g���N�^
		// =================================================================================
		MyVSTProcessor::MyVSTProcessor()
			// �p�����[�^�[�̏����l
			:Lvolume(0.0f), Rvolume(0.0f), Lpan(-100.0f), Rpan(100.0f)
		{
			// �R���g���[���[��FUID��ݒ�
			setControllerClass(ControllerUID);
		}

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
		// ��Ԃ�ǂݍ��ފ֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::setState(IBStream* state)
		{
			// �ۑ��f�[�^��ǂݍ���
			// �ۑ��f�[�^����������ꍇ��state->read���J��Ԃ�
			tresult res;
			res = state->read(&Lvolume, sizeof(ParamValue));
			res = state->read(&Rvolume, sizeof(ParamValue));
			res = state->read(&Lpan, sizeof(ParamValue));
			res = state->read(&Rpan, sizeof(ParamValue));
			if (res != kResultOk)
			{
				// �Ǎ��Ɏ��s�����ꍇ��kResultFalse��Ԃ��B
				return kResultFalse;
			}

			return kResultOk;
		}

		// ===================================================================================
		// ��Ԃ�ۑ�����֐�
		// ===================================================================================
		tresult PLUGIN_API MyVSTProcessor::getState(IBStream* state)
		{
			// �f�[�^��ۑ�����
			// �ۑ��������f�[�^����������ꍇ��state->write���J��Ԃ��B
			state->write(&Lvolume, sizeof(ParamValue));
			state->write(&Rvolume, sizeof(ParamValue));
			state->write(&Lpan, sizeof(ParamValue));
			state->write(&Rpan, sizeof(ParamValue));

			// �֐��̏����ɖ�肪�Ȃ����kResultOk��Ԃ�
			return kResultOk;
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
						if (queue->getPoint(valueCgangeCount - 1, sampleOffset, value) == kResultTrue) {
							// tag���Ƃ̒l�n���A����(���̂܂ܓn������K�i�����ꂽ�܂�)�ǂݏ������l����ƃp�����[�^�[�̒l�ɖ߂��ׂ���
							switch (tag)
							{
							case L_VOLUME_TAG:
								Lvolume = value * 30 - 20; // -20~10
								break;
							case R_VOLUME_TAG:
								Rvolume = value * 30 - 20; // -20~10
								break;
							case L_PAN_TAG:
								Lpan = value * 200 - 100; // -100~100
								break;
							case R_PAN_TAG:
								Rpan = value * 200 - 100; // -100~100
								break;
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
				inLoutR = ((Lpan + 100) / 200) * inL[i];
				inLoutL = -((Lpan + 100) / 200 - 1) * inL[i];
				inRoutL = -((Rpan + 100) / 200 - 1) * inR[i];
				inRoutR = ((Rpan + 100) / 200) * inR[i];

				outL[i] = ((Lvolume + 20) / 20) * (inLoutL + inRoutL);
				outR[i] = ((Rvolume + 20) / 20) * (inLoutR + inRoutR);
			}

			
			return kResultTrue;
		}

	}
} 