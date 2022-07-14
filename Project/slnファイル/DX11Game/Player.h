//=============================================================================
// �v���C���[�܂Ƃ�
// ����F���o�n
//=============================================================================
#pragma once

#include "Main.h"

#define MAX_PLAYER		(1)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT LoadPlayer();
void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();

XMFLOAT4X4 GetPlayerWorld(int no);
XMFLOAT3 GetPlayerCenter(int no);
XMFLOAT3 GetPlayerBBox(int no);

XMFLOAT3 GetPlayerPos(int no);
XMFLOAT3 GetPlayerSize(int no);
bool IsPlayer(int no);
void DestroyPlayer(int no);

XMFLOAT3 GetPlayerVel(int no);

float GetPlayerDashCount();
float GetPlayerJumpCount();
float GetPlayerSlide();
