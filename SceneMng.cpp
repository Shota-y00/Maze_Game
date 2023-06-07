#include "DxLib.h"
#include "Config.h"
#include "Game.h"
#include "Menu.h"
#include "Clear.h"
#include "SceneMng.h"

SceneMng::SceneMng() :
    mNextScene(eScene_None) //���̃V�[���Ǘ��ϐ�
{
    mScene = (BaseScene*) new Menu(this);
}

//������
void SceneMng::Initialize() {
    mScene->Initialize();
}

//�I������
void SceneMng::Finalize() {
    mScene->Finalize();
}

//�X�V
void SceneMng::Update() {
    if (mNextScene != eScene_None) {    //���̃V�[�����Z�b�g����Ă�����
        mScene->Finalize();//���݂̃V�[���̏I�����������s
        delete mScene;
        switch (mNextScene) {       //�V�[���ɂ���ď����𕪊�
        case eScene_Menu:        //���̉�ʂ����j���[�Ȃ�
            mScene = (BaseScene*) new Menu(this);   //���j���[��ʂ̃C���X�^���X�𐶐�����
            break;//�ȉ���
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
        mNextScene = eScene_None;    //���̃V�[�������N���A
        mScene->Initialize();    //�V�[����������
    }

    mScene->Update(); //�V�[���̍X�V
}

//�`��
void SceneMng::Draw() {
    mScene->Draw(); //�V�[���̕`��
}

// ���� nextScene �ɃV�[����ύX����
void SceneMng::ChangeScene(eScene NextScene) {
    mNextScene = NextScene;    //���̃V�[�����Z�b�g����
}