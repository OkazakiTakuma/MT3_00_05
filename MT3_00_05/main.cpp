#include "Matrix.h"
#include"Vector3.h"
#include <Novice.h>
const char kWindowTitle[] = "LD2B_01_オカザキ_タクマ";
static const int kRowHeight = 20;
static const int kColumnWidth = 60;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	Vector3 scale{1.2f, 0.79f, -2.1f};
	Vector3 rotate{0.4f, 1.43f, -0.8f};
	Vector3 translate{2.7f, -4.15f, 1.57f};
	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		Matrix4x4 rotateMatrix = MakeRotateXYZMatrix(rotate);
		Matrix4x4 worldMatrix = MakeAffineMatrix(scale, rotate, translate);
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		MatrixScreenPrintf(0, 0, worldMatrix, "worldMatrix");
		MatrixScreenPrintf(0, kRowHeight * 5, rotateMatrix, "rotateMatrix");
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
