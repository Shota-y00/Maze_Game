#include "CheckHit.h"
#include "DxLib.h"

int Checkhit(float x1, float y1, float w1, float h1, float x2, float y2, float w2, float h2) { //���W�͍���
	float L1 = x1;      // ��
	float R1 = x1 + w1; // �E(��+����)
	float L2 = x2;      // ��
	float R2 = x2 + w2; // �E(��+����)

	if (R1 <= L2) return 0; // �����������Ȃ�
	if (R2 <= L1) return 0; // �����������Ȃ�

	float U1 = y1;      // ��
	float D1 = y1 + h1; // ��(��+�c��)
	float U2 = y2;      // ��
	float D2 = y2 + h2; // ��(��+�c��)

	if (D1 <= U2) return 0; // �����������Ȃ�
	if (D2 <= U1) return 0; // �����������Ȃ�

	// ����ȊO�̏ꍇ�͓������Ă���
	return 1;
}
