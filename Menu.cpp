#include "Menu.h"
#include "Keyboard.h"
#include "DxLib.h"
#include "Game.h"

#define Game_y 250
#define Config_y 320

static int nowselect;  //�|�C���g�̈ʒu 0�`Menu_num-1
static int now_y;
static int Font00, Font01;
static Time rank[3];
static int rank_y;

typedef enum {
    eMenu_Game,   //�Q�[����ʂ�
    eMenu_Config, //�ݒ��ʂ�

    eMenu_num,    //�I�����̐�
}eMenu;

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
    nowselect = eMenu_Game;
    now_y = Game_y;
    Font00 = CreateFontToHandle("�l�r �S�V�b�N", 72, 9, DX_FONTTYPE_NORMAL);      //"MS�S�V�b�N"��64pt,����9�̃t�H���g���쐬
    Font01 = CreateFontToHandle("�l�r �S�V�b�N", 30, 7, DX_FONTTYPE_NORMAL);      //"MS�S�V�b�N"��40pt,����7�̃t�H���g���쐬

    /*�����L���O�̓ǂݍ���*/
    FILE* fp;
    fopen_s(&fp, "ranking.dat", "rb");
    fread(&rank, sizeof(Time), 3, fp);
    fclose(fp);
}


//�X�V
void Menu::Update() {
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {  //����L�[��������Ă�����
        nowselect = (nowselect + eMenu_num - 1) % eMenu_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {  //�����L�[��������Ă�����
        nowselect = (nowselect + 1) % eMenu_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) { //�G���^�[�������ꂽ��
        switch (nowselect) {
        case eMenu_Game:
            mSceneChanger->ChangeScene(eScene_Game);//�V�[�����Q�[����ʂɕύX
            break;
        case eMenu_Config:
            mSceneChanger->ChangeScene(eScene_Config);//�V�[����ݒ��ʂɕύX
            break;
        default:
            break;
        }
    }
    
    /*"R"���������烉���L���O�̏������̏���*/
    if (Keyboard_Get(KEY_INPUT_R) == 1) {
        rank[0] = { INT_MAX, INT_MAX };
        rank[1] = { INT_MAX, INT_MAX };
        rank[2] = { INT_MAX, INT_MAX };
        FILE* fp;
        fopen_s(&fp, "ranking.dat", "wb");
        fwrite(&rank, sizeof(Time), 3, fp);
        fclose(fp);
    }
}

//�`��
void Menu::Draw() {
    //BaseScene::Draw();//�e�N���X�̕`�惁�\�b�h���Ă�
    DrawStringToHandle(140, 80, "ActionGame", GetColor(255, 0, 0), Font00);
    DrawStringToHandle(100, Game_y, "�Q�[���X�^�[�g", GetColor(255, 255, 255), Font01);
    DrawStringToHandle(100, Config_y, "�ݒ�", GetColor(255, 255, 255), Font01);
    switch (nowselect) {
    case eMenu_Game:
        now_y = Game_y;
        break;
    case eMenu_Config:
        now_y = Config_y;
        break;
    default:
        break;
    }
    DrawStringToHandle(50, now_y, "��", GetColor(255, 255, 255), Font01);
    DrawStringToHandle(380, 230, "Ranking", GetColor(255, 255, 255), Font01);

    rank_y = 300;
    for (int i = 0; i < 3; i++) {
        if(rank[i].minute == INT_MAX)
            DrawFormatString(390, rank_y, GetColor(255, 255, 255), "%d. ----:----", i + 1);
        else
            DrawFormatString(390, rank_y, GetColor(255, 255, 255), "%d. %d:%d", i + 1, rank[i].minute, rank[i].second);
        rank_y += 50;
    }
    DrawString(500, 450, "BGM,SE : MusMus", GetColor(255, 255, 255));
}