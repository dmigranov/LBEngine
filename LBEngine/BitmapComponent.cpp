#include "pch.h"
#include "BitmapComponent.h"

#include "MeshComponent.h"

BitmapComponent::BitmapComponent(unsigned int width, unsigned int height, bool isOpaque)
{
	m_quad = new MeshComponent(4, nullptr, 6, nullptr); 	//todo
	m_bitmapWidth = width;
	m_bitmapHeight = height;
	m_spriteSheet = nullptr;
	m_isOpaque = isOpaque;
}

BitmapComponent::BitmapComponent(unsigned int width, unsigned int height, Texture* texture, bool isOpaque) : BitmapComponent(width, height)
{
	SetTexture(texture);
}

BitmapComponent::~BitmapComponent()
{
	delete m_quad;
}

void BitmapComponent::SetFrameIndex(unsigned int frameIndex)
{
	m_frameIndex = frameIndex;
}

void BitmapComponent::SetTexture(Texture* texture)
{
	m_spriteSheet = texture;
	m_texWidth = texture->GetWidth();
	m_texWidth = texture->GetHeight();
}

bool BitmapComponent::IsOpaque()
{
	return m_isOpaque;
}