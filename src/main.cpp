// �ȉ��̍s���Ȃ��ƃR���p�C�����ʂ�܂���
#pragma comment(linker, "/subsystem:windows")
#include "DxLib.h"
#include "utils.h"
#include "vector.h"

//## ���ɉ����Đݒ�
#define WIDTH 1280
#define HEIGHT 720
#define SPEED 8 // �ړ����x 60Hz=8, 300Hz=1
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
    Vector2 objMove, objPos1, objPos2, objPos3;

    // �ړ����̏����ݒ�
    pPos1.x = WIDTH / 2;  // ��ʂ̒��S�ɐݒ�
    pPos1.y = HEIGHT / 2;
    pPos1.size = 32;      // �ړ����̂̃T�C�Y
    pPos2.x = WIDTH / 2;  // ��ʂ̒��S�ɐݒ�
    pPos2.y = HEIGHT / 2;
    pPos2.size = 32;      // �ړ����̂̃T�C�Y
    move.x = SPEED; // �ړ����̈ړ����l
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

        //## �I�I�I�����p�I�I�I
        // TESTp��pPos1��pPos2�̊Ԃɂ���ꍇ���̒��S���i��ł�������ɑ΂��Ĉړ�������
        //DrawCircle(TESTp.x, TESTp.y, TESTp.size, charaColor, TRUE);

        // ���΃x�N�g���v�Z
        Vector2 relativeVector1 = getRelativeVector(pPos1, pPos2);
        Vector2 relativeVector2 = getRelativeVector(pPos1, TESTp);
        Vector2 relativeVector3 = getRelativeVector(pPos2, pPos1);
        Vector2 relativeVector4 = getRelativeVector(pPos2, TESTp);

        //�O�ςƓ��ς��v�Z
        Vector2 RV1Normal = getNormalizedVector(relativeVector1);
        Vector2 RV2Normal = getNormalizedVector(relativeVector2);
        float cross = mathCross (RV1Normal, relativeVector2);
        if(cross < 0) cross *= -1; //�O�ς̐�Βl���擾

        float dotV1 = mathDot (relativeVector1, relativeVector2);
        float dotV2 = mathDot (relativeVector3, relativeVector4);

        //##### �����蔻��
        if(dotV1 > 0 && dotV2 > 0 && cross < TESTp.size){
            printfDx("��������\n");
            charaColor = GetColor(255, 0, 0);

            // ����������v�Z
            Vector2 NNSVector = getNearestNeighbor(pPos1, pPos2, TESTp);
            printfDx("NNSVector.x = %f\n", NNSVector.x);
            printfDx("NNSVector.y = %f\n", NNSVector.y);

            // �v�Z��������K��
            Vector2 NNSVectorNormal = getNormalizedVector(NNSVector);

            // ����������ړ�
            TESTp.x += NNSVectorNormal.x;
            TESTp.y += NNSVectorNormal.y;
        }
        else {
            charaColor = GetColor(255, 255, 255);
        }

        // �����o����镨��
        DrawCircle(TESTp.x, TESTp.y, TESTp.size, GetColor(0, 255, 0), TRUE);

        //## �I�I�I�����p�I�I�I

        //##### ����\�ȋ��̂̈ړ�����
        moveBall (&pPos2, move, 1); // �\���L�[��pPos2���ړ�������
        moveBall (&pPos1, move, 2); // WASD�L�[��pPos1���ړ�������

        // �f�o�b�O
        //printfDx();

        //�O�ς����̎��͎��v���A���̎��͔����v���
        if (cross > 0) {
            printfDx("���v���\n");
        }
        else if (cross < 0) {
            printfDx("�����v���\n");
        }
        else {
            printfDx("����\n");
        }

        //���ς����̎��͓݊p�A���̎��͉s�p
        if (dotV1 > 0) {
            printfDx("�݊p\n");
        }
        else if (dotV1 < 0) {
            printfDx("�s�p\n");
        }
        else {
            printfDx("���p\n");
        }

        //##### �f�o�b�O�p #####
        printfDx("pPos1.x = %f\n", pPos1.x);
        printfDx("pPos1.y = %f\n", pPos1.y);
        printfDx("pPos2.x = %f\n", pPos2.x);
        printfDx("pPos2.y = %f\n", pPos2.y);
        printfDx("TESTp.x = %f\n", TESTp.x);
        printfDx("TESTp.y = %f\n", TESTp.y);
        printfDx("cross = %f\n", cross);
        printfDx("dotV1 = %f\n", dotV1);
        printfDx("dotV2 = %f\n", dotV2);
        //##### �f�o�b�O�p #####

        //##### �`�揈��
        //����\�ȋ��̂̈ړ����� TRUE �h��Ԃ� / FALSE �h��Ԃ��Ȃ�
        DrawCircle(pPos1.x, pPos1.y, pPos1.size, charaColor, TRUE);
        DrawCircle(pPos2.x, pPos2.y, pPos2.size, charaColor, TRUE);
        //����\�ȋ��̓��m����łȂ���
        DrawLine(pPos1.x, pPos1.y, pPos2.x, pPos2.y, charaColor);

        //�ŋߖT�_�̓_��\��
        Vector2 NNSVectorN = getNearestNeighbor(pPos1, pPos2, TESTp);
        // ���ς��v�Z����
        float dot = mathDot (RV1Normal, TESTp);
        Vector2 V3 = getNormalizedVector(relativeVector1);
        // �ŋߖT�_���v�Z����
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

        // ��ʂ̍X�V�i�K�{�j
        ScreenFlip(); // ��ʂ𔽓]�����鏈��
        clsDx();      // �f�o�b�O���O��ʂ��N���A���鏈��
    }

    DxLib_End(); // DX Library�̎g�p���I�����鏈��
    return 0;    // �\�t�g�𐳏�I��
}