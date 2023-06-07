#pragma once
#include "Player.h"

const int Size_map_x = 60; //�}�b�v�`�b�v��x�T�C�Y
const int Size_map_y = 60; //�}�b�v�`�b�v��y�T�C�Y
const int Num_chip_x = 10;  //x�̃}�b�v�`�b�v�̎�ސ�
const int Num_chip_y = 2;  //y�̃}�b�v�`�b�v�̎�ސ�
const int Num_chip_all = Num_chip_x * Num_chip_y; //���}�b�v�`�b�v�̎�ސ�

const int Num_map_x = 50; //���̃}�b�v�`�b�v�̌� 70*50=3500
const int Num_map_y = 50; //�c�̃}�b�v�`�b�v�̌� 70*50=3500



typedef enum {  //�X�e�[�W��
	stage1,
	stage2,

	stage_none, //��z��A�Q�[���N���A�̂Ƃ��ɕK�v
	stage_num,
}stage;

class Map :public Player{
protected:
	int mapdata[stage_num][Num_map_y][Num_map_x] = {};  //�}�b�v�f�[�^
	int m_image[Num_chip_all] = {};//�ǂȂǂ̉摜
	float scene_x;                 //�t���[���̍����x���W
	float scene_y;                 //�t���[���̍����y���W
	float old_scene_x, old_scene_y;
	bool m_flag;                   //�N���A�t���O�Bfalse = not clear, true = clear
	bool nextstage;                //���̃X�e�[�W�ɐi�ރt���O
	int stage, no;                 //���݂̃X�e�[�W��
public:
	Map();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Map_Checkhit();
	void Draw() override;
	void reset_m();
};