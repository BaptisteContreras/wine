/*
 * X11 display driver definitions
 */

#ifndef __WINE_X11DRV_H
#define __WINE_X11DRV_H

#include "config.h"
#include "ts_xlib.h"
#include "ts_xutil.h"

#include "winbase.h"
#include "windows.h"
#include "gdi.h"
#include "xmalloc.h" /* for XCREATEIMAGE macro */
#include "clipboard.h"
#include "keyboard.h"
#include "message.h"
#include "win.h"

  /* X physical pen */
typedef struct
{
    int          style;
    int          endcap;
    int          linejoin;
    int          pixel;
    int          width;
    char *       dashes;
    int          dash_len;
    int          type;          /* GEOMETRIC || COSMETIC */
} X_PHYSPEN;

  /* X physical brush */
typedef struct
{
    int          style;
    int          fillStyle;
    int          pixel;
    Pixmap       pixmap;
} X_PHYSBRUSH;

  /* X physical font */
typedef UINT32	 X_PHYSFONT;

  /* X physical device */
typedef struct
{
    GC            gc;          /* X Window GC */
    Drawable      drawable;
    X_PHYSFONT    font;
    X_PHYSPEN     pen;
    X_PHYSBRUSH   brush;
    int           backgroundPixel;
    int           textPixel;
} X11DRV_PDEVICE;


typedef struct {
    Pixmap	pixmap;
} X11DRV_PHYSBITMAP;

  /* GCs used for B&W and color bitmap operations */
extern GC BITMAP_monoGC, BITMAP_colorGC;

#define BITMAP_GC(bmp) \
  (((bmp)->bitmap.bmBitsPixel == 1) ? BITMAP_monoGC : BITMAP_colorGC)


/* Wine driver X11 functions */

struct tagDC;
struct tagDeviceCaps;

extern BOOL32 X11DRV_Init(void);
extern BOOL32 X11DRV_BitBlt( struct tagDC *dcDst, INT32 xDst, INT32 yDst,
                             INT32 width, INT32 height, struct tagDC *dcSrc,
                             INT32 xSrc, INT32 ySrc, DWORD rop );
extern BOOL32 X11DRV_EnumDeviceFonts( struct tagDC *dc, LPLOGFONT16 plf,
				      DEVICEFONTENUMPROC dfeproc, LPARAM lp );
extern BOOL32 X11DRV_GetCharWidth( struct tagDC *dc, UINT32 firstChar,
                                   UINT32 lastChar, LPINT32 buffer );
extern BOOL32 X11DRV_GetTextExtentPoint( struct tagDC *dc, LPCSTR str,
                                         INT32 count, LPSIZE32 size );
extern BOOL32 X11DRV_GetTextMetrics(struct tagDC *dc, TEXTMETRIC32A *metrics);
extern BOOL32 X11DRV_PatBlt( struct tagDC *dc, INT32 left, INT32 top,
                             INT32 width, INT32 height, DWORD rop );
extern VOID   X11DRV_SetDeviceClipping(struct tagDC *dc);
extern BOOL32 X11DRV_StretchBlt( struct tagDC *dcDst, INT32 xDst, INT32 yDst,
                                 INT32 widthDst, INT32 heightDst,
                                 struct tagDC *dcSrc, INT32 xSrc, INT32 ySrc,
                                 INT32 widthSrc, INT32 heightSrc, DWORD rop );
extern BOOL32 X11DRV_MoveToEx( struct tagDC *dc, INT32 x, INT32 y,LPPOINT32 pt);
extern BOOL32 X11DRV_LineTo( struct tagDC *dc, INT32 x, INT32 y);
extern BOOL32 X11DRV_Arc( struct tagDC *dc, INT32 left, INT32 top, INT32 right,
			  INT32 bottom, INT32 xstart, INT32 ystart, INT32 xend,
			  INT32 yend );
extern BOOL32 X11DRV_Pie( struct tagDC *dc, INT32 left, INT32 top, INT32 right,
			  INT32 bottom, INT32 xstart, INT32 ystart, INT32 xend,
			  INT32 yend );
extern BOOL32 X11DRV_Chord( struct tagDC *dc, INT32 left, INT32 top,
			    INT32 right, INT32 bottom, INT32 xstart,
			    INT32 ystart, INT32 xend, INT32 yend );
extern BOOL32 X11DRV_Ellipse( struct tagDC *dc, INT32 left, INT32 top,
			      INT32 right, INT32 bottom );
extern BOOL32 X11DRV_Rectangle(struct tagDC *dc, INT32 left, INT32 top,
			      INT32 right, INT32 bottom);
extern BOOL32 X11DRV_RoundRect( struct tagDC *dc, INT32 left, INT32 top,
				INT32 right, INT32 bottom, INT32 ell_width,
				INT32 ell_height );
