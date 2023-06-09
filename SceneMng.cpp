#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "Clear.h"
#include "SceneMng.h"

SceneMng::SceneMng() :
    mNextScene(eScene_None) //次のシーン管理変数
{
    mScene = (BaseScene*) new Menu(this);
}

//初期化
void SceneMng::Initialize() {
    mScene->Initialize();
}

//終了処理
void SceneMng::Finalize() {
    mScene->Finalize();
}

//更新
void SceneMng::Update() {
    if (mNextScene != eScene_None) {    //次のシーンがセットされていたら
        mScene->Finalize();//現在のシーンの終了処理を実行
        delete mScene;
        switch (mNextScene) {       //シーンによって処理を分岐
        case eScene_Menu:        //次の画面がメニューなら
            mScene = (BaseScene*) new Menu(this);   //メニュー画面のインスタンスを生成する
            break;//以下略
        case eScene_Game:
            mScene = (BaseScene*) new Game(this);
            break;
        case eScene_Config:
            mScene = (BaseScene*) new Config(this);
            break;
        case eScene_Clear:
            mScene = (BaseScene*) new Clear(this);
            break;
        }
        mNextScene = eScene_None;    //次のシーン情報をクリア
        mScene->Initialize();    //シーンを初期化
    }

    mScene->Update(); //シーンの更新
}

//描画
void SceneMng::Draw() {
    mScene->Draw(); //シーンの描画
}

// 引数 nextScene にシーンを変更する
void SceneMng::ChangeScene(eScene NextScene) {
    mNextScene = NextScene;    //次のシーンをセットする
}