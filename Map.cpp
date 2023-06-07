#include "Map.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "CheckHit.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //�J���}�ŋ�؂邽�߂ɕK�v

using namespace std;

static int c, retu, gyou;
static char buf[10];
static int mx, my;

Map::Map() {
	scene_x = old_scene_x = (float)Size_map_x - p_x;
	scene_y = old_scene_y = (float)Size_map_y * Num_map_y - Size_map_y - p_y - p_height;
	m_flag = false;
	stage = stage1;
	nextstage = false;
}

void Map::Initialize() {

	/*�}�b�v�̉摜�̃��[�h*/
	m_image[0] = NULL;
	m_image[1] = LoadGraph("�摜/�S�[��2.jpg");
	m_image[5] = LoadGraph("�摜/�u���b�N03.png");

	/*�}�b�v�f�[�^�̓ǂݍ���*/
	ifstream ifs("map_data.csv");
	// �J���Ȃ�������G���[
	if (!ifs) {
		cout << "Error! File can not be opened" << endl;
		return;
	}

	string str = "";
	int i = 0, j = 0, k = 0;
	// �t�@�C���̒��g����s���ǂݎ��
	while (getline(ifs, str)) {
		string tmp = "";
		istringstream stream(str);

		// ��؂蕶�����Ȃ��Ȃ�܂ŕ�������؂��Ă���
		while (getline(stream, tmp, ',')) {
			// ��؂�ꂽ������tmp�ɓ���
			mapdata[k][i][j] = atoi(tmp.c_str());
			j++;
		}
		if (i == Num_map_y - 1 && j == Num_map_x - 1) {
			i = j = -1;
			k++;
		}
		else {
			j = 0;
			i++;  // ���̗�Ɉڂ�
		}
	}
	ifs.close();
}

void Map::Finalize() {
	for (int i = 0; i < Num_chip_all; i++)
		DeleteGraph(m_image[i]);
}

void Map::Update() {

	/*scene�̍X�V*/
	old_scene_x = scene_x;
	old_scene_y = scene_y;

	/*�ړ�����*/
	if (Keyboard_Get(KEY_INPUT_UP) != 0)
		scene_y -= speed;
	if (Keyboard_Get(KEY_INPUT_DOWN) != 0)
		scene_y += speed;
	if (Keyboard_Get(KEY_INPUT_RIGHT) != 0)
		scene_x += speed;
	if (Keyboard_Get(KEY_INPUT_LEFT) != 0)
		scene_x -= speed;
}

void Map::Map_Checkhit() {
	mx = (int)(scene_x / Size_map_x);
	my = (int)(scene_y / Size_map_y);
	for (int j = my; j <= my + Window_size_y / Size_map_y && j < Num_map_y; j++) {
		for (int i = mx; i <= mx + Window_size_x / Size_map_x + 1 && i < Num_map_x; i++) {

			no = mapdata[stage][j][i];
			if (no >= 5) {
				// �@���܂Ŏg�p���Ă��铖���蔻���float�ɂ��ď������s��(��CheckHit�̒����Q��) 
				if (Checkhit((float)i * Size_map_x - scene_x, (float)j * Size_map_y - scene_y, (float)Size_map_x, (float)Size_map_y, (float)p_x, (float)p_y, (float)p_width, (float)p_height)) {

					// �A��or�^�����瓖�����Ă��邩�`�F�b�N
					if (scene_y >= old_scene_y) {

						// �B�n�`�����ォ�瓖�����Ă��邩�`�F�b�N����
						// �����łȂ��ꍇ�͉����瓖�����Ă���
						if (j * Size_map_y - p_height >= old_scene_y + p_y) {
							// �C�n�`�ɏォ�瓖�����Ă���
							scene_y = (float)(j * Size_map_y - p_y - p_height);
							old_scene_y = scene_y;
						}
						else {
							// �D�n�`�̉����瓖�����Ă���
							if (scene_x >= old_scene_x) {
								scene_x = (float)i * Size_map_x - p_x - p_width;
								old_scene_x = scene_x;
							}
							else {
								scene_x = (float)i * Size_map_x - p_x + Size_map_x;
								old_scene_x = scene_x;
							}
						}
					}

					// �����瓖�����Ă��邩�`�F�b�N
					else if (scene_y < old_scene_y) {
						// �n�`���������瓖�����Ă��邩�`�F�b�N����
						// �����łȂ��ꍇ�͉����瓖�����Ă���
						if ((j + 1) * Size_map_y <= old_scene_y + p_y) {
							scene_y = (float)(j + 1) * Size_map_y - p_y;
							old_scene_y = scene_y;
						}
						else {
							// �n�`�̉����瓖�����Ă���
							if (scene_x >= old_scene_x) {
								scene_x = (float)i * Size_map_x - p_x - p_width;
								old_scene_x = scene_x;
							}
							else {
								scene_x = (float)i * Size_map_x - p_x + Size_map_x;
								old_scene_x = scene_x;
							}
						}
					}
				}
			}
			/*�N���A�̃u���b�N�ɓ���������*/
			if (no == 1) {
				if (Checkhit((float)i * Size_map_x - scene_x, (float)j * Size_map_y - scene_y, (float)Size_map_x, (float)Size_map_y, (float)p_x, (float)p_y, (float)p_width, (float)p_height)) {
					stage++;
					nextstage = true;
					if (stage == stage_num - 1) {
						m_flag = true;
					}

				}
			}
		}
	}
}

void Map::Draw() {
	if (scene_x < 0)
		mx = 0;
	else
		mx = (int)(scene_x / Size_map_x);
	if (scene_y < 0)
		my = 0;
	else
		my = (int)(scene_y / Size_map_y);
	for (int j = my; j <= my + Window_size_y / Size_map_y && j < Num_map_y; j++) {
		for (int i = mx; i <= mx + Window_size_x / Size_map_x + 1 && i < Num_map_x; i++) {
			no = mapdata[stage][j][i];
			DrawGraph(i * Size_map_x - (int)scene_x, j * Size_map_y - (int)scene_y, m_image[no], true);
		}
	}
}

void Map::reset_m() {
	scene_x = old_scene_x = (float)Size_map_x - p_x;
	scene_y = old_scene_y = (float)Size_map_y * Num_map_y - Size_map_y - p_y - p_height;
	no = 0;
}