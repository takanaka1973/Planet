//
//	共通ヘッダファイル
//

#pragma once

#define STRICT
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include <assert.h>
#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>

// verifyマクロ
#ifdef NDEBUG
#define verify(exp) ((void)(exp))
#else
#define verify(exp) assert(exp)
#endif

