#include "Config.h"
#include "Keyboard.h"
#include "DxLib.h"

#define Menu_y 250

static int nowselect;  //ポイントの位置 0～Menu_num-1
static int now_y;
static int Font00, Font01;

typedef enum {
    eConfig_Menu, //メニュー画面へ

    eConfig_num,    //選択肢の数
}eConfig;

Config::Config(ISceneChanger* changer) : BaseScene(changer) {
    nowselect = eConfig_Menu;
    now_y = Menu_y;
    Font00 = CreateFontToHandle("ＭＳ ゴシック", 72, 9, DX_FONTTYPE_NORMAL);      //"MSゴシック"の64pt,太さ9のフォントを作成
    Font01 = CreateFontToHandle("ＭＳ ゴシック", 35, 7, DX_FONTTYPE_NORMAL);      //"MSゴシック"の40pt,太さ7のフォントを作成
}


//更新
void Config::Update() {
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {  //上矢印キーが押されていたら
        nowselect = (nowselect + eConfig_num - 1) % eConfig_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {  //下矢印キーが押されていたら
        nowselect = (nowselect + 1) % eConfig_num;
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) { //エンターが押されたら
        switch (nowselect) {
        case eConfig_Menu:
            mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニュー画面に変更
            break;
        default:
            break;
        }
    }
}

//描画
void Config::Draw() {
    //BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
    DrawStringToHandle(200, 90, "設定", GetColor(255, 0, 0), Font00);
    DrawStringToHandle(190, Menu_y, "メニューへ", GetColor(255, 255, 255), Font01);
    switch (nowselect) {
    case eConfig_Menu:
        now_y = Menu_y;
        break;
    default:
        break;
    }
    DrawStringToHandle(140, now_y, "◆", GetColor(255, 255, 255), Font01);
}