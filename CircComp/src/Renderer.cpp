#include "Renderer.h"

void Renderer::OnResize(uint32_t w, uint32_t h)
{
	if (m_FinalImage)
	{
		if (w == m_FinalImage->GetWidth() || h == m_FinalImage->GetHeight())
			return;
		m_FinalImage->Resize(w, h);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(w, h, Walnut::ImageFormat::RGBA);
	}
	delete[] m_ImageData;
	m_ImageData = new uint32_t[w * h];
}

void Renderer::Render()
{
	for (uint32_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (uint32_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			glm::vec2 coord = { (float)x / m_FinalImage->GetWidth(), (float)y / m_FinalImage->GetHeight() };
			m_ImageData[x + y * m_FinalImage->GetWidth()] = PixelShader(coord);
		}
	}

	m_FinalImage->SetData(m_ImageData);
}

uint32_t Renderer::PixelShader(glm::vec2 coord)
{
	uint8_t r = (uint8_t)(coord.x * 255.0f);
	uint8_t g = (uint8_t)(coord.y * 255.0f);
	uint8_t b = (uint8_t)(sin(std::time(0)));

	//ABGR format
	return 0xff000000 | (g<<10) | r;
}
