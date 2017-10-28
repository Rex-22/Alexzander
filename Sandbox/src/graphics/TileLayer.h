#pragma once

#include <Alex.h>

class TileLayer : public al::graphics::Layer2D
{
public:
	TileLayer(al::graphics::Shader* shader);
	TileLayer(al::graphics::Renderer2D* renderer, al::graphics::Shader* shader);
};