#pragma once
#include "Player.h"

const int Size_map_x = 60; //マップチップのxサイズ
const int Size_map_y = 60; //マップチップのyサイズ
const int Num_chip_x = 10;  //xのマップチップの種類数
const int Num_chip_y = 2;  //yのマップチップの種類数
const int Num_chip_all = Num_chip_x * Num_chip_y; //総マップチップの種類数

const int Num_map_x = 50; //横のマップチップの個数 70*50=3500
const int Num_map_y = 50; //縦のマップチップの個数 70*50=3500



typedef enum {  //ステージ数
	stage1,
	stage2,

	stage_none, //空配列、ゲームクリアのときに必要
	stage_num,
}stage;

class Map :public Player{
protected:
	int mapdata[stage_num][Num_map_y][Num_map_x] = {};  //マップデータ
	int m_image[Num_chip_all] = {};//壁などの画像
	float scene_x;                 //フレームの左上のx座標
	float scene_y;                 //フレームの左上のy座標
	float old_scene_x, old_scene_y;
	bool m_flag;                   //クリアフラグ。false = not clear, true = clear
	bool nextstage;                //次のステージに進むフラグ
	int stage, no;                 //現在のステージ数
public:
	Map();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Map_Checkhit();
	void Draw() override;
	void reset_m();
};