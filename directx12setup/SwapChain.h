#pragma once
#include <d3d11.h>

class DeviceContext;
class SwapChain
{
public:
	SwapChain();
	~SwapChain();
	bool init(HWND hnd, UINT width, UINT height);
	bool release();
	bool present(bool vsync);
private:
	IDXGISwapChain* m_swap_chain;
	ID3D11RenderTargetView* m_rtv;
	ID3D11DepthStencilView* m_dsv;
	friend class DeviceContext;
};

