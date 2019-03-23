// include original file
#include "guieditor.h"

// �댯��������Ȃ�
using namespace VSTGUI;

namespace Steinberg {
	namespace Vst {
		// =================================================================================
		// �R���X�g���N�^
		// =================================================================================
		MyVSTGUIEditor::MyVSTGUIEditor(void* controller) 
			: VSTGUIEditor(controller)
		{
			// �E�B���h�E�T�C�Y��ݒ�
			// �ݒ肵�Ȃ���΁A�E�B���h�E���J���Ȃ�
			ViewRect viewRect(0, 0, H_WINDOWSIZE, V_WINDOWSIZE);
			setRect(viewRect);
		}

		// =================================================================================
		// open���ɌĂ΂��֐�
		// =================================================================================
		bool PLUGIN_API MyVSTGUIEditor::open(void* parent, const PlatformType& platformType)
		{
			// GUI�E�B���h�E���J���ꂽ�Ƃ��ɁAUI���쐬����

			// �t���[��(�z�u�̈�)�����łɍ쐬�E�ݒ肳��Ă���ꍇ(frame��NULL�łȂ��ꍇ)�͏I��
			// frame�͌p�����N���X�Œ�`����Ă���B
			if (frame) { return false; }

			// �쐬����t���[���̃T�C�Y��ݒ�i��{�I��GUI�E�B���h�E�Ɠ����j
			CRect size(0, 0, H_WINDOWSIZE, V_WINDOWSIZE);

			// �t���[�����쐬�B�쐬�Ɏ��s������(NULL�Ȃ�)�I���B
			// �����ɂ́A�t���[���T�C�Y�A����GUI�N���X�̃|�C���^���w�肷��
			frame = new CFrame(size, this);
			if (frame == NULL) { return false; }

			// �쐬�����t���[���ɔw�i�摜��ݒ�
			CBitmap* cbmp = new CBitmap("background.png"); // ���\�[�X����w�i�摜��ǂݍ���
			frame->setBackground(cbmp); // �t���[���ɔw�i�摜��ݒ�
			cbmp->forget();	// �t���[���ɐݒ��͔w�i�摜��forget�ŉ�����Ă���

			// �쐬�����t���[�����J��
			frame->open(parent);

			// GUI�E�B���h�E�̃I�[�v���ɐ��������ꍇ��true��Ԃ�
			return true;
		}

		// =================================================================================
		// close���ɌĂ΂��֐�
		// =================================================================================
		void PLUGIN_API MyVSTGUIEditor::close()
		{
			// GUI�E�B���h�E�������Ƃ��ɁAUI���폜����

			// �t���[�������
			// �w�i�摜��ǉ������܂�(�m�u�j��X���C�_�[�Ȃǂ����킹�ĉ�������
			if (frame)
			{
				frame->forget();
				frame = 0;
			}
		}

		// =================================================================================
		// �R���g���[���[���쎞���ɌĂ΂��֐�
		// =================================================================================
		void MyVSTGUIEditor::valueChanged(CControl* pControl)
		{
		}
	}
}