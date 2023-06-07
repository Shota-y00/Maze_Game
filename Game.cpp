#include "Game.h"
#include "DxLib.h"

static int second, minute, time, count;
static Time sub[4];

Game::Game(ISceneChanger* changer) : BaseScene(changer) {
    bgm_sound = LoadSoundMem("音声/BGM2.mp3");
}

//初期化
void Game::Initialize() {
    time = GetNowCount();
    Player::Initialize();
    Map::Initialize();
    PlaySoundMem(bgm_sound, DX_PLAYTYPE_LOOP, TRUE);
}

void Game::Finalize() {
    StopSoundMem(bgm_sound);
    Player::Finalize();
    Map::Finalize();
    DeleteSoundMem(bgm_sound);
}

//更新
void Game::Update() {
    count = (GetNowCount() - time) / 1000;
    minute = count / 60;
    second = count % 60;

    Player::Update();
    Map::Update();

    Map::Map_Checkhit();
    
    if (Map::m_flag) {         //クリア時
        result_count.minute = minute;
        result_count.second = second;
        rank_update();
        mSceneChanger->ChangeScene(eScene_Clear);  //シーンをクリア画面に変更
    }
    if (Map::nextstage) {    //次のステージへ
        Map::reset_m();
        Map::nextstage = false;
    }
}

void Game::rank_update() {
    FILE* fp;
    fopen_s(&fp, "ranking.dat", "rb");
    fread(&sub, sizeof(Time), 3, fp);
    fclose(fp);
    sub[3] = result_count;
    for (int i = 2; i >= 0; i--) {
        if (sub[i].minute > result_count.minute) {
            sub[i + 1] = sub[i];
            sub[i] = result_count;
        }
        else if (sub[i].minute == result_count.minute)
            if (sub[i].second > result_count.second) {
                sub[i + 1] = sub[i];
                sub[i] = result_count;
            }
            else
                break;
        else
            break;
    }
    fopen_s(&fp, "ranking.dat", "wb");
    fwrite(&sub, sizeof(Time), 3, fp);
    fclose(fp);
}

//描画
void Game::Draw() {
    Map::Draw();
    Player::Draw();
    DrawFormatString(0, 0, GetColor(255, 255, 255), "Time: %d:%d", minute, second);
}