#pragma once
#include <windows.h>
// Values and names extracted from twinui.pdb (April 2018 update), documented by toying with the API.
// Output from DIA2Dump above the definitions.

// Enum           : ACCENT_STATE, Type: int
// Data           :   constant 0x0, Constant, Type: int, ACCENT_DISABLED
// Data           :   constant 0x1, Constant, Type: int, ACCENT_ENABLE_GRADIENT
// Data           :   constant 0x2, Constant, Type: int, ACCENT_ENABLE_TRANSPARENTGRADIENT
// Data           :   constant 0x3, Constant, Type: int, ACCENT_ENABLE_BLURBEHIND
// Data           :   constant 0x4, Constant, Type: int, ACCENT_ENABLE_ACRYLICBLURBEHIND
// Data           :   constant 0x5, Constant, Type: int, ACCENT_ENABLE_HOSTBACKDROP
// Data           :   constant 0x6, Constant, Type: int, ACCENT_INVALID_STATE
enum ACCENT_STATE : INT {				// Affects the rendering of the background of a window.
	ACCENT_DISABLED = 0,					// Default value. Background is black.
	ACCENT_ENABLE_GRADIENT = 1,				// Background is GradientColor, alpha channel ignored.
	ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,	// Background is GradientColor.
	ACCENT_ENABLE_BLURBEHIND = 3,			// Background is GradientColor, with blur effect.
	ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,	// Background is GradientColor, with acrylic blur effect.
	ACCENT_ENABLE_HOSTBACKDROP = 5,			// Unknown.
	ACCENT_INVALID_STATE = 6				// Unknown. Seems to draw background fully transparent.
};

// UserDefinedType: ACCENT_POLICY
// Data           :   this+0x0, Member, Type: enum ACCENT_STATE, AccentState
// Data           :   this+0x4, Member, Type: unsigned int, AccentFlags
// Data           :   this+0x8, Member, Type: unsigned long, GradientColor
// Data           :   this+0xC, Member, Type: long, AnimationId
struct ACCENT_POLICY {			// Determines how a window's background is rendered.
	ACCENT_STATE	AccentState;	// Background effect.
	UINT			AccentFlags;	// Flags. Set to 2 to tell GradientColor is used, rest is unknown.
	COLORREF		GradientColor;	// Background color.
	LONG			AnimationId;	// Unknown
};

