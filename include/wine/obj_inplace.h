/*
 * Defines the COM interfaces and APIs related to structured data storage.
 *
 * Depends on 'obj_base.h'.
 *
 * Copyright (C) 1999 Paul Quinn
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef __WINE_WINE_OBJ_INPLACE_H
#define __WINE_WINE_OBJ_INPLACE_H

struct tagMSG;

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */

/*****************************************************************************
 * Predeclare the structures
 */
typedef struct  tagOleMenuGroupWidths
{
	LONG width[ 6 ];
} OLEMENUGROUPWIDTHS, *LPOLEMENUGROUPWIDTHS;


typedef struct tagOleInPlaceFrameInfo
{
	UINT cb;
	BOOL fMDIApp;
	HWND hwndFrame;
	HACCEL haccel;
	UINT cAccelEntries;
} OLEINPLACEFRAMEINFO, *LPOLEINPLACEFRAMEINFO;

typedef enum tagOLEGETMONIKER
{
	OLEGETMONIKER_ONLYIFTHERE = 1,
	OLEGETMONIKER_FORCEASSIGN = 2,
	OLEGETMONIKER_UNASSIGN = 3,
	OLEGETMONIKER_TEMPFORUSER = 4
} OLEGETMONIKER;

typedef enum tagOLERENDER
{
	OLERENDER_NONE = 0,
	OLERENDER_DRAW = 1,
	OLERENDER_FORMAT = 2,
	OLERENDER_ASIS = 3
} OLERENDER;

typedef enum tagUSERCLASSTYPE
{
	USERCLASSTYPE_FULL = 1,
	USERCLASSTYPE_SHORT = 2,
	USERCLASSTYPE_APPNAME = 3
} USERCLASSTYPE;

typedef enum tagOLECLOSE
{
	OLECLOSE_SAVEIFDIRTY = 1,
	OLECLOSE_NOSAVE = 2,
	OLECLOSE_PROMPTSAVE = 3
} OLECLOSE;

typedef enum tagOLEUPDATE
{
	OLEUPDATE_ALWAYS = 1,
	OLEUPDATE_ONCALL = 3
} OLEUPDATE, *LPOLEUPDATE;

typedef struct tagOLEVERB
{
	LONG lVerb;
	LPOLESTR lpszVerbName;
	DWORD fuFlags;
	DWORD grfAttribs;
} OLEVERB, *LPOLEVERB;

typedef enum tagOLELINKBIND
{
	OLELINKBIND_EVENIFCLASSDIFF = 1
} OLELINKBIND;

typedef enum tagOLEWHICHMK
{
	OLEWHICHMK_CONTAINER = 1,
	OLEWHICHMK_OBJREL = 2,
	OLEWHICHMK_OBJFULL = 3
} OLEWHICHMK;

typedef enum tagBINDSPEED
{
	BINDSPEED_INDEFINITE = 1,
	BINDSPEED_MODERATE = 2,
	BINDSPEED_IMMEDIATE = 3
} BINDSPEED;

typedef enum tagOLECONTF
{
	OLECONTF_EMBEDDINGS = 1,
	OLECONTF_LINKS = 2,
	OLECONTF_OTHERS = 4,
	OLECONTF_OLNYUSER = 8,
	OLECONTF_ONLYIFRUNNING = 16
} OLECONTF;

typedef HGLOBAL HOLEMENU;
typedef LPRECT LPBORDERWIDTHS;
typedef LPCRECT LPCBORDERWIDTHS;


/*****************************************************************************
 * Predeclare the interfaces
 */
DEFINE_OLEGUID(IID_IOleWindow,  0x00000114L, 0, 0);
typedef struct IOleWindow IOleWindow, *LPOLEWINDOW;

DEFINE_OLEGUID(IID_IOleInPlaceObject,  0x00000113L, 0, 0);
typedef struct IOleInPlaceObject IOleInPlaceObject, *LPOLEINPLACEOBJECT;

