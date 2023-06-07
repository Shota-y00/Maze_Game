#include "Clear.h"
#include "Keyboard.h"
#include "DxLib.h"

#define Game_y 250
#define Menu_y 320

static int nowselect;  //�|�C���g�̈ʒu 0�`Menu_num-1
static int now_y;
static int Font00, Font01;

typedef enum {
    eClear_Game,   //�Q�[����ʂ�
    eClear_Menu,   //���j���\��ʂ�

    eClear_num,    //�I�����̐�
}eClear;

//�C���X�g���N�^
Clear::Clear(ISceneChanger* changer) : BaseScene(changer) {
    nowselect = eClear_Game;
    now_y = Game_y;
    Font00 = CreateFontToHandle("�l�r �S�V�b�N", 72, 9, DX_FONTTYPE_NORMAL);      //"MS�S�V�b�N"��64pt,����9�̃t�H���g���쐬
    Font01 = CreateFontToHandle("�l�r �S�V�b�N", 35, 7, DX_FONTTYPE_NORMAL);      //"MS�S�V�b�N"��40pt,����7�̃t�H���g���쐬
}

//�X�V
void Clear::Update() {
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {  //����L�[��������Ă�����
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
        nowselect = (nowselect + eClear_num - 1) % eClear_num;
    }
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {  //�����L�[��������Ă�����
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
        nowselect = (nowselect + 1) % eClear_num;
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) { //�G���^�[�������ꂽ��
        switch (nowselect) {
        case eClear_Game:
            mSceneChanger->ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
            break;
        case eClear_Menu:
            mSceneChanger->ChangeScene(eScene_Menu);//�V�[�������j���[��ʂɕύX
            break;
        default:
            break;
        }
    }
}

//�`��
void Clear::Draw() {
    //BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
    DrawStringToHandle(130, 90, "You win!!", GetColor(255, 0, 0), Font00);
    DrawStringToHandle(190, Game_y, "�ăX�^�[�g", GetColor(255, 255, 255), Font01);
    DrawStringToHandle(190, Menu_y, "���j���[��", GetColor(255, 255, 255), Font01);
    switch (nowselect) {
    case eClear_Game:
        now_y = Game_y;
        break;
    case eClear_Menu:
        now_y = Menu_y;
        break;
    default:
        break;
    }
    DrawStringToHandle(140, now_y, "��", GetColor(255, 255, 255), Font01);
}