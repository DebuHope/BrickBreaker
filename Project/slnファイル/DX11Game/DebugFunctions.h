#pragma once

#include <d2d1.h>

#include "D2DText.h"

// lib�w��
#pragma comment(lib,"d2d1.lib")


// �f�o�b�O�p�֐�
#ifdef _DEBUG
// �o�^����Ă���t�H���g���ꗗ�ŕ\������
// �g�p����ӏ��ł͕K��D2DTextMng.AllRemove���ĂԂ���
void DisplayFontList(D2D1_POINT_2F pos);

#endif // _DEBUG

