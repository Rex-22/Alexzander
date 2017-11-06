#pragma once

/*
* APP
*/
#include <al/app/Application.h>
#include <al/app/Window.h>

/*
* AUDIO
*/
#include <al/audio/AudioEngine.h>
#include <al/audio/Sound.h>

/*
 *ENTITY
 */
#include <al/entity/Entity.h>
#include <al/entity/component/Component.h>
#include <al/entity/component/SpriteComponent.h>
#include <al/entity/component/TransformComponent.h>

/*
 * EVENTS
 */
#include <al/events/Event.h>
#include <al/events/EventDispatcher.h>
#include <al/events/KeyEvent.h>
#include <al/events/MouseEvent.h>

/*
 * GRAPHICS
 */
#include <al/graphics/Shader.h>
#include <al/graphics/TextureManager.h>
#include <al/graphics/Texture.h>
#include <al/graphics/Font.h>
#include <al/graphics/FontManager.h>

#include <al/graphics/renderer/IRenderer.h>
#include <al/graphics/renderer/Renderer2D.h>

#include <al/graphics/renderables/IRenderable.h>
#include <al/graphics/renderables/Renderable2D.h>
#include <al/graphics/renderables/Sprite.h>

#include <al/graphics/layers/Layer.h>
#include <al/graphics/layers/Layer2D.h>
#include <al/graphics/layers/Group.h>

#include <al/graphics/ui/Label.h>

/*
 * SCENE
 */
#include <al/scene/Scene2D.h>
#include <al/scene/Scene.h>

 /*
 * UTILS
 */
#include <al/utils/FileUtils.h>
#include <al/utils/Timer.h>
#include <al/utils/Log.h>
#include <al/utils/Timestep.h>
#include <al/utils/ImageUtils.h>

#include <al/Common.h>
#include <al/Types.h>