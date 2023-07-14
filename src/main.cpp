// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "option.h"

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

    // DX���C�u��������������
    if (DxLib_Init() == -1) {
        return -1; // �G���[���N�����璼���ɏI��
    }

    //## �ŗL�̐ݒ�
    // �F�̐ݒ�
    unsigned int charaColor = GetColor(255, 255, 255);

    // Vector2�\���̂̐錾
    // pos: ���݂̍��W, move: �ړ���, moveVec: �ړ��x�N�g��
    Vector2 pos, move;

    // �ړ����̏����ݒ�
    pos.x = WIDTH / 2;  // ��ʂ̒��S�ɐݒ�
    pos.y = HEIGHT / 2;
    pos.size = 32;      // �ړ����̂̃T�C�Y
    move.x = SPEED; // �ړ����̈ړ����l
    move.y = SPEED;

    //##### ���C�����[�v�i�`�揈���j #####//
    while (ProcessMessage() == 0) {
        // ��ʂ̍X�V
        ClearDrawScreen();

        //##### �������̂̏���
        //���̈ړ����� TRUE �h��Ԃ� / FALSE �h��Ԃ��Ȃ�
        DrawCircle(pos.x, pos.y, pos.size, charaColor, TRUE);
        // WASD�L�[��pos���ړ�������
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

        //##### �`�揈��

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip(); // ��ʂ𔽓]�����鏈��
        clsDx();      // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}