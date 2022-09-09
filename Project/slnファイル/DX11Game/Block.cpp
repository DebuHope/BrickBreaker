//======================================================================================
// �G���h���[������
// ����F���o�n
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Block.h"
#include "main.h"
#include "Player.h"
#include "Input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BLOCK01	"data/model/text/block_01.fbx"
#define BLOCK02	"data/model/text/block_02.fbx"

#define MAX_BLOCK_MODEL		(4)

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct _tBlock
{
	XMFLOAT4X4	mtxWorld;

	int	nType;	// ���
	XMFLOAT3 pos;	// ���W
	XMFLOAT3 rot;	// ��]
	XMFLOAT3 scl;	// �g�嗦
	XMFLOAT3 vel;	// ���x
	bool	nState;	// �s��(0�ȉ�:���g�p 1�ȏ�:�ʏ�)
}tBlock;

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static CAssimpModel	g_model[MAX_BLOCK_MODEL];	// ���f���f�[�^
static tBlock			g_block[MAX_BLOCK];


HRESULT LoadBlock(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// ���f���f�[�^�̓ǂݍ���
	hr = g_model[0].Load(pDevice, pDeviceContext, BLOCK01);
	hr = g_model[1].Load(pDevice, pDeviceContext, BLOCK02);

	return hr;
}

//=============================================================================
// ����������
//=============================================================================
void InitBlock(void)
{
	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		g_block[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_block[i].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_block[i].scl = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_block[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_block[i].nState = 0;
	}

	// ���[���h�}�g���b�N�X�̏�����
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		XMStoreFloat4x4(&g_block[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// �I������
//=============================================================================
void UninitBlock(void)
{
	// ���f���̉��
	//for (int i = 0; i < MAX_BLOCK_MODEL; i++) {
	//	g_model[i].Release();
	//}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (g_block[i].nState == 0)	continue;

		// �ʒu�̍X�V
		g_block[i].pos.x += g_block[i].vel.x;
		g_block[i].pos.y += g_block[i].vel.y;
		g_block[i].pos.z += g_block[i].vel.z;


		// ���[���h�}�g���b�N�X�̏�����
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;
		mtxWorld = XMMatrixIdentity();

		// �X�P�[���𔽉f
		mtxScl = XMMatrixScaling(
			g_block[i].scl.x,
			g_block[i].scl.y,
			g_block[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// ��]�𔽉f
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_block[i].rot.x),
			XMConvertToRadians(g_block[i].rot.y),
			XMConvertToRadians(g_block[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// �ړ��𔽉f
		mtxTranslate = XMMatrixTranslation(
			g_block[i].pos.x,
			g_block[i].pos.y,
			g_block[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ���[���h�}�g���b�N�X�ݒ�
		XMStoreFloat4x4(&g_block[i].mtxWorld, mtxWorld);

#ifdef _DEBUG

		/*PrintDebugProc("BallAngle X : %0.1f Y : %0.1f\n\n\n", angleX, angleY);*/
#endif // _DEBUG
	}
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

		// ���f���\��
		if (g_block[i].nState == 0)	continue;

		g_model[g_block[i].nType].Draw(pDeviceContext, g_block[i].mtxWorld);
	}
}

// �ݒu
int SetBlock(XMFLOAT3 pos, XMFLOAT3 scl, int type)
{
	_tBlock* pBlock = g_block;
	for (int i = 0; i < MAX_BLOCK; ++i, ++pBlock)
	{	// �o�����Ă���ꍇ�X���[
		if (pBlock->nState != 0) continue;

		pBlock->pos = pos;
		pBlock->scl = scl;
		pBlock->nState = 1;	// �o��
		pBlock->nType = type;

		return i;	// �ԍ���Ԃ�
	}
	return -1;	// ������Ȃ�����
}

XMFLOAT4X4 GetBlockWorld(int no)
{
	return g_block[no].mtxWorld;
}

// ���S���W����
XMFLOAT3 GetBlockCenter(int no)
{
	if (no < 0 || no >= MAX_BLOCK) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}

	XMFLOAT3 pos = g_model[g_block[no].nType].GetCenter();
	pos.x += g_block[no].pos.x;
	pos.y += g_block[no].pos.y;
	pos.z += g_block[no].pos.z;
	return pos;
}

// ���f���T�C�Y����
XMFLOAT3 GetBlockBBox(int no)
{
	if (no < 0 || no >= MAX_BLOCK) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// ���f������T�C�Y����������
	return g_model[g_block[no].nType].GetBBox();
}

// ���W����
XMFLOAT3 GetBlockPos(int no)
{
	if (no < 0 || no >= MAX_BLOCK) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_block[no].pos;
}

// �T�C�Y����
XMFLOAT3 GetBlockSize(int no)
{
	if (no < 0 || no >= MAX_BLOCK) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(g_block[no].scl.x, g_block[no].scl.y, g_block[no].scl.z);
}


//�����蔻��p�@�������Ă��邩
bool IsBlock(int no)
{
	return true;
}

// �������Ă��邩
bool IsBlock()
{
	bool is = false;

	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (g_block[i].nType == 0) is |= (g_block[i].nState == 1);

	}

	return is;
}

// �\�����Ȃ�
void DestroyBlock(int no)
{
	if (no < 0 || no >= MAX_BLOCK || g_block[no].nType != 0) {
		return;
	}
	g_block[no].nState = 0;
	g_block[no].pos = XMFLOAT3(0.0f, -1000.0f, 100.0f);
}