extern COLORREF X11DRV_SetPixel( struct tagDC *dc, INT32 x, INT32 y,
				 COLORREF color );
extern COLORREF X11DRV_GetPixel( struct tagDC *dc, INT32 x, INT32 y);
extern BOOL32 X11DRV_PaintRgn( struct tagDC *dc, HRGN32 hrgn );
extern BOOL32 X11DRV_Polyline( struct tagDC *dc,const POINT32* pt,INT32 count);
extern BOOL32 X11DRV_PolyBezier( struct tagDC *dc, const POINT32 start, const POINT32* lppt, DWORD cPoints);
extern BOOL32 X11DRV_Polygon( struct tagDC *dc, const POINT32* pt, INT32 count );
extern BOOL32 X11DRV_PolyPolygon( struct tagDC *dc, const POINT32* pt, 
				  const INT32* counts, UINT32 polygons);
extern BOOL32 X11DRV_PolyPolyline( struct tagDC *dc, const POINT32* pt, 
				  const DWORD* counts, DWORD polylines);

extern HGDIOBJ32 X11DRV_SelectObject( struct tagDC *dc, HGDIOBJ32 handle );

extern COLORREF X11DRV_SetBkColor( struct tagDC *dc, COLORREF color );
extern COLORREF X11DRV_SetTextColor( struct tagDC *dc, COLORREF color );
extern BOOL32 X11DRV_ExtFloodFill( struct tagDC *dc, INT32 x, INT32 y,
				   COLORREF color, UINT32 fillType );
extern BOOL32 X11DRV_ExtTextOut( struct tagDC *dc, INT32 x, INT32 y,
				 UINT32 flags, const RECT32 *lprect,
				 LPCSTR str, UINT32 count, const INT32 *lpDx );
extern BOOL32 X11DRV_CreateBitmap( HBITMAP32 hbitmap );
extern BOOL32 X11DRV_DeleteObject( HGDIOBJ32 handle );
extern LONG X11DRV_BitmapBits( HBITMAP32 hbitmap, void *bits, LONG count,
			       WORD flags );
extern INT32 X11DRV_SetDIBitsToDevice( struct tagDC *dc, INT32 xDest,
				       INT32 yDest, DWORD cx, DWORD cy,
				       INT32 xSrc, INT32 ySrc,
				       UINT32 startscan, UINT32 lines,
				       LPCVOID bits, const BITMAPINFO *info,
				       UINT32 coloruse );
extern INT32 X11DRV_DeviceBitmapBits( struct tagDC *dc, HBITMAP32 hbitmap,
				      WORD fGet, UINT32 startscan,
				      UINT32 lines, LPSTR bits,
				      LPBITMAPINFO info, UINT32 coloruse );
extern HANDLE32 X11DRV_LoadOEMResource( WORD id, WORD type );

/* X11 driver internal functions */

extern BOOL32 X11DRV_BITMAP_Init(void);
extern BOOL32 X11DRV_BRUSH_Init(void);
extern BOOL32 X11DRV_DIB_Init(void);
extern BOOL32 X11DRV_FONT_Init( struct tagDeviceCaps* );
extern BOOL32 X11DRV_OBM_Init(void);

struct tagBITMAPOBJ;
extern XImage *X11DRV_BITMAP_GetXImage( const struct tagBITMAPOBJ *bmp );
extern int X11DRV_DIB_GetXImageWidthBytes( int width, int depth );
extern BOOL32 X11DRV_DIB_Init(void);
extern X11DRV_PHYSBITMAP *X11DRV_AllocBitmap( struct tagBITMAPOBJ *bmp );

extern BOOL32 X11DRV_SetupGCForPatBlt( struct tagDC *dc, GC gc,
				       BOOL32 fMapColors );
extern BOOL32 X11DRV_SetupGCForBrush( struct tagDC *dc );
extern BOOL32 X11DRV_SetupGCForPen( struct tagDC *dc );
extern BOOL32 X11DRV_SetupGCForText( struct tagDC *dc );

extern const int X11DRV_XROPfunction[];

extern Display * display;
extern Screen * screen;
extern Window rootWindow;
extern int screenWidth, screenHeight, screenDepth;


/* Xlib critical section */

extern CRITICAL_SECTION X11DRV_CritSection;

extern void _XInitImageFuncPtrs(XImage *);

#define XCREATEIMAGE(image,width,height,bpp) \
{ \
    int width_bytes = X11DRV_DIB_GetXImageWidthBytes( (width), (bpp) ); \
    (image) = TSXCreateImage(display, DefaultVisualOfScreen(screen), \
                           (bpp), ZPixmap, 0, xcalloc( (height)*width_bytes ),\
                           (width), (height), 32, width_bytes ); \
}

