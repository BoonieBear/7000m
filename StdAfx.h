// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__DA6B5BEF_701D_450C_AC48_7AD40AF70286__INCLUDED_)
#define AFX_STDAFX_H__DA6B5BEF_701D_450C_AC48_7AD40AF70286__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "SkinH.h"
#pragma comment(lib,"SkinH.lib")
#define SAFE_DELETE(p)			{if((p) != NULL){delete (p); (p) = NULL;}}
#define SAFE_DELETE_ARRAY(p)	{if((p) != NULL){delete[] (p); (p) = NULL;}}
#define SAFE_RELEASE(p)			{if((p) != NULL){(p)->Release();(p) = NULL;}}
#define SAFE_CLOSE_HANDLE(p)	{if((p) != NULL){CloseHandle(p);(p) = NULL;}}
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__DA6B5BEF_701D_450C_AC48_7AD40AF70286__INCLUDED_)
