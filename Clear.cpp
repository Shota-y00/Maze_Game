#include "Clear.h"
#include "Keyboard.h"
#include "DxLib.h"

#define Game_y 250
#define Menu_y 320

static int nowselect;  //ポイントの位置 0～Menu_num-1
static int now_y;
static int Font00, Font01;

typedef enum {
    eClear_Game,   //ゲーム画面へ
    eClear_Menu,   //メニュ―画面へ

    eClear_num,    //選択肢の数
}eClear;

//インストラクタ
Clear::Clear(ISceneChanger* changer) : BaseScene(changer) {
    nowselect = eClear_Game;
    now_y = Game_y;
    Font00 = CreateFontToHandle("ＭＳ ゴシック", 72, 9, DX_FONTTYPE_NORMAL);      //"MSゴシック"の64pt,太さ9のフォントを作成
    Font01 = CreateFontToHandle("ＭＳ ゴシック", 35, 7, DX_FONTTYPE_NORMAL);      //"MSゴシック"の40pt,太さ7のフォントを作成
}

//更新
void Clear::Update() {
    if (Keyboard_Get(KEY_INPUT_UP) == 1) {  //上矢印キーが押されていたら
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
        nowselect = (nowselect + eClear_num - 1) % eClear_num;
    }
    if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {  //下矢印キーが押されていたら
        PlaySoundMem(select_sound, DX_PLAYTYPE_BACK, TRUE);
        nowselect = (nowselect + 1) % eClear_num;
    }
    if (Keyboard_Get(KEY_INPUT_RETURN) == 1) { //エンターが押されたら
        switch (nowselect) {
        case eClear_Game:
            mSceneChanger->ChangeScene(eScene_Game);//シーンをゲーム画面に変更
            break;
        case eClear_Menu:
            mSceneChanger->ChangeScene(eScene_Menu);//シーンをメニュー画面に変更
            break;
        default:
            break;
        }
    }
}

//描画
void Clear::Draw() {
    //BaseScene::Draw();//親クラスの描画メソッドを呼ぶ
    DrawStringToHandle(130, 90, "You win!!", GetColor(255, 0, 0), Font00);
    DrawStringToHandle(190, Game_y, "再スタート", GetColor(255, 255, 255), Font01);
    DrawStringToHandle(190, Menu_y, "メニューへ", GetColor(255, 255, 255), Font01);
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
    DrawStringToHandle(140, now_y, "◆", GetColor(255, 255, 255), Font01);
}