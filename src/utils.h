//
// Created by waya on 2023/07/14.
//

#ifndef UTILS_CLASS
#define UTILS_CLASS

#pragma once
#include <cmath>
#include <iostream>
#include <random>
#include "vector.h"
using namespace std;

// ##### 2�̉~�̒��S���W�̋������v�Z����֐� #####
// �Q�l���� : https://www.geisya.or.jp/~mwm48961/math/distance1j.htm
// ����     : x1, y1, x2, y2
// �߂�l   : 2�̉~�̒��S���W�̋���
// ����     : sqrt�֐����g�p���邽�߁Amath.h or cmath���C���N���[�h����K�v������
float getDistance(float x1, float y1, float x2, float y2) {
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    float dx = x1 - x2; // �ړI�̒n�_ - ���݂̒n�_
    float dy = y1 - y2;
    // 2�̉~�̒��S���W�̋������v�Z
    return sqrt((dx * dx) + (dy * dy));
}

// ##### �O�όv�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : x1, y1, x2, y2
// �߂�l   : �O��
// ����     : �Ȃ�
float getCrossProduct(float x1, float y1, float x2, float y2) {
    return x1 * y2 - y1 * x2;
}

// ##### ���όv�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 12�y�[�W�ڎ���
// ����     : x1, y1, x2, y2
// �߂�l   : ����
// ����     : �Ȃ�
float getDotProduct(float x1, float y1, float x2, float y2) {
    return x1 * x2 + y2 * y1;
}

// ##### ���ςƊO�ς��v�Z���ē_�Ɠ_�̊Ԃ�������true��Ԃ� #####
// �Q�l���� : �Ȃ�
// ����     : x1, y1, x2, y2, x3, y3
// �߂�l   : �_�Ɠ_�̊Ԃ�������true
// ����     : �Ȃ�
bool isPointBetween(float x1, float y1, float x2, float y2, float x3, float y3) {
    // �_�Ɠ_�̊Ԃ��ǂ����𔻒肷��
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    float dx1 = x2 - x1; // �ړI�̒n�_ - ���݂̒n�_
    float dy1 = y2 - y1;
    float dx2 = x3 - x1; // �ړI�̒n�_ - ���݂̒n�_
    float dy2 = y3 - y1;
    // �O�ς��v�Z
    float crossProduct = getCrossProduct(dx1, dy1, dx2, dy2);
    // ���ς��v�Z
    float dotProduct = getDotProduct(dx1, dy1, dx2, dy2);
    // �_�Ɠ_�̊Ԃ̕��O��100�ɐN�����Ă�����true��Ԃ�
    if (crossProduct >= -10 || crossProduct <= 10 && dotProduct >= 0) {
        return true;
    }
        // ���ςƊO�ς��v�Z���ē_�Ɠ_�̊Ԃ�������true��Ԃ�
    else return false;
}

// ##### �����_���Ȓl��ԋp����֐� #####
// �Q�l���� : http://vivi.dyndns.org/tech/cpp/random.html
// ����     : min, max
// �߂�l   : min�ȏ�max�ȉ��̃����_���Ȓl
// ����     : random�֐����g�p���邽�߁Arandom���C���N���[�h����K�v������
int getRandom(int min, int max) {
    random_device rnd;     // �񌈒�I�ȗ���������𐶐�
    mt19937 mt(rnd());     //  �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h�l
    uniform_int_distribution<> rand100(min, max); // �͈͎w��̗���
    // �����_���Ȓl��ԋp����
    return rand100(mt);
}

// ���菈�������ʉ�
Vector2 findDistance(float x1, float y1, float x2, float y2) {
    // ���΃x�N�g���𐳋K��
    Vector2 relativeVector = {
            (x1 - x2) / getDistance(x1, y1, x2, y2),
            (y1 - y2) / getDistance(x1, y1, x2, y2)
    };

    // return ���ɓ���ւ�������@���킩��Ȃ��̂�POWER IS POWER
    Vector2 tmp = { relativeVector.y, -relativeVector.x };

    // �������́i���́j�̐i�s�����x�N�g����ԋp
    return tmp;
};

// ##### ���΃x�N�^�[�v�Z�֐� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : x1, y1, x2, y2
// �߂�l   : ���΃x�N�^�[
// ����     : �Ȃ�
Vector2 getRelativeVector(Vector2 V1, Vector2 V2) {
    // 2�̉~�̒��S���W�̍������v�Z�i���΃x�N�g���j
    float dx = V1.x - V2.x; // �ړI�̒n�_ - ���݂̒n�_
    float dy = V1.y - V2.y;
    // ���΃x�N�g����ԋp����
    return Vector2(dx, dy);
};

// ##### ���΃x�N�^�[���K�� #####
// �Q�l���� : �Q�[���A���S���Y�� Z07 7�y�[�W�ڎ���
// ����     : V1
// �߂�l   : ���΃x�N�^�[
// ����     : �Ȃ�
Vector2 getNormalizedVector(Vector2 V1) {
    // ���΃x�N�g���𐳋K������
    float length = sqrt(V1.x * V1.x + V1.y * V1.y);
    V1.x /= length;
    V1.y /= length;
    // ���K���������΃x�N�g����ԋp����
    return Vector2(V1.x, V1.y);
};

// ##### ����I�u�W�F�N�g�ړ����� #####
// �Q�l���� : �Ȃ�
// ����     : pPos, vec2, p
// �߂�l   : �Ȃ�
// ����     : p�ɂ�1��2������K�v������B1��pPos1�A2��pPos2�𑀍삷��
void moveCross(Vector2 *pVec2, Vector2 vec2, int p) {
    if (p == 1) {
        // �\���L�[��pPos2���ړ�������
        if (CheckHitKey(KEY_INPUT_UP)) {
            pVec2->y -= vec2.y;
        }
        if (CheckHitKey(KEY_INPUT_DOWN)) {
            pVec2->y += vec2.y;
        }
        if (CheckHitKey(KEY_INPUT_LEFT)) {
            pVec2->x -= vec2.x;
        }
        if (CheckHitKey(KEY_INPUT_RIGHT)) {
            pVec2->x += vec2.x;
        }
    }
    else if (p == 2) {
        // WASD�L�[��pPos1���ړ�������
        if (CheckHitKey(KEY_INPUT_W)) {
            pVec2->y -= vec2.y;
        }
        if (CheckHitKey(KEY_INPUT_S)) {
            pVec2->y += vec2.y;
        }
        if (CheckHitKey(KEY_INPUT_A)) {
            pVec2->x -= vec2.x;
        }
        if (CheckHitKey(KEY_INPUT_D)) {
            pVec2->x += vec2.x;
        }
    }
}

#endif //UTILS_H
