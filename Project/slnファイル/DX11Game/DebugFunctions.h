#pragma once

#include <d2d1.h>

#include "D2DText.h"

// lib指定
#pragma comment(lib,"d2d1.lib")


// デバッグ用関数
#ifdef _DEBUG
// 登録されているフォントを一覧で表示する
// 使用する箇所では必ずD2DTextMng.AllRemoveを呼ぶこと
void DisplayFontList(D2D1_POINT_2F pos);

#endif // _DEBUG

