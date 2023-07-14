// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "utils.h"
#include "vector.h"

//## ���ɉ����Đݒ�
#define WIDTH 1280
#define HEIGHT 720
#define SPEED 1 // �ړ����x 60Hz=8, 300Hz=1
using namespace std;

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
    Vector2 TESTp, TESTm;

    // �ړ����̏����ݒ�
    pPos1.x = WIDTH / 2;  // ��ʂ̒��S�ɐݒ�
    pPos1.y = HEIGHT / 2;
    pPos1.size = 32;      // �ړ����̂̃T�C�Y
    pPos2.x = WIDTH / 2;  // ��ʂ̒��S�ɐݒ�
    pPos2.y = HEIGHT / 2;
    pPos2.size = 32;      // �ړ����̂̃T�C�Y
    move.x = SPEED; // �ړ����̈ړ����l
    move.y = SPEED;

    //## �I�I�I�����p�I�I�I
    TESTp.x = 800;
    TESTp.y = 600;
    TESTp.size = 8;
    TESTm.x = SPEED;
    TESTm.y = SPEED;
    //## �I�I�I�����p�I�I�I

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