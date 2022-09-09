//======================================================================================
// �V�[���J�ڏ���
// ����F���o�n
//======================================================================================

// �w�b�_�t�@�C���̃C���N���[�h
#include <stdlib.h>
#include"transition.h"
#include"Texture.h"
#include"polygon.h"
#include "Player.h"
#include "Debugproc.h"
#include "Player.h"
#include "Life.h"
#include "Game.h"
#include "Score.h"

// �}�N����`

#define MAX_TEXTURE (1)

#define TRANSITION1		_T("data/texture/title_01.png")

// �O���[�o���ϐ��錾
static ID3D11ShaderResourceView* g_pTexture[MAX_TEXTURE];	// �e�N�X�`��	

static XMFLOAT2 g_Position[2];		// ���W
static float	g_Vel;			// ���x
static XMFLOAT2 g_Size;			// �T�C�Y
static float	g_Angle;		// ��]�p�x
static XMFLOAT2 g_TexCoord;		// �e�N�X�`�����W(�|���S���̍���)(TextureCoordinate)
static XMFLOAT2 g_TexFrameSize;	// �e�N�X�`����\��t����T�C�Y
static int		DrawTexNo;
static int		waitCount;

static bool		StartFlag;
static ETypeScene NextScene;
static bool waitingFlag;

// static = �ϐ���������Ă��Ă������̃w�b�_�t�@�C���݂̂̕ϐ��ɂȂ�

HRESULT LoadTransition()
{
	HRESULT hr = S_OK;
	ID3D11Device*	pDevice = GetDevice();

	hr = CreateTextureFromFile(pDevice, TRANSITION1, &g_pTexture[0]);
	if (FAILED(hr)) return hr;

	return hr;
}

//======================================================================================
// ������
//======================================================================================
void InitTransition()
{
	// �p�����[�^�̏�����
	//g_Position[0] = XMFLOAT2(-1920.0f / 4.0f, 0);
	//g_Position[1] = XMFLOAT2(1920.0f / 4.0f, 0);
	g_Position[0] = XMFLOAT2(-1920.0f / 2.0f - 240.0f, 0);
	g_Position[1] = XMFLOAT2(1920.0f / 2.0f + 240.0f, 0);
	g_Vel = 0.0f;
	g_Size			= XMFLOAT2(SCREEN_WIDTH, SCREEN_HEIGHT);
	g_Angle			= 0.0f;
	g_TexCoord		= XMFLOAT2(0.0f, 0.0f);
	g_TexFrameSize	= XMFLOAT2(1.0f, 1.0f);
	DrawTexNo = 0;
	waitCount = 0;
	StartFlag = false;
	waitingFlag = false;
}

//======================================================================================
// �I��
//======================================================================================
void UninitTransition()
{
	//// �e�N�X�`����Еt��
	//for (int i = 0; i < MAX_TEXTURE; i++)
	//{
	//	SAFE_RELEASE(g_pTexture[i]);
	//}
}

//======================================================================================
// �X�V
//======================================================================================
void UpdateTransition()
{
	// �V�[���؂�ւ�
	if (StartFlag == true) 
	{
		g_Position[0].x += g_Vel -= 1.45f;
		g_Position[1].x -= g_Vel -= 1.45f;

		if (g_Position[0].x >= -1920.0f / 4.0f || g_Position[1].x <= 1920.0f / 4.0f)
		{
			g_Position[0].x = -1920.0f / 4.0f;
			g_Position[1].x = 1920.0f / 4.0f;
			g_Position[0].x += g_Vel = 0.0f;
			g_Position[1].x += g_Vel = 0.0f;
			waitingFlag = true;
			StartFlag = false;
			
		}
	}

	if (waitCount == 20)
	{
		StartSceneChange(NextScene);
	}

	if (waitCount == 40)
	{
		StartFlag = true;
	}

	if (g_Position[0].x <= -1920.0f / 2.0f - 240.0f && g_Position[1].x >= 1920.0f / 2.0f + 240.0f)
	{
		g_Position[0].x = -1920.0f / 2.0f - 240.0f;
		g_Position[1].x = 1920.0f / 2.0f + 240.0f;
	}

	waitCount++;
}

//======================================================================================
// �`��
//======================================================================================
void DrawTransition()
{
	// �|���S���̕`�揈��
	ID3D11DeviceContext*	pDeviceContext = GetDeviceContext();

	SetPolygonAngle(0.0f);
	SetPolygonAlpha(1.0f);
	SetPolygonColor(1.0f, 1.0f, 1.0f);

	// �|���S���̏��ݒ�
	// ��
	SetPolygonSize(1920 / 2, 1080);
	SetPolygonPos(g_Position[0].x, g_Position[0].y);
	SetPolygonUV(0, 0);
	SetPolygonFrameSize(0.5, 1);
	SetPolygonTexture(g_pTexture[0]);
	DrawPolygon(pDeviceContext);
	// �E
	SetPolygonSize(1920 / 2, 1080);
	SetPolygonPos(g_Position[1].x, g_Position[1].y);
	SetPolygonUV(0.5, 0);
	SetPolygonFrameSize(0.5, 1);
	SetPolygonTexture(g_pTexture[0]);
	DrawPolygon(pDeviceContext);
}

//======================================================================================
// �V�[���J��
//======================================================================================
void StartChange(ETypeScene nextscene, int no)
{
	if (StartFlag != true) {
		StartFlag = true;
		NextScene = nextscene;
		g_Vel = 67.0f;
		waitCount = 0;

		switch (no)
		{
		case 0:	// �Q�[���J�n��
			waitCount = -180;
			//DrawTexNo = rand() % 2;
			break;
		case 1:
			//DrawTexNo = 2;
			break;
		case 2:
			//DrawTexNo = 3;
			//waitCount = -180;
			break;
		}
	}
}
