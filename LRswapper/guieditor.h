#ifndef __GUIEDITOR_H__
#define __GUIEDITOR_H__

// VST3 SDK
#include "public.sdk/source/vst/vstguieditor.h"
#include "pluginterfaces/vst/ivstplugview.h"

// include original file
#include "tag.h"


// VST3作成に必要なの名前空間を使用
namespace Steinberg {
	namespace Vst {

		// ============================================================================================
		// VSTのGUIクラス
		// ============================================================================================
		class MyVSTGUIEditor : public VSTGUIEditor, public VSTGUI::IControlListener
		{
		public:
			// コンストラクタ
			MyVSTGUIEditor(void* controller);

			// GUIウィンドウを開いたときに呼び出される関数
			virtual bool PLUGIN_API open(void* parent, const VSTGUI::PlatformType& platformType = VSTGUI::kDefaultNative);

			// GUIウィンドウを閉じたときに呼び出される関数
			virtual void PLUGIN_API close();

			// GUIウィンドウのコントローラを操作したときに呼び出される関数
			void valueChanged(VSTGUI::CControl* pControl);

			// VSTGUIEditorクラスの各種設定を自作GUIクラス置き換えるマクロ
			DELEGATE_REFCOUNT(VSTGUIEditor)
		};

	}
} // namespace SteinbergとVstの終わり

#endif