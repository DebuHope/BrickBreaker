//======================================================================================
// サウンド理処理まとめ
// 制作：向出創
//======================================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "main.h"

#include <xaudio2.h>
// Windows7の場合は上記を削除して以下に置き換え.
//#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>

//*****************************************************************************
// サウンドファイル
//*****************************************************************************
typedef enum
{
	SOUND_LABEL_BGM01 = 0,	
	SOUND_LABEL_SE_RUN,		
	SOUND_LABEL_SE_DASH,	
	SOUND_LABEL_SE_JUMP,	
	SOUND_LABEL_SE_SLIDE,
	SOUND_LABEL_SE_HIT,		
	SOUND_LABEL_SE_CANDY,
	SOUND_LABEL_SE_FALL,
	SOUND_LABEL_SE_CHECKPOINT,

	SOUND_LABEL_MAX

} SOUND_LABEL;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitSound(HWND hWnd);
void UninitSound(void);

HRESULT PlaySound(SOUND_LABEL label);	// 再生

void StopSound(SOUND_LABEL label);		// 1つ停止
void StopSound(void);					// 全部停止
void PauseSound( void );				// 一時停止
void ResumeSound( void );				// 再開

void SetVolume(float fVol);				// 音量調整
void SetVolume(float fVol, SOUND_LABEL label);

#endif
