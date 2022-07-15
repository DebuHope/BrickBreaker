//======================================================================================
// �G���h���[�������܂Ƃ�
// ����F���o�n
//======================================================================================
#pragma once

#include "Main.h"

#define MAX_BLOCK		(100)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT LoadBlock(void);
void InitBlock(void);
void UninitBlock(void);
void UpdateBlock(void);
void DrawBlock(void);

// �ݒu(pos = �o���ʒu, scl = �傫��, type = ���f���̎��)
int SetBlock(XMFLOAT3 pos, XMFLOAT3 scl, int type);

XMFLOAT4X4 GetBlockWorld(int no);
XMFLOAT3 GetBlockCenter(int no);
XMFLOAT3 GetBlockBBox(int no);

XMFLOAT3 GetBlockPos(int no);
XMFLOAT3 GetBlockSize(int no);
bool IsBlock(int no);
void DestroyBlock(int no);