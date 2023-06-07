#include "Menu.h"
#include "Keyboard.h"
#include "DxLib.h"
#include "Game.h"

#define Game_y 250
#define Config_y 320

static int nowselect;  //ポイントの位置 0～Menu_num-1
static int now_y;
static int Font00, Font01;
static Time rank[3];
static int rank_y;

typedef enum {
    eMenu_Game,   //ゲーム画面へ
    eMenu_Config, //設定画面へ

    eMenu_num,    //選択肢の数
}eMenu;

Menu::Menu(ISceneChanger* changer) : BaseScene(changer) {
    nowselect = eMenu_Game;
    now_y = Game_y;
    Font00 = CreateFontToHandle("ＭＳ ゴシック", 72, 9, DX_FONTTYPE_NORMAL);      //"MSゴシック"の64pt,太さ9のフォントを作成
    Font01 = CreateFontToHandle("ＭＳ ゴシック", 30, 7, DX_FONTTYPE_NORMAL);      //"MSゴシック"の40pt,太さ7のフォントを作成

    /*ランキングの読み込み*/
    FILE* fp;
    fopen_s(&fp, "ranking.dat", "rb");
    fread(&rank, sizeof(Time), 3, fp);
    fclose(fp);
}


//更新
void Menu::Update() {
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {  //上矢印キーが押されていたら
        nowselect = (nowselect + eMenu_num - 1) % eMenu_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {  //下矢印キーが押されていたら
        nowselect = (nowselect + 1) % eMenu_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) { //エンターが押されたら
        switch (nowselect) {
        case eMenu_Game:
            mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
            break;
        case eMenu_Config:
            mSceneChanger->ChangeScene(eScene_Config);//シーンを設定画面に変更
            break;
        default:
            break;
        }
    }
    
    /*"R"を押したらランキングの初期化の処理*/
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

//描画
void Menu::Draw() {
    //BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
    DrawStringToHandle(140, 80, "ActionGame", GetColor(255, 0, 0), Font00);
    DrawStringToHandle(100, Game_y, "ゲームスタート", GetColor(255, 255, 255), Font01);
    DrawStringToHandle(100, Config_y, "設定", GetColor(255, 255, 255), Font01);
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
    DrawStringToHandle(50, now_y, "◆", GetColor(255, 255, 255), Font01);
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