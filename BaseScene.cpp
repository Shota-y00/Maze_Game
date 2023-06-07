#include "BaseScene.h"
#include "DxLib.h"

BaseScene::BaseScene(ISceneChanger* changer) :
    mImage(0) {
    mSceneChanger = changer;
    select_sound = LoadSoundMem("����/btn01.mp3");
}

void BaseScene::Finalize() {
    DeleteGraph(mImage);
    DeleteSoundMem(select_sound);
}

void BaseScene::Draw() {
    DrawGraph(0, 0, mImage, FALSE);  //x,y�͍���
    //DrawRotaGraph(0, 0, 1.0, 0.0, mImage, FALSE);  //x,y�͐^��
}