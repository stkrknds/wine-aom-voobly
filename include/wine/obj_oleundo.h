/*
 * Defines the COM interfaces and APIs from ocidl.h which pertain to Undo/Redo
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

#ifndef __WINE_WINE_OBJ_OLEUNDO_H
#define __WINE_WINE_OBJ_OLEUNDO_H

#ifdef __cplusplus
extern "C" {
#endif /* defined(__cplusplus) */

/*****************************************************************************
 * Predeclare the interfaces
 */
DEFINE_GUID(IID_IQuickActivate, 0xcf51ed10, 0x62fe, 0x11cf, 0xbf, 0x86, 0x00, 0xa0, 0xc9, 0x03, 0x48, 0x36);
typedef struct IQuickActivate IQuickActivate,*LPQUICKACTIVATE;

DEFINE_GUID(IID_IPointerInactive, 0x55980ba0, 0x35aa, 0x11cf, 0xb6, 0x71, 0x00, 0xaa, 0x00, 0x4c, 0xd6, 0xd8);
typedef struct IPointerInactive IPointerInactive,*LPPOINTERINACTIVE;

DEFINE_GUID(IID_IAdviseSinkEx, 0x3af24290, 0x0c96, 0x11ce, 0xa0, 0xcf, 0x00, 0xaa, 0x00, 0x60, 0x0a, 0xb8);
typedef struct IAdviseSinkEx IAdviseSinkEx,*LPADVISESINKEX;

DEFINE_GUID(IID_IOleUndoManager, 0xd001f200, 0xef97, 0x11ce, 0x9b, 0xc9, 0x00, 0xaa, 0x00, 0x60, 0x8e, 0x01);
typedef struct IOleUndoManager IOleUndoManager,*LPOLEUNDOMANAGER;

DEFINE_GUID(IID_IOleUndoUnit, 0x894ad3b0, 0xef97, 0x11ce, 0x9b, 0xc9, 0x00, 0xaa, 0x00, 0x60, 0x8e, 0x01);
typedef struct IOleUndoUnit IOleUndoUnit,*LPOLEUNDOUNIT;

DEFINE_GUID(IID_IOleParentUndoUnit, 0xa1faf330, 0xef97, 0x11ce, 0x9b, 0xc9, 0x00, 0xaa, 0x00, 0x60, 0x8e, 0x01);
typedef struct IOleParentUndoUnit IOleParentUndoUnit,*LPOLEPARENTUNDOUNIT;

DEFINE_GUID(IID_IEnumOleUndoUnits, 0xb3e7c340, 0xef97, 0x11ce, 0x9b, 0xc9, 0x00, 0xaa, 0x00, 0x60, 0x8e, 0x01);
typedef struct IEnumOleUndoUnits IEnumOleUndoUnits,*LPENUMOLEUNDOUNITS;

/*****************************************************************************
 * Declare the structures
 */
typedef enum tagQACONTAINERFLAGS
{
	QACONTAINER_SHOWHATCHING = 0x1,
	QACONTAINER_SHOWGRABHANDLES = 0x2,
	QACONTAINER_USERMODE = 0x4,
	QACONTAINER_DISPLAYASDEFAULT = 0x8,
	QACONTAINER_UIDEAD = 0x10,
	QACONTAINER_AUTOCLIP = 0x20,
	QACONTAINER_MESSAGEREFLECT = 0x40,
	QACONTAINER_SUPPORTSMNEMONICS = 0x80
} QACONTAINERFLAGS;

typedef DWORD OLE_COLOR;

typedef struct tagQACONTROL
{
	ULONG cbSize;
	DWORD dwMiscStatus;
	DWORD dwViewStatus;
	DWORD dwEventCookie;
	DWORD dwPropNotifyCookie;
	DWORD dwPointerActivationPolicy;
} QACONTROL;

typedef struct tagQACONTAINER
{
	ULONG cbSize;
	IOleClientSite *pClientSite;
	IAdviseSinkEx *pAdviseSink;
	IPropertyNotifySink *pPropertyNotifySink;
	IUnknown *pUnkEventSink;
	DWORD dwAmbientFlags;
	OLE_COLOR colorFore;
	OLE_COLOR colorBack;
	IFont *pFont;
	IOleUndoManager *pUndoMgr;
	DWORD dwAppearance;
	LONG lcid;
	HPALETTE hpal;
	struct IBindHost *pBindHost;
} QACONTAINER;

