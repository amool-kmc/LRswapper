// include original file
#include "guieditor.h"

// 危険かもしれない
using namespace VSTGUI;

namespace Steinberg {
	namespace Vst {
		// =================================================================================
		// コンストラクタ
		// =================================================================================
		MyVSTGUIEditor::MyVSTGUIEditor(void* controller) 
			: VSTGUIEditor(controller)
		{
			// ウィンドウサイズを設定
			// 設定しなければ、ウィンドウが開かない
			ViewRect viewRect(0, 0, H_WINDOWSIZE, V_WINDOWSIZE);
			setRect(viewRect);
		}

		// =================================================================================
		// open時に呼ばれる関数
		// =================================================================================
		bool PLUGIN_API MyVSTGUIEditor::open(void* parent, const PlatformType& platformType)
		{
			// GUIウィンドウが開かれたときに、UIを作成する

			// フレーム(配置領域)がすでに作成・設定されている場合(frameがNULLでない場合)は終了
			// frameは継承元クラスで定義されている。
			if (frame) { return false; }

			// 作成するフレームのサイズを設定（基本的にGUIウィンドウと同じ）
			CRect size(0, 0, H_WINDOWSIZE, V_WINDOWSIZE);

			// フレームを作成。作成に失敗したら(NULLなら)終了。
			// 引数には、フレームサイズ、自作GUIクラスのポインタを指定する
			frame = new CFrame(size, this);
			if (frame == NULL) { return false; }

			// 作成したフレームに背景画像を設定
			CBitmap* cbmp = new CBitmap("background.png"); // リソースから背景画像を読み込む
			frame->setBackground(cbmp); // フレームに背景画像を設定
			cbmp->forget();	// フレームに設定後は背景画像はforgetで解放しておく

			// 作成したフレームを開く
			frame->open(parent);

			// GUIウィンドウのオープンに成功した場合はtrueを返す
			return true;
		}

		// =================================================================================
		// close時に呼ばれる関数
		// =================================================================================
		void PLUGIN_API MyVSTGUIEditor::close()
		{
			// GUIウィンドウが閉じたときに、UIを削除する

			// フレームを解放
			// 背景画像や追加したつまみ(ノブ）やスライダーなどもあわせて解放される
			if (frame)
			{
				frame->forget();
				frame = 0;
			}
		}

		// =================================================================================
		// コントローラー操作時時に呼ばれる関数
		// =================================================================================
		void MyVSTGUIEditor::valueChanged(CControl* pControl)
		{
		}
	}
}