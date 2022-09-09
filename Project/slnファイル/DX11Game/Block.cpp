//======================================================================================
// エンドロール処理
// 制作：向出創
//======================================================================================
#include "AssimpModel.h"
#include "Debugproc.h"
#include "Block.h"
#include "main.h"
#include "Player.h"
#include "Input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLOCK01	"data/model/text/block_01.fbx"
#define BLOCK02	"data/model/text/block_02.fbx"

#define MAX_BLOCK_MODEL		(4)

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct _tBlock
{
	XMFLOAT4X4	mtxWorld;

	int	nType;	// 種類
	XMFLOAT3 pos;	// 座標
	XMFLOAT3 rot;	// 回転
	XMFLOAT3 scl;	// 拡大率
	XMFLOAT3 vel;	// 速度
	bool	nState;	// 行動(0以下:未使用 1以上:通常)
}tBlock;

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static CAssimpModel	g_model[MAX_BLOCK_MODEL];	// モデルデータ
static tBlock			g_block[MAX_BLOCK];


HRESULT LoadBlock(void)
{
	HRESULT hr = S_OK;
	ID3D11Device* pDevice = GetDevice();
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// モデルデータの読み込み
	hr = g_model[0].Load(pDevice, pDeviceContext, BLOCK01);
	hr = g_model[1].Load(pDevice, pDeviceContext, BLOCK02);

	return hr;
}

//=============================================================================
// 初期化処理
//=============================================================================
void InitBlock(void)
{
	// 位置・回転・スケールの初期設定
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		g_block[i].pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_block[i].rot = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_block[i].scl = XMFLOAT3(1.0f, 1.0f, 1.0f);
		g_block[i].vel = XMFLOAT3(0.0f, 0.0f, 0.0f);
		g_block[i].nState = 0;
	}

	// ワールドマトリックスの初期化
	XMMATRIX mtxWorld;
	mtxWorld = XMMatrixIdentity();
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		XMStoreFloat4x4(&g_block[i].mtxWorld, mtxWorld);
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitBlock(void)
{
	// モデルの解放
	//for (int i = 0; i < MAX_BLOCK_MODEL; i++) {
	//	g_model[i].Release();
	//}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (g_block[i].nState == 0)	continue;

		// 位置の更新
		g_block[i].pos.x += g_block[i].vel.x;
		g_block[i].pos.y += g_block[i].vel.y;
		g_block[i].pos.z += g_block[i].vel.z;


		// ワールドマトリックスの初期化
		XMMATRIX mtxWorld, mtxRot, mtxScl, mtxTranslate;
		mtxWorld = XMMatrixIdentity();

		// スケールを反映
		mtxScl = XMMatrixScaling(
			g_block[i].scl.x,
			g_block[i].scl.y,
			g_block[i].scl.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxScl);

		// 回転を反映
		mtxRot = XMMatrixRotationRollPitchYaw(
			XMConvertToRadians(g_block[i].rot.x),
			XMConvertToRadians(g_block[i].rot.y),
			XMConvertToRadians(g_block[i].rot.z)
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxRot);

		// 移動を反映
		mtxTranslate = XMMatrixTranslation(
			g_block[i].pos.x,
			g_block[i].pos.y,
			g_block[i].pos.z
		);
		mtxWorld = XMMatrixMultiply(mtxWorld, mtxTranslate);

		// ワールドマトリックス設定
		XMStoreFloat4x4(&g_block[i].mtxWorld, mtxWorld);

#ifdef _DEBUG

		/*PrintDebugProc("BallAngle X : %0.1f Y : %0.1f\n\n\n", angleX, angleY);*/
#endif // _DEBUG
	}
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawBlock(void)
{
	for (int i = 0; i < MAX_BLOCK; i++)
	{
		ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

		// モデル表示
		if (g_block[i].nState == 0)	continue;

		g_model[g_block[i].nType].Draw(pDeviceContext, g_block[i].mtxWorld);
	}
}

// 設置
int SetBlock(XMFLOAT3 pos, XMFLOAT3 scl, int type)
{
	_tBlock* pBlock = g_block;
	for (int i = 0; i < MAX_BLOCK; ++i, ++pBlock)
	{	// 出現している場合スルー
		if (pBlock->nState != 0) continue;

		pBlock->pos = pos;
		pBlock->scl = scl;
		pBlock->nState = 1;	// 出現
		pBlock->nType = type;

		return i;	// 番号を返す
	}
	return -1;	// 見つからなかった
}

XMFLOAT4X4 GetBlockWorld(int no)
{
	return g_block[no].mtxWorld;
}

// 中心座標所得
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

// モデルサイズ所得
XMFLOAT3 GetBlockBBox(int no)
{
	if (no < 0 || no >= MAX_BLOCK) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	// モデルからサイズ半分を所得
	return g_model[g_block[no].nType].GetBBox();
}

// 座標所得
XMFLOAT3 GetBlockPos(int no)
{
	if (no < 0 || no >= MAX_BLOCK) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return g_block[no].pos;
}

// サイズ所得
XMFLOAT3 GetBlockSize(int no)
{
	if (no < 0 || no >= MAX_BLOCK) {
		return XMFLOAT3(0.0f, 0.0f, 0.0f);
	}
	return XMFLOAT3(g_block[no].scl.x, g_block[no].scl.y, g_block[no].scl.z);
}


//当たり判定用　生存しているか
bool IsBlock(int no)
{
	return true;
}

// 生存しているか
bool IsBlock()
{
	bool is = false;

	for (int i = 0; i < MAX_BLOCK; i++)
	{
		if (g_block[i].nType == 0) is |= (g_block[i].nState == 1);

	}

	return is;
}

// 表示しない
void DestroyBlock(int no)
{
	if (no < 0 || no >= MAX_BLOCK || g_block[no].nType != 0) {
		return;
	}
	g_block[no].nState = 0;
	g_block[no].pos = XMFLOAT3(0.0f, -1000.0f, 100.0f);
}