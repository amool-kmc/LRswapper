// include VST3 SDK file
#include "public.sdk/source/vst/vsteditcontroller.h"
#include "pluginterfaces/base/ibstream.h"


// include original file
#include "tag.h"
#include "guieditor.h"


// VST3作成に必要な名前空間を使用
namespace Steinberg {
	namespace Vst {


		// ===================================================================================
		// Controllerクラス
		// ===================================================================================
		class MyVSTController : public EditController
		{
		public:
			// クラス初期化関数
			tresult PLUGIN_API initialize(FUnknown* context);

			// Processorクラスの保存状態を反映させる関数
			tresult PLUGIN_API setComponentState(IBStream* state);

			// 自作VST GUIEditorを作成する関数
			IPlugView* PLUGIN_API createView(const char* name);

			// 自作Controllerクラスのインスタンスを作成するための関数
			static FUnknown* createInstance(void*) { return (IEditController*)new MyVSTController(); }

		};


	}
}