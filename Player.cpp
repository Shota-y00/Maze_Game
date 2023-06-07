#include "Player.h"
#include "Keyboard.h"
#include "DxLib.h"

Player::Player() {
	p_width = p_height = 50;
	p_x = Window_size_x / 2 - p_width / 2;
	p_y = Window_size_y / 2 - p_height / 2;
	speed = 5.0f;
	dir = 0;
}

void Player::Initialize() {
	LoadDivGraph("‰æ‘œ/ƒvƒŒƒCƒ„[‰æ‘œ2.png", 4, 1, 4, 50, 50, p_image);
}

void Player::Finalize() {
	for (int i = 0; i < 4; i++)
		DeleteGraph(p_image[i]);
}

void Player::Update() {

	/*ˆÚ“®ˆ—*/
	if (Keyboard_Get(KEY_INPUT_UP) != 0) 
		dir = 3;
	if (Keyboard_Get(KEY_INPUT_DOWN) != 0) 
		dir = 0;
	if (Keyboard_Get(KEY_INPUT_RIGHT) != 0)
		dir = 2;
	if (Keyboard_Get(KEY_INPUT_LEFT) != 0)
		dir = 1;
}

void Player::Draw() {
	DrawGraph(p_x, p_y, p_image[dir], true);
}