/* exported dib functions for now */

/* This structure holds the arguments for DIB_SetImageBits() */
typedef struct
{
    struct tagDC     *dc;
    LPCVOID           bits;
    XImage           *image;
    int               lines;
    DWORD             infoWidth;
    WORD              depth;
    WORD              infoBpp;
    WORD              compression;
    int              *colorMap;
    int               nColorMap;
    Drawable          drawable;
    GC                gc;
    int               xSrc;
    int               ySrc;
    int               xDest;
    int               yDest;
    int               width;
    int               height;
} DIB_SETIMAGEBITS_DESCR;

extern int X11DRV_DIB_GetImageBits( const DIB_SETIMAGEBITS_DESCR *descr );
extern int X11DRV_DIB_SetImageBits( const DIB_SETIMAGEBITS_DESCR *descr );
extern int *X11DRV_DIB_BuildColorMap( struct tagDC *dc, WORD coloruse,
				      WORD depth, const BITMAPINFO *info,
				      int *nColors );

/* X11 windows driver */
extern WND_DRIVER X11DRV_WND_Driver;

extern Window X11DRV_WND_GetXWindow(HWND32 hwnd);

extern BOOL32 X11DRV_WND_CreateDesktopWindow(WND *wndPtr, CLASS *classPtr, BOOL32 bUnicode);
extern BOOL32 X11DRV_WND_CreateWindow(WND *wndPtr, CLASS *classPtr, CREATESTRUCT32A *cs, BOOL32 bUnicode);
extern BOOL32 X11DRV_WND_DestroyWindow(WND *pWnd);
extern WND *X11DRV_WND_SetParent(WND *wndPtr, WND *pWndParent);
extern void X11DRV_WND_ForceWindowRaise(WND *pWnd);
extern void X11DRV_WND_SetWindowPos(WND *wndPtr, const WINDOWPOS32 *winpos, BOOL32 bSMC_SETXPOS);
extern void X11DRV_WND_SetText(WND *wndPtr, LPCSTR text);
extern void X11DRV_WND_SetFocus(WND *wndPtr);
extern void X11DRV_WND_PreSizeMove(WND *wndPtr);
extern void X11DRV_WND_PostSizeMove(WND *wndPtr);

/* X11 clipboard driver */

extern CLIPBOARD_DRIVER X11DRV_CLIPBOARD_Driver;

extern void X11DRV_CLIPBOARD_EmptyClipboard();
extern void X11DRV_CLIPBOARD_SetClipboardData(UINT32 wFormat);
extern BOOL32 X11DRV_CLIPBOARD_RequestSelection();
extern void X11DRV_CLIPBOARD_ResetOwner(WND *pWnd);

void X11DRV_CLIPBOARD_ReadSelection(Window w, Atom prop);
void X11DRV_CLIPBOARD_ReleaseSelection(Window w, HWND32 hwnd);

/* X11 keyboard driver */

extern KEYBOARD_DRIVER X11DRV_KEYBOARD_Driver;

extern void X11DRV_KEYBOARD_Init(void);
extern WORD X11DRV_KEYBOARD_VkKeyScan(CHAR cChar);
extern UINT16 X11DRV_KEYBOARD_MapVirtualKey(UINT16 wCode, UINT16 wMapType);
extern INT16 X11DRV_KEYBOARD_GetKeyNameText(LONG lParam, LPSTR lpBuffer, INT16 nSize);
extern INT16 X11DRV_KEYBOARD_ToAscii(UINT16 virtKey, UINT16 scanCode, LPBYTE lpKeyState, LPVOID lpChar, UINT16 flags);

/* X11 mouse driver */

#if 0 
extern MOUSE_DRIVER X11DRV_MOUSE_Driver;
#endif

/* X11 event driver */

extern EVENT_DRIVER X11DRV_EVENT_Driver;

extern BOOL32 X11DRV_EVENT_Init(void);
extern void X11DRV_EVENT_AddIO(int fd, unsigned flag);
extern void X11DRV_EVENT_DeleteIO(int fd, unsigned flag);
extern BOOL32 X11DRV_EVENT_WaitNetEvent(BOOL32 sleep, BOOL32 peek);
extern void X11DRV_EVENT_Synchronize(void);
extern BOOL32 X11DRV_EVENT_CheckFocus( void );
extern BOOL32 X11DRV_EVENT_QueryPointer(DWORD *posX, DWORD *posY, DWORD *state);
extern void X11DRV_EVENT_DummyMotionNotify(void);
extern BOOL32 X11DRV_EVENT_Pending(void);
extern BOOL16 X11DRV_EVENT_IsUserIdle(void);

#endif  /* __WINE_X11DRV_H */
