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


			// �R���g���[���[UI�̒ǉ�---------------------------------
			createHSlider(R_PAN_TAG, 150, 127);
			createHSlider(L_PAN_TAG, 150, 177);
			createVSlider(R_VOLUME_TAG, 690, 265);
			createVSlider(L_VOLUME_TAG, 290, 265);

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
		// �R���g���[���[���쎞�ɌĂ΂��֐�
		// =================================================================================
		void MyVSTGUIEditor::valueChanged(CControl* pControl)
		{
			// �ǂ̃p�����[�^�[�����삳�ꂽ�����擾����B
			int32 index = pControl->getTag();

			// �p�����[�^�[�̒l���擾����B
			float value = pControl->getValueNormalized();

			// �擾�����l���p�����[�^�[�ɔ��f������
			controller->setParamNormalized(index, value);

			// ���������N���X�ɔ��f�����l��ʒm����
			controller->performEdit(index, value);
		}

		// =================================================================================
		// ���^�X���C�_�[�쐬�֐�
		// =================================================================================
		CControl* MyVSTGUIEditor::createHSlider(ParamID tag, int x, int y)
		{
			// �摜�t�@�C����ǂݍ���
			CBitmap *backbmp = new CBitmap("hslider.png");
			CBitmap *handlebmp = new CBitmap("hslider_handle.png");

			// �摜�T�C�Y�擾
			CRect size;
			size(0, 0, backbmp->getWidth(), backbmp->getHeight());
			size.offset(x, y);   // �ʒu��ݒ�(tergetframe�̍��オ0,0�ƂȂ�)

			// �X���C�_�[�̍쐬
			// �X���C�_�[�̔w�i�ɂ��킹�ė]���ݒ�
			int bmpmargin = 0;
			CHorizontalSlider* control = new CHorizontalSlider(size, this, tag,
				x + bmpmargin,
				x + backbmp->getWidth() - (handlebmp->getWidth() + bmpmargin),
				handlebmp, backbmp);


			// �n���h���̓�����������E��
			control->setStyle(CSlider::Style::kLeft | CSlider::Style::kHorizontal);

			// �p�����[�^�̌��݂̒l���擾���A�R���g���[���ɔ��f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// �X���C�_�[���t���[���ɓo�^
			frame->addView(control);

			// �ǂݍ��񂾉摜�͖Y�ꂸ���
			backbmp->forget();
			handlebmp->forget();

			return control;
		}

		// =================================================================================
		// �c�^�X���C�_�[�쐬�֐�
		// =================================================================================
		CControl* MyVSTGUIEditor::createVSlider(ParamID tag, int x, int y)
		{
			// �摜�t�@�C����ǂݍ���
			CBitmap *backbmp = new CBitmap("vslider.png");
			CBitmap *handlebmp = new CBitmap("vslider_handle.png");

			// �摜�T�C�Y�擾
			CRect size;
			size(0, 0, backbmp->getWidth(), backbmp->getHeight());
			size.offset(x, y);   // �ʒu��ݒ�(tergetframe�̍��オ0,0�ƂȂ�)

			// �X���C�_�[�̍쐬
			// �X���C�_�[�̔w�i�ɂ��킹�ė]���ݒ�
			int bmpmargin = 0;
			CVerticalSlider* control = new CVerticalSlider(size, this, tag,
				y + bmpmargin,
				y + backbmp->getHeight() - (handlebmp->getHeight() + bmpmargin),
				handlebmp, backbmp);

			// �p�����[�^�̌��݂̒l���擾���A�R���g���[���ɔ��f
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// �m�u���t���[���ɓo�^
			frame->addView(control);

			// �ǂݍ��񂾉摜�͖Y�ꂸ���
			backbmp->forget();
			handlebmp->forget();

			return control;
		}

		CControl* MyVSTGUIEditor::createTextLabel(int x, int y, UTF8StringPtr text)
		{
			// �e�L�X�g���x���R���g���[�����쐬����

			// �R���g���[���̃T�C�Y��ݒ�(�T�C�Y�͓K��)
			CRect  size;
			size(0, 0, 80, 16);
			size.offset(x, y);   // �ʒu��ݒ�(frame�̍��オ0,0�ƂȂ�)

			// �R���g���[���쐬
			CTextLabel* control = new CTextLabel(size, text);

			// ���^�t�H���g���w��
			control->setFont(kNormalFontSmaller);

			// �����F�E�w�i�F��ݒ�
			control->setFontColor(kBlackCColor);
			control->setBackColor(kWhiteCColor);
			control->setFrameColor(kGreyCColor);

			// �R���g���[�����t���[���ɓo�^
			frame->addView(control);

			return control;
		}
	}
}