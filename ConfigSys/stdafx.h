
// stdafx.h�: fichier Include pour les fichiers Include syst�me standard,
// ou les fichiers Include sp�cifiques aux projets qui sont utilis�s fr�quemment,
// et sont rarement modifi�s

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // Exclure les en-t�tes Windows rarement utilis�s
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // certains constructeurs CString seront explicites

// d�sactive le masquage MFC de certains messages d'avertissement courants et par ailleurs souvent ignor�s
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // composants MFC principaux et standard
#include <afxext.h>         // extensions MFC





#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // Prise en charge MFC pour les contr�les communs Internet Explorer�4
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // Prise en charge des MFC pour les contr�les communs Windows
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // prise en charge des MFC pour les rubans et les barres de contr�les



#define mBitsSet(flags, mask)		(flags|=(mask))
#define mBitsClr(flags, mask)		(flags&=(~(mask)))
#define mBitsTgl(flags, mask)		(flags^=(mask))
#define mBitsMsk(flags, mask)		(flags&(mask))
#define mIsBitsSet(flags, mask)		((flags&(mask))==(mask))
#define mIsBitsClr(flags, mask)		(((~flags)&(mask))==(mask))






