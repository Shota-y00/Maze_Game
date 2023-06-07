#pragma once
#include "DxLib.h"
#include "Task.h"

const int Window_size_x = 640; //窓のxサイズ
const int Window_size_y = 480; // 窓のyサイズ

class Player : Task{
protected:
	int p_image[4];         //プレイヤーの画像
	int dir;                //プレイヤーが向いている向き。画像の出力に使用。0=下,1=左,2=右,3=上
	int p_x, p_y;           //プレイヤーの座標。真ん中に固定
	int p_width, p_height;  //プレイヤーの幅、高さ
	float speed;            //移動スピード 
public:
	Player();
	void Initialize() override;
	void Finalize() override;
	void Update() override;
	void Draw() override;
};

