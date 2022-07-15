//======================================================================================
// �G���h���[�������܂Ƃ�
// ����F���o�n
//======================================================================================
#pragma once

#include "Main.h"

#define MAX_TEXT		(1)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT LoadText(void);
void InitText(void);
void UninitText(void);
void UpdateText(void);
void DrawTex(void);

// �ݒu(pos = �o���ʒu, scl = �傫��, type = ���f���̎��)
int SetText(XMFLOAT3 pos, XMFLOAT3 scl, XMFLOAT3 dir, int type);

XMFLOAT4X4 GetTextWorld(int no);
XMFLOAT3 GetTextCenter(int no);
XMFLOAT3 GetTextBBox(int no);

XMFLOAT3 GetTextPos(int no);
XMFLOAT3 GetTextSize(int no);
bool IsText(int no);
void DestroyText(int no);

void PadlleBall(int no);
void SetAngleX(float _angleX);
void SetAngleY(float _angleY);
float	GetBallAngleX(int no);
float	GetBallAngleY(int no);

// �{�[�����u���b�N�Ɠ����������̋�������(�ȈՔ����)
void CheckBallHitDirection(XMFLOAT3* BCenter, XMFLOAT3* BSize);