DEFINE_OLEGUID(IID_IOleInPlaceActiveObject,  0x00000117L, 0, 0);
typedef struct IOleInPlaceActiveObject IOleInPlaceActiveObject, *LPOLEINPLACEACTIVEOBJECT;

DEFINE_OLEGUID(IID_IOleInPlaceUIWindow,  0x00000115L, 0, 0);
typedef struct IOleInPlaceUIWindow IOleInPlaceUIWindow, *LPOLEINPLACEUIWINDOW;

DEFINE_OLEGUID(IID_IOleInPlaceFrame,  0x00000116L, 0, 0);
typedef struct IOleInPlaceFrame IOleInPlaceFrame, *LPOLEINPLACEFRAME;

DEFINE_OLEGUID(IID_IOleInPlaceSite,  0x00000119L, 0, 0);
typedef struct IOleInPlaceSite IOleInPlaceSite, *LPOLEINPLACESITE;

DEFINE_OLEGUID(IID_IOleClientSite,  0x00000118L, 0, 0);
typedef struct IOleClientSite IOleClientSite, *LPOLECLIENTSITE;

DEFINE_OLEGUID(IID_IOleContainer,  0x0000011bL, 0, 0);
typedef struct IOleContainer IOleContainer, *LPOLECONTAINER;

DEFINE_OLEGUID(IID_IParseDisplayName,  0x0000011aL, 0, 0);
typedef struct IParseDisplayName IParseDisplayName, *LPPARSEDISPLAYNAME;

DEFINE_OLEGUID(IID_IOleItemContainer,  0x0000011cL, 0, 0);
typedef struct IOleItemContainer IOleItemContainer, *LPOLEITEMCONTAINER;

DEFINE_OLEGUID(IID_IOleLink,  0x0000011dL, 0, 0);
typedef struct IOleLink IOleLink, *LPOLELINK;

/*****************************************************************************
 * IOleWindow interface
 */
#define INTERFACE IOleWindow
#define IOleWindow_METHODS \
	IUnknown_METHODS \
	STDMETHOD(GetWindow)(THIS_ HWND *phwnd) PURE; \
	STDMETHOD(ContextSensitiveHelp)(THIS_ BOOL fEnterMode) PURE;
