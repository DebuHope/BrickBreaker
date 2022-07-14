//=============================================================================
// 影処理
// 制作：向出創
//=============================================================================
#include "Shadow.h"
#include "Shader.h"
#include "Texture.h"
#include "Mesh.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_SHADOW	L"data/texture/shadow000.jpg"	// テクスチャ

#define M_DIFFUSE		XMFLOAT4(1.0f,1.0f,1.0f,1.0f)
#define M_SPECULAR		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)
#define M_AMBIENT		XMFLOAT4(0.0f,0.0f,0.0f,1.0f)
#define M_EMISSIVE		XMFLOAT4(0.0f,0.0f,0.0f,0.0f)

#define MAX_SHADOW		(200)			// 影の数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct _tShadow
{
	int			nState;		// 状態
	XMFLOAT3	pos;		// 座標
	float		fRadius;	// 半径
}tShadow;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexShadow(ID3D11Device* pDevice);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static MESH		g_mesh;		// メッシュ情報（オブジェクトの表面）
static MATERIAL	g_material;	// マテリアル情報

static tShadow g_shadow[MAX_SHADOW];	// 影ストック

HRESULT LoadShadow(void)
{
	ID3D11Device* pDevice = GetDevice();
	HRESULT hr;

	// 位置回転拡大率の初期化
	g_mesh.scl = XMFLOAT3(1.0f, 1.0f, 1.0f);
	g_mesh.pos = XMFLOAT3(0.0f, 0.0f, 0.0f);
	g_mesh.rot = XMFLOAT3(0.0f, 0.0f, 0.0f);	//X軸　右＋　Y軸　上＋　Z軸　奥＋

	// マテリアルの初期設定
	g_material.Diffuse = M_DIFFUSE;
	g_material.Ambient = M_AMBIENT;
	g_material.Specular = M_SPECULAR;
	g_material.Power = 1.0f;
	g_material.Emissive = M_EMISSIVE;
	g_mesh.pMaterial = &g_material;

	// テクスチャの読み込み
	hr = CreateTextureFromFile(pDevice, TEXTURE_SHADOW, &g_mesh.pTexture);
	if (FAILED(hr))	return hr;

	// ワールドマトリクス初期化
	XMStoreFloat4x4(&g_mesh.mtxTexture, XMMatrixIdentity());
	XMStoreFloat4x4(&g_mesh.mtxWorld, XMMatrixIdentity());

	// 頂点情報の作成
	hr = MakeVertexShadow(pDevice);

	return hr;
}

//=============================================================================
// 初期化処理
//=============================================================================
void InitShadow(void)
{
	// 構造体変数初期化
	for (int i = 0; i < MAX_SHADOW; i++) {
		g_shadow[i].nState = 0;
	}
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	// メッシュ解放
	//ReleaseMesh(&g_mesh);
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{
	// メッシュ更新
	UpdateMesh(&g_mesh);
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	ID3D11DeviceContext* pDeviceContext = GetDeviceContext();

	// 減算合成設定
	SetBlendState(BS_SUBTRACTION);

	// メッシュの描画
	tShadow* pShadow = g_shadow;
	for (int i = 0; i < MAX_SHADOW; i++, pShadow++) {
		// 出てない影は描画しない
		if (pShadow->nState == 0) {
			continue;
		}

		// 倍率
		float ratio = pShadow->pos.y / 320.0f;
		if (ratio < 0.0f)	ratio = 0.0f;
		if (ratio > 1.0f)	ratio = 1.0f;

		// 不透明度
		g_material.Diffuse.w = 0.8f - ratio;
		if (g_material.Diffuse.w < 0.0f)	g_material.Diffuse.w = 0.0f;

		// サイズ
		g_mesh.mtxWorld._11 = g_mesh.mtxWorld._33 = pShadow->fRadius * (1.0f - ratio);

		// 位置
		g_mesh.mtxWorld._41 = pShadow->pos.x;
		g_mesh.mtxWorld._42 = 1.0f;
		g_mesh.mtxWorld._43 = pShadow->pos.z;

		DrawMesh(pDeviceContext, &g_mesh);
	}

	// 元に戻す
	SetBlendState(BS_NONE);
}

HRESULT MakeVertexShadow(ID3D11Device* pDevice)
{
	VERTEX_3D vertexWk[NUM_VERTEX]; //作業用頂点情報
	int		  indexWk[NUM_VERTEX];	//作業用インデックス

	// 頂点座標の設定
	g_mesh.nNumVertex = NUM_VERTEX;
	vertexWk[0].vtx	= XMFLOAT3(-0.5f, 0.0f,  0.5f);
	vertexWk[1].vtx	= XMFLOAT3( 0.5f, 0.0f,  0.5f);
	vertexWk[2].vtx	= XMFLOAT3(-0.5f, 0.0f, -0.5f);
	vertexWk[3].vtx	= XMFLOAT3( 0.5f, 0.0f, -0.5f);
	
	// ディフューズの設定								alpha値				
	vertexWk[0].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertexWk[1].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertexWk[2].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);
	vertexWk[3].diffuse = XMFLOAT4(1.0f, 1.0f, 1.0f, 0.5f);

	// 法線ベクトルの設定
	vertexWk[0].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[1].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[2].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);
	vertexWk[3].nor = XMFLOAT3(0.0f, 1.0f, 0.0f);

	// テクスチャ座標の設定
	vertexWk[0].tex = XMFLOAT2(0.0f, 0.0f);
	vertexWk[1].tex = XMFLOAT2(1.0f, 0.0f);
	vertexWk[2].tex = XMFLOAT2(0.0f, 1.0f);
	vertexWk[3].tex = XMFLOAT2(1.0f, 1.0f);

	// インデックス配列の設定
	g_mesh.nNumIndex = NUM_VERTEX;
	indexWk[0] = 0;
	indexWk[1] = 1;
	indexWk[2] = 2;
	indexWk[3] = 3;

	return MakeMeshVertex(pDevice, &g_mesh, vertexWk, indexWk);
}

// 影の作成
int CreateShadow(XMFLOAT3 pos, float radius)
{
	tShadow* pShadow = g_shadow;
	for (int i = 0; i < MAX_SHADOW; i++, pShadow++) {
		// 出現している影はスルー
		if (pShadow->nState > 0)continue;

		pShadow->pos = pos;
		pShadow->fRadius = radius;
		pShadow->nState = 1;	// 出現
		return i;	// 番号を返す
	}
	return -1;	// 見つからなかった
}

// 影の移動
void MoveShadow(int nShadow, XMFLOAT3 pos)
{
	// 例外処理
	if (nShadow < 0 || nShadow >= MAX_SHADOW)	return;

	g_shadow[nShadow].pos = pos;
}

// 影の解放
void ReleaseShadow(int nShadow)
{
	// 例外処理
	if (nShadow < 0 || nShadow >= MAX_SHADOW)	return;

	g_shadow[nShadow].nState = 0;	// 未使用
}
