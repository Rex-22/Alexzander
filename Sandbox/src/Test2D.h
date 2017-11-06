#pragma once

#include <Alex.h>

class Test2D : public al::graphics::Layer2D
{
private:
	al::graphics::Label* m_FPS;

	float gain = 0.5f;
public:
	Test2D();
	~Test2D() {}

	void OnInit() override;

	void OnEvent(al::events::Event& event) override;

	bool OnKeyPressedEvent(al::events::KeyPressedEvent& event);
	bool OnMouseMovedEvent(al::events::MouseMovedEvent& event);
};