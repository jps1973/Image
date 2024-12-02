// Bitmap.h
//
// Note that the following needs to be added to the g++ command
//  -lole32 -loleaut32 -luuid

#pragma once

#include <windows.h>
#include <commctrl.h>
#include <olectl.h>
#include <ole2.h>

#include "Ascii.h"
#include "Common.h"


#define BITMAP_UNABLE_TO_LOAD_ERROR_MESSAGE_FORMAT_STRING						"Unable to load bitmap %s"

BOOL BitmapLoad( LPCTSTR lpszFileName );

BOOL BitmapPaint( HWND hWnd, int nLeft = 0, int nTop = 0 );
