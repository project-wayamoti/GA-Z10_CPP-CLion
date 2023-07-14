// 以下の行がないとコンパイルが通りません
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "option.h"

//## 環境に応じて設定
#define WIDTH 1280
#define HEIGHT 720
#define SPEED 1 // 移動速度 60Hz=8, 300Hz=1

void moveWASD(Vector2 *pVector2, Vector2 vector2);

void moveCross(Vector2 *pVector2, Vector2 vector2);

using namespace std;

// プログラムの最初はWinMainで始める
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### 初期設定 #####//
    // 画面設定
    ChangeWindowMode(TRUE); // ウィンドウモード設定
    SetGraphMode(WIDTH, HEIGHT, 32);
    SetWaitVSyncFlag(TRUE); // 垂直同期を有効にする

    //## 型宣言
    //## 固有の設定
    // 色の設定
    unsigned int charaColor = GetColor(255, 255, 255);

    // Vector2構造体の宣言
    // pPos1: 現在の座標, move: 移動量, moveVec: 移動ベクトル
    Vector2 pPos1, pPos2, move;

    // 移動物体初期設定
    pPos1.x = WIDTH / 2;  // 画面の中心に設定
    pPos1.y = HEIGHT / 2;
    pPos1.size = 32;      // 移動物体のサイズ
    pPos2.x = WIDTH / 2;  // 画面の中心に設定
    pPos2.y = HEIGHT / 2;
    pPos2.size = 32;      // 移動物体のサイズ
    move.x = SPEED; // 移動物体移動数値
    move.y = SPEED;

    // DXライブラリ初期化処理
    if (DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }

    //##### メインループ（描画処理） #####//
    while (ProcessMessage() == 0) {
        // 画面の更新
        ClearDrawScreen();

        //##### 中央物体の処理
        //球体移動処理 TRUE 塗りつぶし / FALSE 塗りつぶさない
        DrawCircle(pPos1.x, pPos1.y, pPos1.size, charaColor, TRUE);
        DrawCircle(pPos2.x, pPos2.y, pPos2.size, charaColor, TRUE);
        // WASDキーでpPos1を移動させる
        moveWASD(&pPos1, move);
        // 十字キーでpPos2を移動させる
        moveCross(&pPos2, move);

        //##### 描画処理

        // 画面の更新（必須）
        ScreenFlip(); // 画面を反転させる処理
        clsDx();      // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}

void moveCross(Vector2 *pVector2, Vector2 vector2) {
    // 十字キーでpPos2を移動させる
    if (CheckHitKey(KEY_INPUT_UP)) {
        pVector2->y -= vector2.y;
    }
    if (CheckHitKey(KEY_INPUT_DOWN)) {
        pVector2->y += vector2.y;
    }
    if (CheckHitKey(KEY_INPUT_LEFT)) {
        pVector2->x -= vector2.x;
    }
    if (CheckHitKey(KEY_INPUT_RIGHT)) {
        pVector2->x += vector2.x;
    }
}

// 移動処理
void moveWASD(Vector2 *pVector2, Vector2 vector2) {
    // WASDキーでpPos1を移動させる
    if (CheckHitKey(KEY_INPUT_W)) {
        pVector2->y -= vector2.y;
    }
    if (CheckHitKey(KEY_INPUT_S)) {
        pVector2->y += vector2.y;
    }
    if (CheckHitKey(KEY_INPUT_A)) {
        pVector2->x -= vector2.x;
    }
    if (CheckHitKey(KEY_INPUT_D)) {
        pVector2->x += vector2.x;
    }

}