/*****************************************************************************
 * IQuickActivate interface
 */
#define INTERFACE IQuickActivate
#define IQuickActivate_METHODS \
	STDMETHOD(QuickActivate)(THIS_ QACONTAINER *pQaContainer, QACONTROL *pQaControl) PURE; \
	STDMETHOD(SetContentExtent)(THIS_ LPSIZEL pSizel) PURE; \
	STDMETHOD(GetContentExtent)(THIS_ LPSIZEL pSizel) PURE;
#define IQuickActivate_IMETHODS \
	IUnknown_IMETHODS \
	IQuickActivate_METHODS
ICOM_DEFINE(IQuickActivate,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IQuickActivate_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IQuickActivate_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IQuickActivate_Release(p)            (p)->lpVtbl->Release(p)
/*** IQuickActivate methods ***/
#define IQuickActivate_QuickActivate(p,a,b)  (p)->lpVtbl->QuickActivate(p,a,b)
#define IQuickActivate_SetContentExtent(p,a) (p)->lpVtbl->SetContentExtent(p,a)
#define IQuickActivate_GetContentExtent(p,a) (p)->lpVtbl->GetContentExtent(p,a)
#endif


/*****************************************************************************
 * IPointerInactive interface
 */
#define INTERFACE IPointerInactive
#define IPointerInactive_METHODS \
	STDMETHOD(GetActivationPolicy)(THIS_ DWORD *pdwPolicy) PURE; \
	STDMETHOD(OnInactiveMouseMove)(THIS_ LPCRECT pRectBounds, LONG x, LONG y, DWORD grfKeyState) PURE; \
	STDMETHOD(OnInactiveSetCursor)(THIS_ LPCRECT pRectBounds, LONG x, LONG y, DWORD dwMouseMsg, BOOL fSetAlways) PURE;
#define IPointerInactive_IMETHODS \
	IUnknown_IMETHODS \
	IPointerInactive_METHODS
ICOM_DEFINE(IPointerInactive,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IPointerInactive_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IPointerInactive_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IPointerInactive_Release(p)            (p)->lpVtbl->Release(p)
/*** IPointerInactive methods ***/
#define IPointerInactive_GetActivationPolicy(p,a)         (p)->lpVtbl->GetActivationPolicy(p,a)
#define IPointerInactive_OnInactiveMoveMouse(p,a,b,c,d)   (p)->lpVtbl->OnInactiveMoveMouse(p,a,b,c,d)
#define IPointerInactive_OnInactiveSetCursor(p,a,b,c,d,e) (p)->lpVtbl->OnInactiveSetCursor(p,a,b,d,e)
#endif


/*****************************************************************************
 * IAdviseSinkEx interface
 */
#define INTERFACE IAdviseSinkEx
#define IAdviseSinkEx_METHODS \
	STDMETHOD(OnViewStatusChange)(THIS_ DWORD dwViewStatus) PURE;
#define IAdviseSinkEx_IMETHODS \
	IAdviseSink_IMETHODS \
	IAdviseSinkEx_METHODS
ICOM_DEFINE(IAdviseSinkEx,IAdviseSink)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IAdviseSinkEx_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IAdviseSinkEx_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IAdviseSinkEx_Release(p)            (p)->lpVtbl->Release(p)
/*** IAdviseSink methods ***/
#define IAdviseSinkEx_OnDataChange(p,a,b)   (p)->lpVtbl->OnDataChange(p,a,b)
#define IAdviseSinkEx_OnViewChange(p,a,b)   (p)->lpVtbl->OnViewChange(p,a,b)
#define IAdviseSinkEx_OnRename(p,a)         (p)->lpVtbl->OnRename(p,a)
#define IAdviseSinkEx_OnSave(p)             (p)->lpVtbl->OnSave(p)
#define IAdviseSinkEx_OnClose(p)            (p)->lpVtbl->OnClose(p)
/*** IAdviseSinkEx methods ***/
#define IAdviseSinkEx_OnViewStatusChange(p,a)  (p)->lpVtbl->OnViewStatusChange(p,a)
#endif


/*****************************************************************************
 * IOleUndoManager interface
 */
#define INTERFACE IOleUndoManager
#define IOleUndoManager_METHODS \
	STDMETHOD(Open)(THIS_ IOleParentUndoUnit *pPUU) PURE; \
	STDMETHOD(Close)(THIS_ IOleParentUndoUnit *pPUU, BOOL fCommit) PURE; \
	STDMETHOD(Add)(THIS_ IOleUndoUnit *pUU) PURE; \
	STDMETHOD(GetOpenParentState)(THIS_ DWORD *pdwState) PURE; \
	STDMETHOD(DiscardFrom)(THIS_ IOleUndoUnit *pUU) PURE; \
	STDMETHOD(UndoTo)(THIS_ IOleUndoUnit *pUU) PURE; \
	STDMETHOD(RedoTo)(THIS_ IOleUndoUnit *pUU) PURE; \
	STDMETHOD(EnumUndoable)(THIS_ IEnumOleUndoUnits **ppEnum) PURE; \
	STDMETHOD(EnumRedoable)(THIS_ IEnumOleUndoUnits **ppEnum) PURE; \
	STDMETHOD(GetLastUndoDescription)(THIS_ BSTR *pBstr) PURE; \
	STDMETHOD(GetLastRedoDescription)(THIS_ BSTR *pBstr) PURE; \
	STDMETHOD(Enable)(THIS_ BOOL fEnable) PURE;
#define IOleUndoManager_IMETHODS \
	IUnknown_IMETHODS \
	IOleUndoManager_METHODS
ICOM_DEFINE(IOleUndoManager,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleUndoManager_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleUndoManager_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IOleUndoManager_Release(p)            (p)->lpVtbl->Release(p)
/*** IOleUndoManager methods ***/
#define IOleUndoManager_Open(p,a)                   (p)->lpVtbl->Open(p,a)
#define IOleUndoManager_Close(p,a,b)                (p)->lpVtbl->Close(p,a,b)
#define IOleUndoManager_Add(p,a)                    (p)->lpVtbl->Add(p,a)
#define IOleUndoManager_GetOpenParentState(p,a)     (p)->lpVtbl->GetOpenParentState(p,a)
#define IOleUndoManager_DiscardFrom(p,a)            (p)->lpVtbl->DiscardFrom(p,a)
#define IOleUndoManager_UndoTo(p,a)                 (p)->lpVtbl->UndoTo(p,a)
#define IOleUndoManager_RedoTo(p,a)                 (p)->lpVtbl->RedoTo(p,a)
#define IOleUndoManager_EnumUndoable(p,a)           (p)->lpVtbl->EnumUndoable(p,a)
#define IOleUndoManager_EnumRedoable(p,a)           (p)->lpVtbl->EnumRedoable(p,a)
#define IOleUndoManager_GetLastUndoDescription(p,a) (p)->lpVtbl->GetLastUndoDescription(p,a)
#define IOleUndoManager_GetLastRedoDescription(p,a) (p)->lpVtbl->GetLastRedoDescription(p,a)
#define IOleUndoManager_Enable(p,a)                 (p)->lpVtbl->Enable(p,a)
#endif


/*****************************************************************************
 * IOleUndoUnit interface
 */
#define INTERFACE IOleUndoUnit
#define IOleUndoUnit_METHODS \
	STDMETHOD(Do)(THIS_ IOleUndoManager *pUndoManager) PURE; \
	STDMETHOD(GetDescription)(THIS_ BSTR *pBstr) PURE; \
	STDMETHOD(GetUnitType)(THIS_ CLSID *pClsid, LONG *plID) PURE; \
	STDMETHOD(OnNextAdd)(THIS) PURE;
#define IOleUndoUnit_IMETHODS \
	IUnknown_IMETHODS \
	IOleUndoUnit_METHODS
ICOM_DEFINE(IOleUndoUnit,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleUndoUnit_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleUndoUnit_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IOleUndoUnit_Release(p)            (p)->lpVtbl->Release(p)
/*** IOleUndoUnit methods ***/
#define IOleUndoUnit_Do(p,a)               (p)->lpVtbl->Do(p,a)
#define IOleUndoUnit_GetDescription(p,a)   (p)->lpVtbl->GetDescription(p,a)
#define IOleUndoUnit_GetUnitType(p,a,b)    (p)->lpVtbl->GetUnitType(p,a,b)
#define IOleUndoUnit_OnNextAdd(p)          (p)->lpVtbl->OnNextAdd(p)
#endif



/*****************************************************************************
 * IOleUndoUnit interface
 */
#define INTERFACE IOleParentUndoUnit
#define IOleParentUndoUnit_METHODS \
	STDMETHOD(Open)(THIS_ IOleParentUndoUnit *pPUU) PURE; \
	STDMETHOD(Close)(THIS_ IOleParentUndoUnit *pPUU, BOOL fCommit) PURE; \
	STDMETHOD(Add)(THIS_ IOleUndoUnit *pUU) PURE; \
	STDMETHOD(FindUnit)(THIS_ IOleUndoUnit *pUU) PURE; \
	STDMETHOD(GetParentState)(THIS_ DWORD *pdwState) PURE;
#define IOleParentUndoUnit_IMETHODS \
	IOleUndoUnit_IMETHODS \
	IOleParentUndoUnit_METHODS
ICOM_DEFINE(IOleParentUndoUnit,IOleUndoUnit)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IOleParentUndoUnit_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IOleParentUndoUnit_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IOleParentUndoUnit_Release(p)            (p)->lpVtbl->Release(p)
/*** IOleUndoUnit methods ***/
#define IOleParentUndoUnit_Do(p,a)               (p)->lpVtbl->Do(p,a)
#define IOleParentUndoUnit_GetDescription(p,a)   (p)->lpVtbl->GetDescription(p,a)
#define IOleParentUndoUnit_GetUnitType(p,a,b)    (p)->lpVtbl->GetUnitType(p,a,b)
#define IOleParentUndoUnit_OnNextAdd(p)          (p)->lpVtbl->OnNextAdd(p)
/*** IOleParentUndoUnit methods ***/
#define IOleParentUndoUnit_Open(p,a)             (p)->lpVtbl->Open(p,a)
#define IOleParentUndoUnit_Close(p,a,b)          (p)->lpVtbl->Close(p,a,b)
#define IOleParentUndoUnit_Add(p,a)              (p)->lpVtbl->Add(p,a)
#define IOleParentUndoUnit_FindUnit(p,a)         (p)->lpVtbl->FindUnit(p,a)
#define IOleParentUndoUnit_GetParentState(p,a,b) (p)->lpVtbl->GetParentState(p,a)
#endif


/*****************************************************************************
 * IEnumOleUndoUnits interface
 */
#define INTERFACE IEnumOleUndoUnits
#define IEnumOleUndoUnits_METHODS \
	STDMETHOD(Next)(THIS_ ULONG cElt, IOleUndoUnit **rgElt, ULONG *pcEltFetched) PURE; \
	STDMETHOD(Skip)(THIS_ ULONG cElt) PURE; \
	STDMETHOD(Reset)(THIS) PURE; \
	STDMETHOD(Clone)(THIS_ IEnumOleUndoUnits **ppEnum) PURE;
#define IEnumOleUndoUnits_IMETHODS \
	IUnknown_IMETHODS \
	IEnumOleUndoUnits_METHODS
ICOM_DEFINE(IEnumOleUndoUnits,IUnknown)
#undef INTERFACE

#ifdef COBJMACROS
/*** IUnknown methods ***/
#define IEnumOleUndoUnits_QueryInterface(p,a,b) (p)->lpVtbl->QueryInterface(p,a,b)
#define IEnumOleUndoUnits_AddRef(p)             (p)->lpVtbl->AddRef(p)
#define IEnumOleUndoUnits_Release(p)            (p)->lpVtbl->Release(p)
/*** IEnumOleUndoUnits methods ***/
#define IEnumOleUndoUnits_Next(p,a,b,c)         (p)->lpVtbl->Next(p,a,b,c)
#define IEnumOleUndoUnits_Skip(p,a)             (p)->lpVtbl->Skip(p,a)
#define IEnumOleUndoUnits_Reset(p,a)            (p)->lpVtbl->Reset(p,a)
#define IEnumOleUndoUnits_Clone(p,a)            (p)->lpVtbl->Clone(p,a)
#endif

#ifdef __cplusplus
} /* extern "C" */
#endif /* defined(__cplusplus) */

#endif /* __WINE_WINE_OBJ_OLEUNDO_H */
