#ifndef __GUIEDITOR_H__
#define __GUIEDITOR_H__

// VST3 SDK
#include "public.sdk/source/vst/vstguieditor.h"
#include "pluginterfaces/vst/ivstplugview.h"

// include original file
#include "tag.h"


// VST3�쐬�ɕK�v�Ȃ̖��O��Ԃ��g�p
namespace Steinberg {
	namespace Vst {

		// ============================================================================================
		// VST��GUI�N���X
		// ============================================================================================
		class MyVSTGUIEditor : public VSTGUIEditor, public VSTGUI::IControlListener
		{
		public:
			// �R���X�g���N�^
			MyVSTGUIEditor(void* controller);

			// GUI�E�B���h�E���J�����Ƃ��ɌĂяo�����֐�
			virtual bool PLUGIN_API open(void* parent, const VSTGUI::PlatformType& platformType = VSTGUI::kDefaultNative);

			// GUI�E�B���h�E������Ƃ��ɌĂяo�����֐�
			virtual void PLUGIN_API close();

			// GUI�E�B���h�E�̃R���g���[���𑀍삵���Ƃ��ɌĂяo�����֐�
			void valueChanged(VSTGUI::CControl* pControl);

			// VSTGUIEditor�N���X�̊e��ݒ������GUI�N���X�u��������}�N��
			DELEGATE_REFCOUNT(VSTGUIEditor)
		};

	}
} // namespace Steinberg��Vst�̏I���

#endif