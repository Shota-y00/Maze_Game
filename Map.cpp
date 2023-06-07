#include "Map.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "CheckHit.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //カンマで区切るために必要

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

	/*マップの画像のロード*/
	m_image[0] = NULL;
	m_image[1] = LoadGraph("画像/ゴール2.jpg");
	m_image[5] = LoadGraph("画像/ブロック03.png");

	/*マップデータの読み込み*/
	ifstream ifs("map_data.csv");
	// 開かなかったらエラー
	if (!ifs) {
		cout << "Error! File can not be opened" << endl;
		return;
	}

	string str = "";
	int i = 0, j = 0, k = 0;
	// ファイルの中身を一行ずつ読み取る
	while (getline(ifs, str)) {
		string tmp = "";
		istringstream stream(str);

		// 区切り文字がなくなるまで文字を区切っていく
		while (getline(stream, tmp, ',')) {
			// 区切られた文字がtmpに入る
			mapdata[k][i][j] = atoi(tmp.c_str());
			j++;
		}
		if (i == Num_map_y - 1 && j == Num_map_x - 1) {
			i = j = -1;
			k++;
		}
		else {
			j = 0;
			i++;  // 次の列に移る
		}
	}
	ifs.close();
}

void Map::Finalize() {
	for (int i = 0; i < Num_chip_all; i++)
		DeleteGraph(m_image[i]);
}

void Map::Update() {

	/*sceneの更新*/
	old_scene_x = scene_x;
	old_scene_y = scene_y;

	/*移動処理*/
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
				// ①今まで使用している当たり判定をfloatにして処理を行う(※CheckHitの中を参照) 
				if (Checkhit((float)i * Size_map_x - scene_x, (float)j * Size_map_y - scene_y, (float)Size_map_x, (float)Size_map_y, (float)p_x, (float)p_y, (float)p_width, (float)p_height)) {

					// ②上or真横から当たっているかチェック
					if (scene_y >= old_scene_y) {

						// ③地形よりも上から当たっているかチェックする
						// そうでない場合は横から当たっている
						if (j * Size_map_y - p_height >= old_scene_y + p_y) {
							// ④地形に上から当たっている
							scene_y = (float)(j * Size_map_y - p_y - p_height);
							old_scene_y = scene_y;
						}
						else {
							// ⑤地形の横から当たっている
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

					// 下から当たっているかチェック
					else if (scene_y < old_scene_y) {
						// 地形よりも下から当たっているかチェックする
						// そうでない場合は横から当たっている
						if ((j + 1) * Size_map_y <= old_scene_y + p_y) {
							scene_y = (float)(j + 1) * Size_map_y - p_y;
							old_scene_y = scene_y;
						}
						else {
							// 地形の横から当たっている
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
			/*クリアのブロックに当たった時*/
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