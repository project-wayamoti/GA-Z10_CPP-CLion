// 以下の行がないとコンパイルが通りません
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "utils.h"
#include "vector.h"

//## 環境に応じて設定
#define WIDTH 1280
#define HEIGHT 720
#define SPEED 8 // 移動速度 60Hz=8, 300Hz=1
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
    Vector2 TESTp, TESTm;
    Vector2 objMove, objPos1, objPos2, objPos3;

    // 移動物体初期設定
    pPos1.x = WIDTH / 2;  // 画面の中心に設定
    pPos1.y = HEIGHT / 2;
    pPos1.size = 32;      // 移動物体のサイズ
    pPos2.x = WIDTH / 2;  // 画面の中心に設定
    pPos2.y = HEIGHT / 2;
    pPos2.size = 32;      // 移動物体のサイズ
    move.x = SPEED; // 移動物体移動数値
    move.y = SPEED;

    int objSize = 8;
    objMove.x = SPEED;
    objMove.y = SPEED;
    objPos1.x = 100;
    objPos1.y = 100;
    objPos2.x = 200;
    objPos2.y = 200;
    objPos3.x = 300;
    objPos3.y = 300;

    //## ！！！実験用！！！
    TESTp.x = 800;
    TESTp.y = 600;
    TESTp.size = 8;
    TESTm.x = SPEED;
    TESTm.y = SPEED;
    //## ！！！実験用！！！

    // DXライブラリ初期化処理
    if (DxLib_Init() == -1) {
        return -1; // エラーが起きたら直ちに終了
    }

    //##### メインループ（描画処理） #####//
    while (ProcessMessage() == 0) {
        // 画面の更新
        ClearDrawScreen();

        //## ！！！実験用！！！
        // TESTpをpPos1とpPos2の間にいる場合線の中心が進んでいる向きに対して移動させる
        //DrawCircle(TESTp.x, TESTp.y, TESTp.size, charaColor, TRUE);

        // 相対ベクトル計算
        Vector2 relativeVector1 = getRelativeVector(pPos1, pPos2);
        Vector2 relativeVector2 = getRelativeVector(pPos1, TESTp);
        Vector2 relativeVector3 = getRelativeVector(pPos2, pPos1);
        Vector2 relativeVector4 = getRelativeVector(pPos2, TESTp);

        //外積と内積を計算
        Vector2 RV1Normal = getNormalizedVector(relativeVector1);
        Vector2 RV2Normal = getNormalizedVector(relativeVector2);
        float cross = mathCross (RV1Normal, relativeVector2);
        if(cross < 0) cross *= -1; //外積の絶対値を取得

        float dotV1 = mathDot (relativeVector1, relativeVector2);
        float dotV2 = mathDot (relativeVector3, relativeVector4);

        //##### 当たり判定
        if(dotV1 > 0 && dotV2 > 0 && cross < TESTp.size){
            printfDx("当たった\n");
            charaColor = GetColor(255, 0, 0);

            // あたったら計算
            Vector2 NNSVector = getNearestNeighbor(pPos1, pPos2, TESTp);
            printfDx("NNSVector.x = %f\n", NNSVector.x);
            printfDx("NNSVector.y = %f\n", NNSVector.y);

            // 計算したやつ正規化
            Vector2 NNSVectorNormal = getNormalizedVector(NNSVector);

            // あたったら移動
            TESTp.x += NNSVectorNormal.x;
            TESTp.y += NNSVectorNormal.y;
        }
        else {
            charaColor = GetColor(255, 255, 255);
        }

        // 押し出される物体
        DrawCircle(TESTp.x, TESTp.y, TESTp.size, GetColor(0, 255, 0), TRUE);

        //## ！！！実験用！！！

        //##### 操作可能な球体の移動処理
        moveBall (&pPos2, move, 1); // 十字キーでpPos2を移動させる
        moveBall (&pPos1, move, 2); // WASDキーでpPos1を移動させる

        // デバッグ
        //printfDx();

        //外積が正の時は時計回り、負の時は反時計回り
        if (cross > 0) {
            printfDx("時計回り\n");
        }
        else if (cross < 0) {
            printfDx("反時計回り\n");
        }
        else {
            printfDx("直線\n");
        }

        //内積が正の時は鈍角、負の時は鋭角
        if (dotV1 > 0) {
            printfDx("鈍角\n");
        }
        else if (dotV1 < 0) {
            printfDx("鋭角\n");
        }
        else {
            printfDx("直角\n");
        }

        //##### デバッグ用 #####
        printfDx("pPos1.x = %f\n", pPos1.x);
        printfDx("pPos1.y = %f\n", pPos1.y);
        printfDx("pPos2.x = %f\n", pPos2.x);
        printfDx("pPos2.y = %f\n", pPos2.y);
        printfDx("TESTp.x = %f\n", TESTp.x);
        printfDx("TESTp.y = %f\n", TESTp.y);
        printfDx("cross = %f\n", cross);
        printfDx("dotV1 = %f\n", dotV1);
        printfDx("dotV2 = %f\n", dotV2);
        //##### デバッグ用 #####

        //##### 描画処理
        //操作可能な球体の移動処理 TRUE 塗りつぶし / FALSE 塗りつぶさない
        DrawCircle(pPos1.x, pPos1.y, pPos1.size, charaColor, TRUE);
        DrawCircle(pPos2.x, pPos2.y, pPos2.size, charaColor, TRUE);
        //操作可能な球体同士を線でつなげる
        DrawLine(pPos1.x, pPos1.y, pPos2.x, pPos2.y, charaColor);

        //最近傍点の点を表示
        Vector2 NNSVectorN = getNearestNeighbor(pPos1, pPos2, TESTp);
        // 内積を計算する
        float dot = mathDot (RV1Normal, TESTp);
        Vector2 V3 = getNormalizedVector(relativeVector1);
        // 最近傍点を計算する
        Vector2 nearestNeighbor = {
                relativeVector1.x + (V3.x * dot),
                relativeVector1.y + (V3.y * dot)
        };

        printfDx("NNSVectorN.x = %f\n", NNSVectorN.x);
        printfDx("NNSVectorN.y = %f\n", NNSVectorN.y);
        printfDx("nearestNeighbor.x = %f\n", nearestNeighbor.x);
        printfDx("nearestNeighbor.y = %f\n", nearestNeighbor.y);
        printfDx("V3.x = %f\n", V3.x);
        printfDx("V3.y = %f\n", V3.y);
        printfDx("dot = %f\n", dot);

        DrawCircle (NNSVectorN.x, NNSVectorN.y, 5, GetColor (255, 0, 0), TRUE);

        // 画面の更新（必須）
        ScreenFlip(); // 画面を反転させる処理
        clsDx();      // デバッグログ画面をクリアする処理
    }

    DxLib_End(); // DX Libraryの使用を終了する処理
    return 0;    // ソフトを正常終了
}