#include "Config.h"
#include "Keyboard.h"
#include "DxLib.h"

#define Menu_y 250

static int nowselect;  //�|�C���g�̈ʒu 0�`Menu_num-1
static int now_y;
static int Font00, Font01;

typedef enum {
    eConfig_Menu, //���j���[��ʂ�

    eConfig_num,    //�I�����̐�
}eConfig;

Config::Config(ISceneChanger* changer) : BaseScene(changer) {
    nowselect = eConfig_Menu;
    now_y = Menu_y;
    Font00 = CreateFontToHandle("�l�r �S�V�b�N", 72, 9, DX_FONTTYPE_NORMAL);      //"MS�S�V�b�N"��64pt,����9�̃t�H���g���쐬
    Font01 = CreateFontToHandle("�l�r �S�V�b�N", 35, 7, DX_FONTTYPE_NORMAL);      //"MS�S�V�b�N"��40pt,����7�̃t�H���g���쐬
}


//�X�V
void Config::Update() {
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {  //����L�[��������Ă�����
        nowselect = (nowselect + eConfig_num - 1) % eConfig_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {  //�����L�[��������Ă�����
        nowselect = (nowselect + 1) % eConfig_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) { //�G���^�[�������ꂽ��
        switch (nowselect) {
        case eConfig_Menu:
            mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[��ʂɕύX
            break;
        default:
            break;
        }
    }
}

//�`��
void Config::Draw() {
    //BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
    DrawStringToHandle(200, 90, "�ݒ�", GetColor(255, 0, 0), Font00);
    DrawStringToHandle(190, Menu_y, "���j���[��", GetColor(255, 255, 255), Font01);
    switch (nowselect) {
    case eConfig_Menu:
        now_y = Menu_y;
        break;
    default:
        break;
    }
    DrawStringToHandle(140, now_y, "��", GetColor(255, 255, 255), Font01);
}