ICOM_DEFINE(IOleWindow,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleWindow_QueryInterface(p,a,b)      (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleWindow_AddRef(p)                  (p)->lpVtbl->AddRef(p)
#define IOleWindow_Release(p)                 (p)->lpVtbl->Release(p)
/*** IOleWindow methods ***/
#define IOleWindow_GetWindow(p,a)             (p)->lpVtbl->GetWindow(p,a)
#define IOleWindow_ContextSensitiveHelp(p,a)  (p)->lpVtbl->ContextSensitiveHelp(p,a)
#endif


/*****************************************************************************
 * IOleInPlaceObject interface
 */
#define INTERFACE IOleInPlaceObject
#define IOleInPlaceObject_METHODS \
	IOleWindow_METHODS \
	STDMETHOD(InPlaceDeactivate)(THIS) PURE; \
	STDMETHOD(UIDeactivate)(THIS) PURE; \
	STDMETHOD(SetObjectRects)(THIS_ LPCRECT lprcPosRect, LPCRECT lprcClipRect) PURE; \
	STDMETHOD(ReactivateAndUndo)(THIS) PURE;
ICOM_DEFINE(IOleInPlaceObject,IOleWindow)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleInPlaceObject_QueryInterface(p,a,b)      (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleInPlaceObject_AddRef(p)                  (p)->lpVtbl->AddRef(p)
#define IOleInPlaceObject_Release(p)                 (p)->lpVtbl->Release(p)
/*** IOleWindow methods ***/
#define IOleInPlaceObject_GetWindow(p,a)             (p)->lpVtbl->GetWindow(p,a)
#define IOleInPlaceObject_ContextSensitiveHelp(p,a)  (p)->lpVtbl->ContextSensitiveHelp(p,a)
/*** IOleInPlaceObject methods ***/
#define IOleInPlaceObject_InPlaceDeactivate(p)       (p)->lpVtbl->InPlaceDeactivate(p)
#define IOleInPlaceObject_UIDeactivate(p)            (p)->lpVtbl->UIDeactivate(p)
#define IOleInPlaceObject_SetObjectRects(p,a,b)      (p)->lpVtbl->SetObjectRects(p,a,b)
#define IOleInPlaceObject_ReactivateAndUndo(p)       (p)->lpVtbl->ReactivateAndUndo(p)
#endif

/*****************************************************************************
 * IOleInPlaceActiveObject interface
 */
#define INTERFACE IOleInPlaceActiveObject
#define IOleInPlaceActiveObject_METHODS \
	IOleWindow_METHODS \
	STDMETHOD(TranslateAccelerator)(THIS_ struct tagMSG *lpmsg) PURE; \
	STDMETHOD(OnFrameWindowActivate)(THIS_ BOOL fActivate) PURE; \
	STDMETHOD(OnDocWindowActivate)(THIS_ BOOL fActivate) PURE; \
	STDMETHOD(ResizeBorder)(THIS_ LPCRECT prcBorder, IOleInPlaceUIWindow *pUIWindow, BOOL fWindowFrame) PURE; \
	STDMETHOD(EnableModeless)(THIS_ BOOL fEnable) PURE;
ICOM_DEFINE(IOleInPlaceActiveObject,IOleWindow)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleInPlaceActiveObject_QueryInterface(p,a,b)      (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleInPlaceActiveObject_AddRef(p)                  (p)->lpVtbl->AddRef(p)
#define IOleInPlaceActiveObject_Release(p)                 (p)->lpVtbl->Release(p)
/*** IOleWindow methods ***/
#define IOleInPlaceActiveObject_GetWindow(p,a)             (p)->lpVtbl->GetWindow(p,a)
#define IOleInPlaceActiveObject_ContextSensitiveHelp(p,a)  (p)->lpVtbl->ContextSensitiveHelp(p,a)
/*** IOleInPlaceActiveObject methods ***/
#define IOleInPlaceActiveObject_TranslateAccelerator(p,a)  (p)->lpVtbl->TranslateAccelerator(p,a)
#define IOleInPlaceActiveObject_OnFrameWindowActivate(p,a) (p)->lpVtbl->OnFrameWindowActivate(p,a)
#define IOleInPlaceActiveObject_OnDocWindowActivate(p,a)   (p)->lpVtbl->OnDocWindowActivate(p,a)
#define IOleInPlaceActiveObject_ResizeBorder(p,a,b,c)      (p)->lpVtbl->ResizeBorder(p,a,b,c)
#define IOleInPlaceActiveObject_EnableModeless(p,a)        (p)->lpVtbl->EnableModeless(p,a)
#endif

/*****************************************************************************
 * IOleInPlaceUIWindow interface
 */
#define INTERFACE IOleInPlaceUIWindow
#define IOleInPlaceUIWindow_METHODS \
	IOleWindow_METHODS \
	STDMETHOD(GetBorder)(THIS_ LPRECT lprectBorder) PURE; \
	STDMETHOD(RequestBorderSpace)(THIS_ LPCBORDERWIDTHS pborderwidths) PURE; \
	STDMETHOD(SetBorderSpace)(THIS_ LPCBORDERWIDTHS pborderwidths) PURE; \
	STDMETHOD(SetActiveObject)(THIS_ IOleInPlaceActiveObject *pActiveObject, LPCOLESTR pszObjName) PURE;
ICOM_DEFINE(IOleInPlaceUIWindow,IOleWindow)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleInPlaceUIWindow_QueryInterface(p,a,b)     (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleInPlaceUIWindow_AddRef(p)                 (p)->lpVtbl->AddRef(p)
#define IOleInPlaceUIWindow_Release(p)                (p)->lpVtbl->Release(p)
/*** IOleWindow methods ***/
#define IOleInPlaceUIWindow_GetWindow(p,a)            (p)->lpVtbl->GetWindow(p,a)
#define IOleInPlaceUIWindow_ContextSensitiveHelp(p,a) (p)->lpVtbl->ContextSensitiveHelp(p,a)
/*** IOleInPlaceUIWindow methods ***/
#define IOleInPlaceUIWindow_GetBorder(p,a)            (p)->lpVtbl->GetBorder(p,a)
#define IOleInPlaceUIWindow_RequestBorderSpace(p,a)   (p)->lpVtbl->RequestBorderSpace(p,a)
#define IOleInPlaceUIWindow_SetBorderSpace(p,a)       (p)->lpVtbl->SetBorderSpace(p,a)
#define IOleInPlaceUIWindow_SetActiveObject(p,a,b)    (p)->lpVtbl->SetActiveObject(p,a,b)
#endif


/*****************************************************************************
 * IOleInPlaceFrame interface
 */
#define INTERFACE IOleInPlaceFrame
#define IOleInPlaceFrame_METHODS \
	IOleInPlaceUIWindow_METHODS \
	STDMETHOD(InsertMenus)(THIS_ HMENU hemnuShared, LPOLEMENUGROUPWIDTHS lpMenuWidths) PURE; \
	STDMETHOD(SetMenu)(THIS_ HMENU hemnuShared, HOLEMENU holemenu, HWND hwndActiveObject) PURE; \
	STDMETHOD(RemoveMenus)(THIS_ HMENU hemnuShared) PURE; \
	STDMETHOD(SetStatusText)(THIS_ LPCOLESTR pszStatusText) PURE; \
	STDMETHOD(EnableModeless)(THIS_ BOOL fEnable) PURE; \
	STDMETHOD(TranslateAccelerator)(THIS_ struct tagMSG *lpmsg, WORD wID) PURE;
ICOM_DEFINE(IOleInPlaceFrame,IOleInPlaceUIWindow)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleInPlaceFrame_QueryInterface(p,a,b)    (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleInPlaceFrame_AddRef(p)                (p)->lpVtbl->AddRef(p)
#define IOleInPlaceFrame_Release(p)               (p)->lpVtbl->Release(p)
/*** IOleWindow methods ***/
#define IOleInPlaceFrame_GetWindow(p,a)           (p)->lpVtbl->GetWindow(p,a)
#define IOleInPlaceFrame_ContextSensitiveHelp(p,a) (p)->lpVtbl->ContextSensitiveHelp(p,a)
/*** IOleInPlaceUIWindow methods ***/
#define IOleInPlaceFrame_GetBorder(p,a)           (p)->lpVtbl->GetBorder(p,a)
#define IOleInPlaceFrame_RequestBorderSpace(p,a)  (p)->lpVtbl->RequestBorderSpace(p,a)
#define IOleInPlaceFrame_SetBorderSpace(p,a)      (p)->lpVtbl->SetBorderSpace(p,a)
#define IOleInPlaceFrame_SetActiveObject(p,a,b)   (p)->lpVtbl->SetActiveObject(p,a,b)
/*** IOleInPlaceFrame methods ***/
#define IOleInPlaceFrame_InsertMenus(p,a,b)       (p)->lpVtbl->InsertMenus(p,a,b)
#define IOleInPlaceFrame_SetMenu(p,a,b,c)         (p)->lpVtbl->SetMenu(p,a,b,c)
#define IOleInPlaceFrame_RemoveMenus(p,a)         (p)->lpVtbl->RemoveMenus(p,a)
#define IOleInPlaceFrame_SetStatusText(p,a)       (p)->lpVtbl->SetStatusText(p,a)
#define IOleInPlaceFrame_EnableModeless(p,a)      (p)->lpVtbl->EnableModeless(p,a)
#define IOleInPlaceFrame_TranslateAccelerator(p,a,b) (p)->lpVtbl->TranslateAccelerator(p,a,b)
#endif


/*****************************************************************************
 * IOleInPlaceSite interface
 */
#define INTERFACE IOleInPlaceSite
#define IOleInPlaceSite_METHODS \
	IOleWindow_METHODS \
	STDMETHOD(CanInPlaceActivate)(THIS) PURE; \
	STDMETHOD(OnInPlaceActivate)(THIS) PURE; \
	STDMETHOD(OnUIActivate)(THIS) PURE; \
	STDMETHOD(GetWindowContext)(THIS_ IOleInPlaceFrame **ppFrame, IOleInPlaceUIWindow **ppDoc, LPRECT lprcPosRect, LPRECT lprcClipRect, LPOLEINPLACEFRAMEINFO lpFrameInfo) PURE; \
	STDMETHOD(Scroll)(THIS_ SIZE scrollExtant) PURE; \
	STDMETHOD(OnUIDeactivate)(THIS_ BOOL fUndoable) PURE; \
	STDMETHOD(OnInPlaceDeactivate)(THIS) PURE; \
	STDMETHOD(DiscardUndoState)(THIS) PURE; \
	STDMETHOD(DeactivateAndUndo)(THIS) PURE; \
	STDMETHOD(OnPosRectChange)(THIS_ LPCRECT lprcPosRect) PURE;
ICOM_DEFINE(IOleInPlaceSite,IOleWindow)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleInPlaceSite_QueryInterface(p,a,b)      (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleInPlaceSite_AddRef(p)                  (p)->lpVtbl->AddRef(p)
#define IOleInPlaceSite_Release(p)                 (p)->lpVtbl->Release(p)
/*** IOleWindow methods ***/
#define IOleInPlaceSite_GetWindow(p,a)             (p)->lpVtbl->GetWindow(p,a)
#define IOleInPlaceSite_ContextSensitiveHelp(p,a)  (p)->lpVtbl->ContextSensitiveHelp(p,a)
/*** IOleInPlaceSite methods ***/
#define IOleInPlaceSite_CanInPlaceActivate(p)      (p)->lpVtbl->CanInPlaceActivate(p)
#define IOleInPlaceSite_OnInPlaceActivate(p)       (p)->lpVtbl->OnInPlaceActivate(p)
#define IOleInPlaceSite_OnUIActivate(p)            (p)->lpVtbl->OnUIActivate(p)
#define IOleInPlaceSite_GetWindowContext(p,a,b,c,d,e) (p)->lpVtbl->GetWindowContext(p,a,b,c,d,e)
#define IOleInPlaceSite_Scroll(p,a)                (p)->lpVtbl->Scroll(p,a)
#define IOleInPlaceSite_OnUIDeactivate(p,a)        (p)->lpVtbl->OnUIDeactivate(p,a)
#define IOleInPlaceSite_OnInPlaceDeactivate(p)     (p)->lpVtbl->OnInPlaceDeactivate(p)
#define IOleInPlaceSite_DiscardUndoState(p)        (p)->lpVtbl->DiscardUndoState(p)
#define IOleInPlaceSite_DeactivateAndUndo(p)       (p)->lpVtbl->DeactivateAndUndo(p)
#define IOleInPlaceSite_OnPosRectChange(p,a)       (p)->lpVtbl->OnPosRectChange(p,a)
#endif


/*****************************************************************************
 * IOleClientSite interface
 */
#define INTERFACE IOleClientSite
#define IOleClientSite_METHODS \
	IUnknown_METHODS \
	STDMETHOD(SaveObject)(THIS) PURE; \
	STDMETHOD(GetMoniker)(THIS_ DWORD dwAssign, DWORD dwWhichMoniker, IMoniker **ppmk) PURE; \
	STDMETHOD(GetContainer)(THIS_ IOleContainer **ppContainer) PURE; \
	STDMETHOD(ShowObject)(THIS) PURE; \
	STDMETHOD(OnShowWindow)(THIS_ BOOL fShow) PURE; \
	STDMETHOD(RequestNewObjectLayout)(THIS) PURE;
ICOM_DEFINE(IOleClientSite,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleClientSite_QueryInterface(p,a,b)      (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleClientSite_AddRef(p)                  (p)->lpVtbl->AddRef(p)
#define IOleClientSite_Release(p)                 (p)->lpVtbl->Release(p)
/*** IOleClientSite methods ***/
#define IOleClientSite_SaveObject(p)              (p)->lpVtbl->SaveObject(p)
#define IOleClientSite_GetMoniker(p,a,b,c)        (p)->lpVtbl->GetMoniker(p,a,b,c)
#define IOleClientSite_GetContainer(p,a)          (p)->lpVtbl->GetContainer(p,a)
#define IOleClientSite_ShowObject(p)              (p)->lpVtbl->ShowObject(p)
#define IOleClientSite_OnShowWindow(p,a)          (p)->lpVtbl->OnShowWindow(p,a)
#define IOleClientSite_RequestNewObjectLayout(p)  ICOM_CALL (RequestNewObjectLayout(p)
#endif


/*****************************************************************************
 * IParseDisplayName interface
 */
#define INTERFACE IParseDisplayName
#define IParseDisplayName_METHODS \
	IUnknown_METHODS \
	STDMETHOD(ParseDisplayName)(THIS_ IBindCtx *pbc, LPOLESTR pszDisplayName, ULONG *pchEaten, IMoniker **ppmkOut) PURE;
ICOM_DEFINE(IParseDisplayName,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IParseDisplayName_QueryInterface(p,a,b)      (p)->lpVtbl->QueryInterface(p,a,b)
#define IParseDisplayName_AddRef(p)                  (p)->lpVtbl->AddRef(p)
#define IParseDisplayName_Release(p)                 (p)->lpVtbl->Release(p)
/*** IParseDisplayName methods ***/
#define IParseDisplayName_ParseDisplayName(p,a,b,c,d) (p)->lpVtbl->ParseDisplayName(p,a,b,c,d)
#endif


/*****************************************************************************
 * IOleContainer interface
 */
#define INTERFACE IOleContainer
#define IOleContainer_METHODS \
	IParseDisplayName_METHODS \
	STDMETHOD(EnumObjects)(THIS_ DWORD grfFlags, IEnumUnknown **ppenum) PURE; \
	STDMETHOD(LockContainer)(THIS_ BOOL fLock) PURE;
ICOM_DEFINE(IOleContainer,IParseDisplayName)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleContainer_QueryInterface(p,a,b)       (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleContainer_AddRef(p)                   (p)->lpVtbl->AddRef(p)
#define IOleContainer_Release(p)                  (p)->lpVtbl->Release(p)
/*** IParseDisplayName methods ***/
#define IOleContainer_ParseDisplayName(p,a,b,c,d) (p)->lpVtbl->ParseDisplayName(p,a,b,c,d)
/*** IOleClientSite methods ***/
#define IOleContainer_EnumObjects(p,a,b)          (p)->lpVtbl->EnumObjects(p,a,b)
#define IOleContainer_LockContainer(p,a)          (p)->lpVtbl->LockContainer(p,a)
#endif


/*****************************************************************************
 * IOleItemContainer interface
 */
#ifdef __WINESRC__
#undef GetObject
#endif

#define INTERFACE IOleItemContainer
#define IOleItemContainer_METHODS \
	IOleContainer_METHODS \
	STDMETHOD(GetObject)(THIS_ LPOLESTR pszItem, DWORD dwSpeedNeeded, IBindCtx *pbc, REFIID riid, void **ppvObject) PURE; \
	STDMETHOD(GetObjectStorage)(THIS_ LPOLESTR pszItem, IBindCtx *pbc, REFIID riid, void **ppvStorage) PURE; \
	STDMETHOD(IsRunning)(THIS_ LPOLESTR pszItem) PURE;
ICOM_DEFINE(IOleItemContainer,IOleContainer)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleItemContainer_QueryInterface(p,a,b)       (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleItemContainer_AddRef(p)                   (p)->lpVtbl->AddRef(p)
#define IOleItemContainer_Release(p)                  (p)->lpVtbl->Release(p)
/*** IParseDisplayName methods ***/
#define IOleItemContainer_GetObject(p,a,b,c,d,e)      (p)->lpVtbl->GetObject(p,a,b,c,d,e)
#define IOleItemContainer_GetObjectStorage(p,a,b,c,d) (p)->lpVtbl->GetObjectStorage(p,a,b,c,d)
#define IOleItemContainer_IsRunning(p,a)              (p)->lpVtbl->IsRunning(p,a)
#endif


/*****************************************************************************
 * IOleItemContainer interface
 */
#define INTERFACE IOleLink
#define IOleLink_METHODS \
	IUnknown_METHODS \
	STDMETHOD(SetUpdateOptions)(THIS_ DWORD dwUpdateOpt) PURE; \
	STDMETHOD(GetUpdateOptions)(THIS_ DWORD *pdwUpdateOpt) PURE; \
	STDMETHOD(SetSourceMoniker)(THIS_ IMoniker *pmk, REFCLSID rclsid) PURE; \
	STDMETHOD(GetSourceMoniker)(THIS_ IMoniker **ppmk) PURE; \
	STDMETHOD(SetSourceDisplayName)(THIS_ LPCOLESTR pszStatusText) PURE; \
	STDMETHOD(GetSourceDisplayName)(THIS_ LPOLESTR *ppszDisplayName) PURE; \
	STDMETHOD(BindToSource)(THIS_ DWORD bindflags, IBindCtx *pbc) PURE; \
	STDMETHOD(BindIfRunning)(THIS) PURE; \
	STDMETHOD(GetBoundSource)(THIS_ IUnknown **ppunk) PURE; \
	STDMETHOD(UnBindSource)(THIS) PURE; \
	STDMETHOD(Update)(THIS_ IBindCtx *pbc) PURE;
ICOM_DEFINE(IOleLink,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleLink_QueryInterface(p,a,b)       (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleLink_AddRef(p)                   (p)->lpVtbl->AddRef(p)
#define IOleLink_Release(p)                  (p)->lpVtbl->Release(p)
/*** IOleLink methods ***/
#define IOleLink_SetUpdateOptions(p,a)       (p)->lpVtbl->SetUpdateOptions(p,a)
#define IOleLink_GetUpdateOptions(p,a)       (p)->lpVtbl->GetUpdateOptions(p,a)
#define IOleLink_SetSourceMoniker(p,a,b)     (p)->lpVtbl->SetSourceMoniker(p,a,b)
#define IOleLink_GetSourceMoniker(p,a)       (p)->lpVtbl->GetSourceMoniker(p,a)
#define IOleLink_SetSourceDisplayName(p,a)   (p)->lpVtbl->SetSourceDisplayName(p,a)
#define IOleLink_GetSourceDisplayName(p,a)   (p)->lpVtbl->GetSourceDisplayName(p,a)
#define IOleLink_BindToSource(p,a,b)         (p)->lpVtbl->BindToSource(p,a,b)
#define IOleLink_BindIfRunning(p)            (p)->lpVtbl->BindIfRunning(p)
#define IOleLink_GetBoundSource(p,a)         (p)->lpVtbl->GetBoundSource(p,a)
#define IOleLink_UnBindSource(p)             (p)->lpVtbl->UnBindSource(p)
#define IOleLink_Update(p,a)                 (p)->lpVtbl->Update(p,a)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif /* defined(__cplusplus) */

#endif /* __WINE_WINE_OBJ_INPLACE_H */