// Enum           : WINDOWCOMPOSITIONATTRIB, Type: int
// Data           :   constant 0x0, Constant, Type: int, WCA_UNDEFINED
// Data           :   constant 0x1, Constant, Type: int, WCA_NCRENDERING_ENABLED
// Data           :   constant 0x2, Constant, Type: int, WCA_NCRENDERING_POLICY
// Data           :   constant 0x3, Constant, Type: int, WCA_TRANSITIONS_FORCEDISABLED
// Data           :   constant 0x4, Constant, Type: int, WCA_ALLOW_NCPAINT
// Data           :   constant 0x5, Constant, Type: int, WCA_CAPTION_BUTTON_BOUNDS
// Data           :   constant 0x6, Constant, Type: int, WCA_NONCLIENT_RTL_LAYOUT
// Data           :   constant 0x7, Constant, Type: int, WCA_FORCE_ICONIC_REPRESENTATION
// Data           :   constant 0x8, Constant, Type: int, WCA_EXTENDED_FRAME_BOUNDS
// Data           :   constant 0x9, Constant, Type: int, WCA_HAS_ICONIC_BITMAP
// Data           :   constant 0xA, Constant, Type: int, WCA_THEME_ATTRIBUTES
// Data           :   constant 0xB, Constant, Type: int, WCA_NCRENDERING_EXILED
// Data           :   constant 0xC, Constant, Type: int, WCA_NCADORNMENTINFO
// Data           :   constant 0xD, Constant, Type: int, WCA_EXCLUDED_FROM_LIVEPREVIEW
// Data           :   constant 0xE, Constant, Type: int, WCA_VIDEO_OVERLAY_ACTIVE
// Data           :   constant 0xF, Constant, Type: int, WCA_FORCE_ACTIVEWINDOW_APPEARANCE
// Data           :   constant 0x10, Constant, Type: int, WCA_DISALLOW_PEEK
// Data           :   constant 0x11, Constant, Type: int, WCA_CLOAK
// Data           :   constant 0x12, Constant, Type: int, WCA_CLOAKED
// Data           :   constant 0x13, Constant, Type: int, WCA_ACCENT_POLICY
// Data           :   constant 0x14, Constant, Type: int, WCA_FREEZE_REPRESENTATION
// Data           :   constant 0x15, Constant, Type: int, WCA_EVER_UNCLOAKED
// Data           :   constant 0x16, Constant, Type: int, WCA_VISUAL_OWNER
// Data           :   constant 0x17, Constant, Type: int, WCA_HOLOGRAPHIC
// Data           :   constant 0x18, Constant, Type: int, WCA_EXCLUDED_FROM_DDA
// Data           :   constant 0x19, Constant, Type: int, WCA_PASSIVEUPDATEMODE
// Data           :   constant 0x1A, Constant, Type: int, WCA_LAST
enum WINDOWCOMPOSITIONATTRIB : INT {	// Determines what attribute is being manipulated.
    WCA_UNDEFINED = 0,
    WCA_NCRENDERING_ENABLED = 1,
    WCA_NCRENDERING_POLICY = 2,
    WCA_TRANSITIONS_FORCEDISABLED = 3,
    WCA_ALLOW_NCPAINT = 4,
    WCA_CAPTION_BUTTON_BOUNDS = 5,
    WCA_NONCLIENT_RTL_LAYOUT = 6,
    WCA_FORCE_ICONIC_REPRESENTATION = 7,
    WCA_EXTENDED_FRAME_BOUNDS = 8,
    WCA_HAS_ICONIC_BITMAP = 9,
    WCA_THEME_ATTRIBUTES = 10,
    WCA_NCRENDERING_EXILED = 11,
    WCA_NCADORNMENTINFO = 12,
    WCA_EXCLUDED_FROM_LIVEPREVIEW = 13,
    WCA_VIDEO_OVERLAY_ACTIVE = 14,
    WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15,
    WCA_DISALLOW_PEEK = 16,
    WCA_CLOAK = 17,
    WCA_CLOAKED = 18,
    WCA_ACCENT_POLICY = 19,
    WCA_FREEZE_REPRESENTATION = 20,
    WCA_EVER_UNCLOAKED = 21,
    WCA_VISUAL_OWNER = 22,
    WCA_HOLOGRAPHIC = 23,
    WCA_EXCLUDED_FROM_DDA = 24,
    WCA_PASSIVEUPDATEMODE = 25,
    WCA_USEDARKMODECOLORS = 26,
    WCA_CORNER_STYLE = 27,
    WCA_PART_COLOR = 28,
    WCA_DISABLE_MOVESIZE_FEEDBACK = 29,
    WCA_LAST = 30
};

// UserDefinedType: tagWINDOWCOMPOSITIONATTRIBDATA
// Data           :   this+0x0, Member, Type: enum WINDOWCOMPOSITIONATTRIB, Attrib
// Data           :   this+0x8, Member, Type: void *, pvData
// Data           :   this+0x10, Member, Type: unsigned int, cbData
struct WINDOWCOMPOSITIONATTRIBDATA {	// Options for [Get/Set]WindowCompositionAttribute.
	WINDOWCOMPOSITIONATTRIB	Attrib;			// Type of what is being get or set.
	LPVOID					pvData;			// Pointer to memory that will receive what is get or that contains what will be set.
	UINT					cbData;			// Size of the data being pointed to by pvData.
};

typedef BOOL (WINAPI* PFN_SET_WINDOW_COMPOSITION_ATTRIBUTE)(HWND, const WINDOWCOMPOSITIONATTRIBDATA *);