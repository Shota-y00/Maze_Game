#pragma once
#include "DxLib.h"
#include "Task.h"

const int Window_size_x = 640; //����x�T�C�Y
const int Window_size_y = 480; // ����y�T�C�Y

class Player : Task{
protected:
	int p_image[4];         //�v���C���[�̉摜
	int dir;                //�v���C���[�������Ă�������B�摜�̏o�͂Ɏg�p�B0=��,1=��,2=�E,3=��
	int p_x, p_y;           //�v���C���[�̍��W�B�^�񒆂ɌŒ�
	int p_width, p_height;  //�v���C���[�̕��A����
	float speed;            //�ړ��X�s�[�h 
public:
	Player();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};

