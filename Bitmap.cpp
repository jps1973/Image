// Bitmap.cpp

#include "Bitmap.h"

// Global variables
static HBITMAP g_hBitmap;
static int g_nWidth;
static int g_nHeight;

BOOL BitmapLoad( LPCTSTR lpszFileName )
{
	BOOL bResult = TRUE;

	HANDLE hFile;

	// Open file
	hFile = CreateFile( lpszFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	
	// Ensure that file was opened
	if( hFile != INVALID_HANDLE_VALUE )
	{
		// Successfully opened file
		DWORD dwFileSize;

		// Get file size
		dwFileSize = GetFileSize( hFile, NULL );
		
		// Ensure that file size was got
		if( dwFileSize != INVALID_FILE_SIZE )
		{
			// Successfully got file size
			HGLOBAL hGlobal;

			// Allocate global memory
			hGlobal = GlobalAlloc( GPTR, dwFileSize );

			// Ensure that global memory was allocated
			if( hGlobal )
			{
				// Successfully allocated global memory
				LPVOID lpGlobal;

				// Get pointer to global memory
				lpGlobal = ( LPVOID )hGlobal;

				// Read file
				if( ReadFile( hFile, lpGlobal, dwFileSize, NULL, NULL ) )
				{
					// Successfully read file
					IStream* lpStream;

					// Create stream
					CreateStreamOnHGlobal( hGlobal, false, &lpStream );
					
					// Ensure that stream was created
					if( lpStream )
					{
						// Successfully created stream
						IPicture* lpPicture;

						// Load picture
						OleLoadPicture( lpStream, 0, false, IID_IPicture, ( void ** )&lpPicture );

						// Ensure that picture was loaded
						if( lpPicture )
						{
							// Successfully loaded picture
							HBITMAP hBitmap = 0;
							BITMAP bm;

							// Get bitmap from picture
							lpPicture->get_Handle( ( unsigned int* )&hBitmap );

							// Copy bitmap into global bitmap
							g_hBitmap = ( HBITMAP )CopyImage( hBitmap, IMAGE_BITMAP, 0, 0, LR_COPYRETURNORG );
							// This is necessary because the bitmap got from the picture will be destroyed
							// when the picture is released

							// Copy bitmap handle into bitmap structure
							GetObject( g_hBitmap, sizeof( bm ), &bm );

							// Update global size values
							g_nWidth	= bm.bmWidth;
							g_nHeight	= bm.bmHeight;

							// Update return value
							bResult = TRUE;

							// Release picture
							lpPicture->Release();

						} // End of successfully loaded picture

						// Release stream
						lpStream->Release();

					} // End of successfully created stream

				} // End of successfully read file

				// Free global memory
				GlobalFree( hGlobal );

			} // End of successfully allocated global memory

		} // End of successfully got file size

		// Close file
		CloseHandle( hFile );

	} // End of successfully opened file

	return bResult;

} // End of function BitmapLoad

BOOL BitmapPaint( HWND hWnd, int nLeft, int nTop )
{
	BOOL bResult;

	PAINTSTRUCT ps;
	HDC hdcWindow;
	HDC hdcBitmap;
	HBITMAP hbmOld;

	// Begin painting
	hdcWindow = BeginPaint( hWnd, &ps );

	// Create bitmap dc
	hdcBitmap = CreateCompatibleDC( hdcWindow );

	// Select global bitmap into dc
	hbmOld = ( HBITMAP )SelectObject( hdcBitmap, g_hBitmap );

	// Paint bitmap onto window
	bResult = BitBlt( hdcWindow, nLeft, nTop, g_nWidth, g_nHeight, hdcBitmap, 0, 0, SRCCOPY );

	// Remove bitmap from dc
	SelectObject( hdcBitmap, hbmOld );

	// Delete bitmap dc
	DeleteDC( hdcBitmap );

	// End painting
	EndPaint( hWnd, &ps );

	return bResult;

} // End of function BitmapLoad
