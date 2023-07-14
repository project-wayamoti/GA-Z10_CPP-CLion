// 以下の行がないとコンパイルが通りません
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "option.h"

//## 環境に応じて設定
#define WIDTH 1280
#define HEIGHT 720
#define SPEED 1 // 移動速度 60Hz=8, 300Hz=1
using namespace std;

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    // 画面設定
    ChangeWindowMode(TRUE); // ウィンドウモード設定
    SetGraphMode(WIDTH, HEIGHT, 32);
    SetWaitVSyncFlag(TRUE); // 垂直同期を有効にする

    // DXライブラリ初期化処理
    if (DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }

    //## 固有の設定
    // 色の設定
    unsigned int charaColor = GetColor(255, 255, 255);

    // Vector2構造体の宣言
    // pos: 現在の座標, move: 移動量, moveVec: 移動ベクトル
    Vector2 pos, move;

    // 移動物体初期設定
    pos.x = WIDTH / 2;  // 画面の中心に設定
    pos.y = HEIGHT / 2;
    pos.size = 32;      // 移動物体のサイズ
    move.x = SPEED; // 移動物体移動数値
    move.y = SPEED;

    //##### メインループ（描画処理） #####//
    while (ProcessMessage() == 0) {
        // 画面の更新
        ClearDrawScreen();

        //##### 中央物体の処理
        //球体移動処理 TRUE 塗りつぶし / FALSE 塗りつぶさない
        DrawCircle(pos.x, pos.y, pos.size, charaColor, TRUE);
        // WASDキーでposを移動させる
        if (CheckHitKey(KEY_INPUT_W)) {
            pos.y -= move.y;
        }
        if (CheckHitKey(KEY_INPUT_S)) {
            pos.y += move.y;
        }
        if (CheckHitKey(KEY_INPUT_A)) {
            pos.x -= move.x;
        }
        if (CheckHitKey(KEY_INPUT_D)) {
            pos.x += move.x;
        }

        //##### 描画処理

        // 画面の更新（必須）
        ScreenFlip(); // 画面を反転させる処理
        clsDx();      // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}