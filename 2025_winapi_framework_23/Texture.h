#pragma once
#include "ResourceBase.h"
class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture();
public:
	LONG GetWidth() const { return m_bitInfo.bmWidth; }
	LONG GetHeight() const { return m_bitInfo.bmHeight; }
	const HDC& GetTextureDC() const { return m_hDC; }
	const HBITMAP& GetHBitmap() const { 
		return m_hBit; 
	}
public:
	virtual void Load(const wstring& _filePath);
private:
	HBITMAP m_hBit;
	HDC     m_hDC;
	BITMAP  m_bitInfo;
};

