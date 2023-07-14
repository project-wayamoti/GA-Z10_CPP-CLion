// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "option.h"

//## ���ɉ����Đݒ�
#define WIDTH 1280
#define HEIGHT 720
#define SPEED 1 // �ړ����x 60Hz=8, 300Hz=1
using namespace std;

//## �v���g�^�C�v�錾

// moveCross(�ړ��x�N�g��, �ړ���, �ړ��Ώ�)
void moveCross(Vector2 *pVec2, Vector2 vec2, int p);

// �v���O�����̍ŏ���WinMain�Ŏn�߂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    //##### �����ݒ� #####//
    // ��ʐݒ�
    ChangeWindowMode(TRUE); // �E�B���h�E���[�h�ݒ�
    SetGraphMode(WIDTH, HEIGHT, 32);
    SetWaitVSyncFlag(TRUE); // ����������L���ɂ���

    //## �^�錾
    //## �ŗL�̐ݒ�
    // �F�̐ݒ�
    unsigned int charaColor = GetColor(255, 255, 255);

    // Vector2�\���̂̐錾
    // pPos1: ���݂̍��W, move: �ړ���, moveVec: �ړ��x�N�g��
    Vector2 pPos1, pPos2, move;

    // �ړ����̏����ݒ�
    pPos1.x = WIDTH / 2;  // ��ʂ̒��S�ɐݒ�
    pPos1.y = HEIGHT / 2;
    pPos1.size = 32;      // �ړ����̂̃T�C�Y
    pPos2.x = WIDTH / 2;  // ��ʂ̒��S�ɐݒ�
    pPos2.y = HEIGHT / 2;
    pPos2.size = 32;      // �ړ����̂̃T�C�Y
    move.x = SPEED; // �ړ����̈ړ����l
    move.y = SPEED;

    // DX���C�u��������������
    if (DxLib_Init() == -1) {
        return -1; // �G���[���N�����璼���ɏI��
    }

    //##### ���C�����[�v�i�`�揈���j #####//
    while (ProcessMessage() == 0) {
        // ��ʂ̍X�V
        ClearDrawScreen();

        //##### �`�揈��
        //����\�ȋ��̂̈ړ����� TRUE �h��Ԃ� / FALSE �h��Ԃ��Ȃ�
        DrawCircle(pPos1.x, pPos1.y, pPos1.size, charaColor, TRUE);
        DrawCircle(pPos2.x, pPos2.y, pPos2.size, charaColor, TRUE);
        //����\�ȋ��̓��m����łȂ���
        DrawLine(pPos1.x, pPos1.y, pPos2.x, pPos2.y, charaColor);

        //##### ����\�ȋ��̂̈ړ�����
        moveCross(&pPos2, move, 1); // �\���L�[��pPos2���ړ�������
        moveCross(&pPos1, move, 2); // WASD�L�[��pPos1���ړ�������

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip(); // ��ʂ𔽓]�����鏈��
        clsDx();      // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}

void moveCross(Vector2 *pVec2, Vector2 vec2, int p) {
    if(p == 1){
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
    }else if (p == 2){
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