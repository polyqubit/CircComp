#pragma once

#include <memory>
#include <iostream>

#include "Walnut/Image.h"
#include "Walnut/Random.h"

class Renderer
{
public:
	Renderer() = default;

	void OnResize(uint32_t w, uint32_t h);
	void Render();

	std::shared_ptr<Walnut::Image> GetFinalImage() const { return m_FinalImage; }
private:
	uint32_t PixelShader(glm::vec2 coord);

	std::shared_ptr<Walnut::Image> m_FinalImage;
	uint32_t* m_ImageData = nullptr;
};

