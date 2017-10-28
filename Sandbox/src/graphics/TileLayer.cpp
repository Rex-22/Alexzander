#include "TileLayer.h"
#include "glm/gtc/matrix_transform.inl"

TileLayer::TileLayer(al::graphics::Shader* shader) 
	:Layer2D(new al::graphics::BatchRenderer2D(), shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{}

TileLayer::TileLayer(al::graphics::Renderer2D* renderer, al::graphics::Shader* shader)
	: Layer2D(renderer, shader, glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{}
