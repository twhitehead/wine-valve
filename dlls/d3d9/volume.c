/*
 * IDirect3DVolume9 implementation
 *
 * Copyright 2002-2005 Jason Edmeades
 *                     Raphael Junqueira
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

#include "config.h"
#include "d3d9_private.h"

WINE_DEFAULT_DEBUG_CHANNEL(d3d);

/* IDirect3DVolume9 IUnknown parts follow: */
HRESULT WINAPI IDirect3DVolume9Impl_QueryInterface(LPDIRECT3DVOLUME9 iface, REFIID riid, LPVOID* ppobj) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;

    if (IsEqualGUID(riid, &IID_IUnknown)
        || IsEqualGUID(riid, &IID_IDirect3DVolume9)) {
        IDirect3DVolume9Impl_AddRef(iface);
        *ppobj = This;
        return D3D_OK;
    }

    WARN("(%p)->(%s,%p),not found\n", This, debugstr_guid(riid), ppobj);
    return E_NOINTERFACE;
}

ULONG WINAPI IDirect3DVolume9Impl_AddRef(LPDIRECT3DVOLUME9 iface) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    TRACE("(%p) : AddRef from %ld\n", This, This->ref);
    return InterlockedIncrement(&This->ref);
}

ULONG WINAPI IDirect3DVolume9Impl_Release(LPDIRECT3DVOLUME9 iface) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    ULONG ref = InterlockedDecrement(&This->ref);
    TRACE("(%p) : ReleaseRef to %ld\n", This, This->ref);
    if (ref == 0) {
        IWineD3DVolume_Release(This->wineD3DVolume);
        HeapFree(GetProcessHeap(), 0, This);
    }
    return ref;
}

/* IDirect3DVolume9 Interface follow: */
HRESULT WINAPI IDirect3DVolume9Impl_GetDevice(LPDIRECT3DVOLUME9 iface, IDirect3DDevice9** ppDevice) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    IWineD3DDevice       *myDevice = NULL;

    IWineD3DVolume_GetDevice(This->wineD3DVolume, &myDevice);
    IWineD3DDevice_GetParent(myDevice, (IUnknown **)ppDevice);
    IWineD3DDevice_Release(myDevice);
    return D3D_OK;
}

HRESULT WINAPI IDirect3DVolume9Impl_SetPrivateData(LPDIRECT3DVOLUME9 iface, REFGUID refguid, CONST void* pData, DWORD SizeOfData, DWORD Flags) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    return IWineD3DVolume_SetPrivateData(This->wineD3DVolume, refguid, pData, SizeOfData, Flags);
}

HRESULT WINAPI IDirect3DVolume9Impl_GetPrivateData(LPDIRECT3DVOLUME9 iface, REFGUID  refguid, void* pData, DWORD* pSizeOfData) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    return IWineD3DVolume_GetPrivateData(This->wineD3DVolume, refguid, pData, pSizeOfData);
}

HRESULT WINAPI IDirect3DVolume9Impl_FreePrivateData(LPDIRECT3DVOLUME9 iface, REFGUID refguid) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    return IWineD3DVolume_FreePrivateData(This->wineD3DVolume, refguid);
}

HRESULT WINAPI IDirect3DVolume9Impl_GetContainer(LPDIRECT3DVOLUME9 iface, REFIID riid, void** ppContainer) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    HRESULT res;

    IUnknown *IWineContainer = NULL;
    res = IWineD3DVolume_GetContainer(This->wineD3DVolume, riid, (void **)&IWineContainer);

    /* If this works, the only valid container is a child of resource (volumetexture) */
    if (res == D3D_OK) {
        IWineD3DResource_GetParent((IWineD3DResource *)IWineContainer, (IUnknown **)ppContainer);
        IWineD3DResource_Release((IWineD3DResource *)IWineContainer);
    }

    return res;
}

HRESULT WINAPI IDirect3DVolume9Impl_GetDesc(LPDIRECT3DVOLUME9 iface, D3DVOLUME_DESC* pDesc) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    WINED3DVOLUME_DESC     wined3ddesc;
    UINT                   tmpInt = -1;

    /* As d3d8 and d3d9 structures differ, pass in ptrs to where data needs to go */
    wined3ddesc.Format              = &pDesc->Format;
    wined3ddesc.Type                = &pDesc->Type;
    wined3ddesc.Usage               = &pDesc->Usage;
    wined3ddesc.Pool                = &pDesc->Pool;
    wined3ddesc.Size                = &tmpInt;
    wined3ddesc.Width               = &pDesc->Width;
    wined3ddesc.Height              = &pDesc->Height;
    wined3ddesc.Depth               = &pDesc->Depth;

    return IWineD3DVolume_GetDesc(This->wineD3DVolume, &wined3ddesc);
}

HRESULT WINAPI IDirect3DVolume9Impl_LockBox(LPDIRECT3DVOLUME9 iface, D3DLOCKED_BOX* pLockedVolume, CONST D3DBOX* pBox, DWORD Flags) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    return IWineD3DVolume_LockBox(This->wineD3DVolume, pLockedVolume, pBox, Flags);
}

HRESULT WINAPI IDirect3DVolume9Impl_UnlockBox(LPDIRECT3DVOLUME9 iface) {
    IDirect3DVolume9Impl *This = (IDirect3DVolume9Impl *)iface;
    return IWineD3DVolume_UnlockBox(This->wineD3DVolume);
}

IDirect3DVolume9Vtbl Direct3DVolume9_Vtbl =
{
    IDirect3DVolume9Impl_QueryInterface,
    IDirect3DVolume9Impl_AddRef,
    IDirect3DVolume9Impl_Release,
    IDirect3DVolume9Impl_GetDevice,
    IDirect3DVolume9Impl_SetPrivateData,
    IDirect3DVolume9Impl_GetPrivateData,
    IDirect3DVolume9Impl_FreePrivateData,
    IDirect3DVolume9Impl_GetContainer,
    IDirect3DVolume9Impl_GetDesc,
    IDirect3DVolume9Impl_LockBox,
    IDirect3DVolume9Impl_UnlockBox
};

/* Internal function called back during the CreateVolumeTexture */
HRESULT WINAPI D3D9CB_CreateVolume(IUnknown  *pDevice, UINT Width, UINT Height, UINT Depth, 
                                   D3DFORMAT  Format, D3DPOOL Pool, DWORD Usage,
                                   IWineD3DVolume **ppVolume, 
                                   HANDLE   * pSharedHandle) {
    IDirect3DVolume9Impl *object;
    IDirect3DDevice9Impl *This = (IDirect3DDevice9Impl *)pDevice;
    
    /* Allocate the storage for the device */
    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDirect3DVolume9Impl));
    object->lpVtbl = &Direct3DVolume9_Vtbl;
    object->ref = 1;
    return IWineD3DDevice_CreateVolume(This->WineD3DDevice, Width, Height, Depth, Usage, Format, 
                                       Pool, ppVolume, pSharedHandle, (IUnknown *)object);
}
