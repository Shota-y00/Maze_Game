#pragma once

#include "BaseScene.h"
#include "Map.h"
#include "ISceneChanger.h"

typedef struct {
    int minute;
    int second;
}Time;

//ゲーム画面クラス
class Game : public BaseScene, Map {
protected:
    Time result_count;
    int bgm_sound;
public:
    Game(ISceneChanger* changer);
    void Initialize() override;    //初期化処理をオーバーライド。
    void Finalize() override;        //終了処理をオーバーライド。
    void Update() override;        //更新処理をオーバーライド。
    void Draw() override;            //描画処理をオーバーライド。
    void rank_update();

};