#include "CheckHit.h"
#include "DxLib.h"

int Checkhit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) { //座標は左上
	float L1 = x1;      // 左
	float R1 = x1 + w1; // 右(左+横幅)
	float L2 = x2;      // 左
	float R2 = x2 + w2; // 右(左+横幅)

	if (R1 <= L2) return 0; // 線上も当たらない
	if (R2 <= L1) return 0; // 線上も当たらない

	float U1 = y1;      // 上
	float D1 = y1 + h1; // 下(上+縦幅)
	float U2 = y2;      // 上
	float D2 = y2 + h2; // 下(上+縦幅)

	if (D1 <= U2) return 0; // 線上も当たらない
	if (D2 <= U1) return 0; // 線上も当たらない

	// それ以外の場合は当たっている
	return 1;
}
