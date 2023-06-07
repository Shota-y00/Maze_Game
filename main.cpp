#include "DxLib.h"
#include "Keyboard.h"
#include "SceneMng.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK); //�E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�

    SceneMng sceneMng;
    sceneMng.Initialize();

    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {//��ʍX�V & ���b�Z�[�W���� & ��ʏ���

        Keyboard_Update();

        sceneMng.Update();  //�X�V
        sceneMng.Draw();    //�`��

    }

    sceneMng.Finalize();

    DxLib_End(); // DX���C�u�����I������
    return 0;
}