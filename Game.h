#pragma once

#include "BaseScene.h"
#include "Map.h"
#include "ISceneChanger.h"

typedef struct {
    int minute;
    int second;
}Time;

//�Q�[����ʃN���X
class Game : public BaseScene, Map {
protected:
    Time result_count;
    int bgm_sound;
public:
    Game(ISceneChanger* changer);
    void Initialize() override;    //�������������I�[�o�[���C�h�B
    void Finalize() override;        //�I���������I�[�o�[���C�h�B
    void Update() override;        //�X�V�������I�[�o�[���C�h�B
    void Draw() override;            //�`�揈�����I�[�o�[���C�h�B
    void rank_update();

};