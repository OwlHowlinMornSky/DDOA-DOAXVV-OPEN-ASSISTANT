#include "Capture.h"

#include <opencv2/opencv.hpp>
#include "Saver.h"
//#include "../Window/macro.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Capture;

namespace {

inline bool CreateCaptureItemForWindow(winrt::Windows::Graphics::Capture::GraphicsCaptureItem& item, HWND hwnd) {
	auto activation_factory = winrt::get_activation_factory<winrt::Windows::Graphics::Capture::GraphicsCaptureItem>();
	auto interop_factory = activation_factory.as<IGraphicsCaptureItemInterop>();
	const auto res = interop_factory->CreateForWindow(hwnd, winrt::guid_of<ABI::Windows::Graphics::Capture::IGraphicsCaptureItem>(), winrt::put_abi(item));
	if (res != S_OK)
		return false;
	return true;
}

inline auto CreateD3DDevice(
	D3D_DRIVER_TYPE const type,
	winrt::com_ptr<ID3D11Device>& device) {
	WINRT_ASSERT(!device);

	UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT;

	return D3D11CreateDevice(
		nullptr,
		type,
		nullptr,
		flags,
		nullptr, 0,
		D3D11_SDK_VERSION,
		device.put(),
		nullptr,
		nullptr);
}

inline auto CreateD3DDevice() {
	winrt::com_ptr<ID3D11Device> device;
	HRESULT hr = CreateD3DDevice(D3D_DRIVER_TYPE_HARDWARE, device);

	if (DXGI_ERROR_UNSUPPORTED == hr) {
		hr = CreateD3DDevice(D3D_DRIVER_TYPE_WARP, device);
	}

	winrt::check_hresult(hr);
	return device;
}

extern "C" {
	HRESULT __stdcall CreateDirect3D11DeviceFromDXGIDevice(::IDXGIDevice* dxgiDevice,
														   ::IInspectable** graphicsDevice);
}

inline auto CreateDirect3DDevice(IDXGIDevice* dxgi_device) {
	winrt::com_ptr<::IInspectable> d3d_device;
	winrt::check_hresult(CreateDirect3D11DeviceFromDXGIDevice(dxgi_device, d3d_device.put()));
	return d3d_device.as<winrt::Windows::Graphics::DirectX::Direct3D11::IDirect3DDevice>();
}

} // namespace 

namespace ohms::capture::wgc {

Capture::Capture() :
	m_device(nullptr),
	m_capture(nullptr) {}

void Capture::Initialize() {
	com_ptr<ID3D11Device> d3dDevice = CreateD3DDevice();
	com_ptr<IDXGIDevice> dxgiDevice = d3dDevice.as<IDXGIDevice>();
	m_device = CreateDirect3DDevice(dxgiDevice.get());
}

bool Capture::StartCapture(HWND hwnd) {
	Stop();

	GraphicsCaptureItem item = { nullptr };

	if (!CreateCaptureItemForWindow(item, hwnd)) {
		return false;
	}

	m_capture = std::make_unique<CaptureCore>(m_device, item, hwnd);

	m_capture->StartCapture();
	return true;
}

void Capture::Stop() {
	if (m_capture) {
		m_capture->Close();
		m_capture.reset();
	}
}

void Capture::setNeedRefresh() {
	if (m_capture != nullptr)
		m_capture->setNeedRefresh();
}

/*void Capture::setDecimationMode(bool val) {
	if (m_capture != nullptr)
		m_capture->setDecimationMode(val);
}*/

void Capture::setClipClientArea(bool val) {
	if (m_capture != nullptr)
		m_capture->setClipClientArea(val);
}

/*void Capture::setShowScale(int val) {
	if (m_capture != nullptr)
		m_capture->setShowScale(val * 10);
}*/

bool Capture::saveNow(bool C3, size_t id) {
	if (m_capture) {
		return ohms::Saver::instance().save(m_capture->getCapMat(), static_cast<unsigned long long>(time(0)), C3, id);
	}
	return false;
}

const cv::Mat* Capture::getCapMat() {
	if (m_capture == nullptr)
		return nullptr;
	return &m_capture->getCapMat();
}

bool Capture::getUpdated() {
	if (m_capture) {
		return m_capture->getUpdated();
	}
	return false;
}

} // namespace ohms::capture::wgc
