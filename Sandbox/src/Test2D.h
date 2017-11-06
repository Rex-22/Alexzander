#pragma once

#include <Alex.h>

class Test2D : public al::graphics::Layer2D
{
private:
	al::graphics::Label* m_FPS;

	al::graphics::Group* g;

	float gain = 0.5f;
public:
	Test2D();
	~Test2D() {}

	void OnInit(al::graphics::Renderer2D& renderer) override;
	void OnRender(al::graphics::Renderer2D& renderer) override;

	void OnEvent(al::events::Event& event) override;

	bool OnKeyPressedEvent(al::events::KeyPressedEvent& event);
	bool OnMouseMovedEvent(al::events::MouseMovedEvent& event);
};