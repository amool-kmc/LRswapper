// VST3 SDK�̃C���N���[�h�t�@�C��
#include "public.sdk/source/main/pluginfactoryvst3.h"

// ����VST�̃w�b�_�t�@�C�����C���N���[�h
#include "fuidlist.h"
#include "processor.h"
#include "controller.h"

#define MYVST_VENDOR   "amool"

#define MYVST_URL      "https://mahoroba-music.work"

// �����(������)�̘A���惁�[���A�h���X�B�I�[�����u\0�v�܂߂�128�����܂ŁB
#define MYVST_EMAIL    "hitotsutesh@yahoo.co.jp"

// ���삷��VST�̖��O�B�I�[�����u\0�v�܂߂�64�����܂ŁB
#define MYVST_VSTNAME  "LRswapper"

// ���삷��VST�̃o�[�W�����B�I�[�����u\0�v�܂߂�64�����܂ŁB
#define MYVST_VERSION  "0" 

// ���삷��VST�̃J�e�S���B�I�[�����u\0�v�܂߂�64�����܂ŁB
#define MYVST_SUBCATEGORIES Vst::PlugType::kFx


// ===================================================================================
// DLL�t�@�C���̏������A�I�������֐�
// ===================================================================================
// ��{�I�ɉ�������K�v�͂Ȃ��B
bool InitModule() { return true; }
bool DeinitModule() { return true; }


// ===================================================================================
// ����VST�v���O�C���̐���
// ===================================================================================
BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

	// Processor�N���X�̍쐬
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ProcessorUID),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		MYVST_VSTNAME,
		Vst::kDistributable,
		MYVST_SUBCATEGORIES,
		MYVST_VERSION,
		kVstVersionString,
		Steinberg::Vst::MyVSTProcessor::createInstance)

	// Controller�N���X�̍쐬���s��
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ControllerUID),
		PClassInfo::kManyInstances,
		kVstComponentControllerClass,
		MYVST_VSTNAME " Controller",	// ����VST�̖��O��"Controller"��t�^�������́B
		0,						    // �g��Ȃ��̂ŕK��0�ɂ���
		"",						    // �g��Ȃ��̂ŕK��""�ɂ���
		MYVST_VERSION,
		kVstVersionString,
		Steinberg::Vst::MyVSTController::createInstance)

END_FACTORY