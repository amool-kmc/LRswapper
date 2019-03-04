// VST3 SDKのインクルードファイル
#include "public.sdk/source/main/pluginfactoryvst3.h"

// 自作VSTのヘッダファイルをインクルード
#include "fuidlist.h"
#include "processor.h"
#include "controller.h"

#define MYVST_VENDOR   "amool"

#define MYVST_URL      "https://mahoroba-music.work"

// 製作者(製作会社)の連絡先メールアドレス。終端文字「\0」含めて128文字まで。
#define MYVST_EMAIL    "hitotsutesh@yahoo.co.jp"

// 自作するVSTの名前。終端文字「\0」含めて64文字まで。
#define MYVST_VSTNAME  "LRswapper"

// 自作するVSTのバージョン。終端文字「\0」含めて64文字まで。
#define MYVST_VERSION  "0" 

// 自作するVSTのカテゴリ。終端文字「\0」含めて64文字まで。
#define MYVST_SUBCATEGORIES Vst::PlugType::kFx


// ===================================================================================
// DLLファイルの初期化、終了処理関数
// ===================================================================================
// 基本的に何もする必要はない。
bool InitModule() { return true; }
bool DeinitModule() { return true; }


// ===================================================================================
// 自作VSTプラグインの生成
// ===================================================================================
BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

	// Processorクラスの作成
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ProcessorUID),
		PClassInfo::kManyInstances,
		kVstAudioEffectClass,
		MYVST_VSTNAME,
		Vst::kDistributable,
		MYVST_SUBCATEGORIES,
		MYVST_VERSION,
		kVstVersionString,
		Steinberg::Vst::MyVSTProcessor::createInstance)

	// Controllerクラスの作成を行う
	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ControllerUID),
		PClassInfo::kManyInstances,
		kVstComponentControllerClass,
		MYVST_VSTNAME " Controller",	// 自作VSTの名前に"Controller"を付与したもの。
		0,						    // 使わないので必ず0にする
		"",						    // 使わないので必ず""にする
		MYVST_VERSION,
		kVstVersionString,
		Steinberg::Vst::MyVSTController::createInstance)

END_FACTORY