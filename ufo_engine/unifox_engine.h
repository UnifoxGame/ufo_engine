#pragma once

#include <d2d1.h>
#include <d2d1helper.h>
#include <d3d11.h>
#include <dwrite.h>
#include <wincodec.h>

#include <vector>
#include <string>
#include <mutex>

#include "singleton.h"

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "dwrite.lib")

namespace ufo
{
	template <class T>
	class window : public pattern::singleton<window<T>>
	{
		HWND m_Hwnd;
		HINSTANCE m_Hinstance;
		WNDCLASS m_WndClass;
		std::function<void()> m_EventsFunc;
		std::function<void(T*)> m_UpdateFunc;
		std::function<void(T const &)> m_RenderFunc;
		std::function<T(T const &, T const &, float)> m_InterpolateFunc;
		T m_CurrentState, m_PreviousState;
		class d2d : public singleton<d2d>
		{
			bool isInitialized;
			std::unique_ptr<ID2D1Factory>			m_Direct2dFactory;
			std::unique_ptr<ID2D1HwndRenderTarget>	m_RenderTarget;

			std::unique_ptr<IWICImagingFactory>		m_ImagingFactory;
			std::unique_ptr<IWICBitmapDecoder>		m_BitmapDecoder;

			std::unique_ptr<IDWriteFactory>			m_DWriteFactory;
			std::unique_ptr<IDWriteTextFormat>		m_TextFormat;
			std::unique_ptr<IDWriteTextLayout>		m_TextLayout;
		private:
			friend class pattern::singleton<d2d>;
			d2d() : isInitialized(false) {}
			d2d(const d2d&) = delete;
			d2d(d2d&&) = delete;
			d2d& operator=(const d2d&) = delete;
			d2d& operator=(d2d&&) = delete;
		public:
			~d2d() = default;
			operator bool() { return isInitialized; }

			void Initialize();

			ID2D1Factory* Direct2DFactory() { return m_Direct2DFactory.get(); }
			ID2D1HwndRenderTarget* RenderTarget() { return m_RenderTarget.get(); }
			IWICImagingFactory* ImagingFactory() { return m_ImagingFactory.get(); }
			IWICBitmapDecoder* BitmapDecoder() { return m_BitmapDecoder.get(); }
			IDWriteFactory* DWriteFactory() { return m_DWriteFactory.get(); }
			IDWriteTextFormat* TextFormat() { return m_TextFormat.get(); }
			IDWriteTextLayout* TextLayout() { return m_TextLayout.get(); }
		};
		class d3d : public singleton<d3d>
		{
			bool isInitialized;
		private:
			friend class pattern::singleton<d3d>;
			d3d() : isInitialized(false) {}
			d3d(const d3d&) = delete;
			d3d(d3d&&) = delete;
			d3d& operator=(const d3d&) = delete;
			d3d& operator=(d3d&&) = delete;
		public:
			~d3d() = default;
			operator bool() { return isInitialized; }

			void Initialize();
		};
	private:
		friend class pattern::singleton<window>;
		window() = default;
		window(const window&) = delete;
		window(window&&) = delete;
		window operator=(const window&) = delete;
		window operator=(window&&) = delete;
	public:
		~window() = default;
		void SetWindow(HINSTANCE, WNDPROC, std::wstring, RECT, DWORD = WS_OVERLAPPEDWINDOW,
			HICON = LoadIcon(NULL, IDI_APPLICATION), HCURSOR = LoadCursor(NULL, IDC_ARROW), 
			HBRUSH = (HBRUSH)GetStockObject(BLACK_BRUSH));
		void Initialize2D();
		void Initialize3D();
		int Run();
	};
	template<class T>
	void window<T>::d2d::Initialize()
	{
		isInitialized = true;
	}
	template<class T>
	void window<T>::d3d::Initialize()
	{
		isInitialized = true;
	}
	template<class T>
	void window<T>::SetWindow(HINSTANCE hInstance, WNDPROC WndProc, std::wstring WndName,
		RECT WndSize, DWORD WndStyle, HICON hIcon, HCURSOR hCursor, HBRUSH hBrush)
	{
		m_WndClass.cbWndExtra = 0;
		m_WndClass.cbClsExtra = 0;
		m_WndClass.hbrBackground = hBrush;
		m_WndClass.hCursor = hCursor;
		m_WndClass.hIcon = hIcon;
		m_WndClass.hInstance = hInstance;
		m_WndClass.lpfnWndProc = WndProc;
		m_WndClass.lpszClassName = WndName.data();
		m_WndClass.lpszMenuName = WndName.data();
		m_WndClass.style = CS_VREDRAW | CS_HREDRAW;
		RegisterClass(&m_WndClass);


	}
	template<class T> void window<T>::Initialize2D() 
	{
		if (!(d2d::Instance() || d3d::Instance()))
			d2d::Instance().Initialize(); 
	}
	template<class T> void window<T>::Initialize3D() 
	{
		if (!(d2d::Instance() || d3d::Instance()))
			d3d::Instance().Initialize(); 
	}
	template<class T> 
	int window<T>::Run()
	{
		try
		{
			if (!(d2d::Instance() || d3d::Instance()))
				throw std::wstring(L"Initialize Error");
			
		}
		catch (std::wstring exp)
		{
			MessageBox(0, exp.data(), 0, MB_OK);
			PostQuitMessage(0);
		}
		return 0;
	}
}