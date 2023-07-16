//
// Created by waya on 2023/07/14.
//

#ifndef UTILS_CLASS_H_
#define UTILS_CLASS_H_

#pragma once
#include <cmath>
#include <random>
#include "vector.h"
using namespace std;

/**
 * 2つの円の中心座標の距離を計算する関数\n
 * 参考文献: https://www.geisya.or.jp/~mwm48961/math/distance1j.htm
 * @param v1 対象にしたい円の中央座標1
 * @param v2 対象にしたい円の中央座標2
 * @return 2つの円の中心座標の距離
 * @notes sqrt関数を使用するため、この関数を他で使う場合は"math.h"or"cmath"をincludeする必要がある
 * @notes ただし今回の場合floatで返す必要があるため、sqrtf関数を使用している。
 */
float getBallDistance(const Vector2& v1, const Vector2& v2) {
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    // 目的の地点 - 現在の地点
    Vector2 diff = { v1.x - v2.x, v1.y - v2.y };
    // 2つの円の中心座標の距離を計算
    return sqrtf(powf(diff.x, 2) + powf(diff.y, 2));
}

/**
 * 外積を計算する\n
 * 参考文献: ゲームアルゴリズム Z07 7ページ目資料
 * @param start 始点の座標
 * @param end 終点の座標
 * @return 外積(float)
 */
float mathCross(const Vector2& start, const Vector2& end) {
    return (float)start.x * end.y - start.y * end.x;
}

/**
 * 内積を計算する\n
 * 参考文献: ゲームアルゴリズム Z07 12ページ目資料
 * @param start 始点の座標
 * @param end 終点の座標
 * @return 内積(float)
 */
float mathDot(const Vector2& start, const Vector2& end) {
    return (float)start.x * end.x + start.y * end.y;
}

/**
 * 点と点の間かどうかを判定する\n
 * 参考文献: なし
 * @param start 始点の座標
 * @param end 終点の座標
 * @param point 点の座標
 * @return 点と点の間だったらtrue
 */
bool isPointBetween(const Vector2& start, const Vector2& end, const Vector2& point) {
    // 点と点の間かどうかを判定する
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    // 目的の地点 - 現在の地点
    Vector2 v4 = {end.x - start.x, end.y - start.y };
    Vector2 v5 = {point.x - start.x, point.y - start.y };
    // 点と点の間の幅前後100に侵入してきたらtrueを返す
    if (mathCross (v4, v5) >= -10 || mathCross (v4, v5) <= 10) {
        return true;
    }
        // 内積と外積を計算して点と点の間だったらtrueを返す
    else return false;
}

/**
 * ランダムな値を返却する\n
 * 参考文献: http://vivi.dyndns.org/tech/cpp/random.html
 * @param min 最小値
 * @param max 最大値
 * @return min以上max以下のランダムな値
 * @note random関数を使用するため、randomをインクルードする必要がある
 */
int getRandom(int min, int max) {
    random_device rnd;      // 非決定的な乱数生成器を生成
    mt19937 mt(rnd()); // メルセンヌ・ツイスタの32ビット版、引数は初期シード値
    uniform_int_distribution<> rand100(min, max); // 範囲指定の乱数
    return rand100(mt);  // ランダムな値を返却する
}

/**
 *
 * @param v1
 * @param v2
 * @return
 */
Vector2 findDistance(const Vector2& v1, const Vector2& v2) {
    // 相対ベクトルを正規化
    Vector2 relativeVector = {
            (v1.x - v2.x) / getBallDistance (v1, v2),
            (v1.y - v2.y) / getBallDistance (v1, v2)
    };

    // return 時に入れ替えする方法がわからないのでPOWER IS POWER
    Vector2 tmp = { relativeVector.y, -relativeVector.x };

    // 中央物体（球体）の進行方向ベクトルを返却
    return tmp;
}

// ##### 相対ベクター計算関数 #####
/**
 * 相対ベクトルを計算する\n
 * 参考文献: ゲームアルゴリズム Z07 7ページ目資料
 * @param target 目的の地点
 * @param point 現在の地点
 * @return 相対ベクトル
 */
Vector2 getRelativeVector(const Vector2& target, const Vector2& point) {
    // 2つの円の中心座標の差分を計算（相対ベクトル）
    // 目的の地点 - 現在の地点
    return {target.x - point.x, target.y - point.y};
}

/**
 * ベクトル長を取得する\n
 * 参考文献: Siro_256
 * @param v1 平方根を取りたいベクトル
 * @return sqrtfで平方根を取ったFloat値
 */
float getVectorLength(const Vector2& v1) {
    return sqrtf(v1.x * v1.x + v1.y * v1.y);
}

/**
 * 相対ベクトルを正規化する
 * 参考文献: ゲームアルゴリズム Z07 7ページ目資料
 * @param v1 相対ベクトル化したいベクトル
 * @return 相対ベクトル化されたベクトル
 */
Vector2 getNormalizedVector(const Vector2& v1) {
    // 相対ベクトルを正規化する
    float length = getVectorLength(v1);
    // 正規化した相対ベクトルを返却する
    return {v1.x / length, v1.y / length};
}

/**
 * 最近傍点を探す\n
 * 参考文献: ゲームアルゴリズム Z10 7ページ目資料
 * @param start 始点の座標
 * @param end 終点の座標
 * @param V2 V1との交点を探す点の座標
 * @return 交点の座標
 */
Vector2 getNearestNeighbor(Vector2 start, Vector2 end, Vector2 V2) {
    Vector2 line = {end.x - start.x, end.y - start.y};
    Vector2 normalizedLine = getNormalizedVector(line);
    Vector2 startToV2 = {V2.x - start.x, V2.y - start.y};
    float dot = mathDot (normalizedLine, startToV2);
    Vector2 point = {start.x + normalizedLine.x * dot, start.y + normalizedLine.y * dot};
    return point;
}

/**
 * 操作可能なオブジェクトを移動させる\n
 * 参考文献: なし
 * @param playerPos 移動させたいオブジェクトの座標
 * @param moveSpeed 移動速度
 * @param mode 操作モード 1: 十字キー 2: WASDキー
 */
void moveBall(Vector2 *playerPos, const Vector2& moveSpeed, int mode) {
    if (mode == 1) {
        // 十字キーでpPos2を移動させる
        if (CheckHitKey(KEY_INPUT_UP)) {
            playerPos->y -= moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_DOWN)) {
            playerPos->y += moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_LEFT)) {
            playerPos->x -= moveSpeed.x;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT)) {
            playerPos->x += moveSpeed.x;
        }
    }
    else if (mode == 2) {
        // WASDキーでpPos1を移動させる
        if (CheckHitKey(KEY_INPUT_W)) {
            playerPos->y -= moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_S)) {
            playerPos->y += moveSpeed.y;
        }
        if (CheckHitKey(KEY_INPUT_A)) {
            playerPos->x -= moveSpeed.x;
        }
        if (CheckHitKey(KEY_INPUT_D)) {
            playerPos->x += moveSpeed.x;
        }
    }
}

#endif //UTILS_CLASS_H_
