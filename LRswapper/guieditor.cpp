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


			// コントローラーUIの追加---------------------------------
			
			createSlider(R_PAN_TAG, 150, 115);
			createSlider(L_PAN_TAG, 150, 165);
			
			//createSlider(L_VOLUME_TAG, 150, 100);
			//createSlider(R_VOLUME_TAG, 150, 150);

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
		// コントローラー操作時に呼ばれる関数
		// =================================================================================
		void MyVSTGUIEditor::valueChanged(CControl* pControl)
		{
			// どのパラメーターが操作されたかを取得する。
			int32 index = pControl->getTag();

			// パラメーターの値を取得する。
			float value = pControl->getValueNormalized();

			// 取得した値をパラメーターに反映させる
			controller->setParamNormalized(index, value);

			// 音声処理クラスに反映した値を通知する
			controller->performEdit(index, value);
		}

		// =================================================================================
		// スライダー作成関数
		// =================================================================================
		void MyVSTGUIEditor::createSlider(ParamID tag, int x, int y)
		{
			// 画像ファイルを読み込み
			CBitmap *backbmp = new CBitmap("hslider.png");
			CBitmap *handlebmp = new CBitmap("hslider_handle.png");

			// 画像サイズ取得
			CRect size;
			size(0, 0, backbmp->getWidth(), backbmp->getHeight());
			size.offset(x, y);   // 位置を設定(tergetframeの左上が0,0となる)

			// スライダーの作成
			//スライダーの背景にあわせて余白設定
			int bmpmargin = 0;
			CHorizontalSlider* control = new CHorizontalSlider(size, this, tag,
				x + bmpmargin,
				x + backbmp->getWidth() - (handlebmp->getWidth() + bmpmargin),
				handlebmp, backbmp);

			
			//右最大値に変更
			control->setStyle(CSlider::Style::kLeft | CSlider::Style::kHorizontal);

			// パラメータの現在の値を取得し、コントローラに反映
			ParamValue value = controller->getParamNormalized(tag);
			control->setValueNormalized(value);

			// スライダーをフレームに登録
			frame->addView(control);

			// 読み込んだ画像は忘れず解放
			backbmp->forget();
			handlebmp->forget();

		}
	}
}