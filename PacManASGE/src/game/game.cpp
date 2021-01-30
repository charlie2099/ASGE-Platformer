#include <string>
#include "game.h"
#include <Engine/Logger.hpp>
#include <Engine/Sprite.h>

ASGEGame::ASGEGame(ASGE::GameSettings settings) : OGLGame(settings)
{
  renderer->setClearColour(ASGE::COLOURS::SLATEGRAY);
  inputs->use_threads = false;
  toggleFPS();
  initCamera();
  logStartup();
}

void ASGEGame::initCamera()
{
  // create a camera to frame the window
  /*camera = ASGE::Camera2D{ static_cast<float>(ASGE::SETTINGS.window_width),
                           static_cast<float>(ASGE::SETTINGS.window_height) };*/

  camera = ASGE::Camera2D{ static_cast<float>(ASGE::SETTINGS.window_width),
                           static_cast<float>(ASGE::SETTINGS.window_height) };
}

void ASGEGame::logStartup() const
{
  std::ostringstream ss{ "initialisation complete" };
  Logging::ERRORS(ss.str());
  Logging::WARN(ss.str());
  Logging::INFO(ss.str());
  Logging::DEBUG(ss.str());
  Logging::TRACE(ss.str());
  Logging::log(Logging::timestamp() + " \x1b[35;1m[CUSTOM]\x1b[0m " + ss.str() + '\n');
}

ASGEGame::~ASGEGame()
{
  this->inputs->unregisterCallback(static_cast<unsigned int>(key_callback_id));
  this->inputs->unregisterCallback(static_cast<unsigned int>(mouse_callback_id));
}

bool ASGEGame::init()
{
  key_callback_id =
    inputs->addCallbackFnc(ASGE::E_KEY, &ASGEGame::keyHandler, this);
  mouse_callback_id =
    inputs->addCallbackFnc(ASGE::E_MOUSE_CLICK, &ASGEGame::clickHandler, this);

  //object.printThis(4);
  //object.printThis("hello");

  //player1.init(renderer.get());

  anim_sprite[0].addSpriteComponent(renderer.get(), "data/images/Male adventurer/PNG/Poses HD/character_maleAdventurer_idle.png");
  for (int i = 1; i < 3; ++i)
  {
    anim_sprite[i].addSpriteComponent(renderer.get(), "data/images/Male adventurer/PNG/Poses HD/character_maleAdventurer_run" + std::to_string(i-1) + ".png");
  }
  for (const auto & i : anim_sprite)
  {
    i.getSpriteComponent()->getSprite()->xPos(10);
    i.getSpriteComponent()->getSprite()->yPos(300);
  }
  anim_sprite_counter = 0;

  terrain.addSpriteComponent(renderer.get(), "data/images/cube.png");
  terrain.getSpriteComponent()->getSprite()->xPos(0);
  terrain.getSpriteComponent()->getSprite()->yPos(anim_sprite->getSpriteComponent()->getSprite()->yPos() + anim_sprite->getSpriteComponent()->getSprite()->height());
  terrain.getSpriteComponent()->getSprite()->width(ASGE::SETTINGS.window_width);
  terrain.getSpriteComponent()->getSprite()->height(100);
  terrain.getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::LIMEGREEN);

  tree.addSpriteComponent(renderer.get(), "data/images/cube.png");
  tree.getSpriteComponent()->getSprite()->xPos(1250);
  tree.getSpriteComponent()->getSprite()->yPos(200);
  tree.getSpriteComponent()->getSprite()->width(100);
  tree.getSpriteComponent()->getSprite()->height(300);
  tree.getSpriteComponent()->getSprite()->colour(ASGE::COLOURS::BROWN);

  return true;
}

void ASGEGame::keyHandler(const ASGE::SharedEventData& data)
{
  const auto* key = dynamic_cast<const ASGE::KeyEvent*>(data.get());

  if(key->key == ASGE::KEYS::KEY_LEFT && key->action == 1)
  {
    player.state = Skeleton::State::LEFT;
    anim_sprite[1].getSpriteComponent()->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
    anim_sprite[2].getSpriteComponent()->getSprite()->setFlipFlags(ASGE::Sprite::FLIP_X);
  }

  if(key->key == ASGE::KEYS::KEY_RIGHT && key->action == 1)
  {
    player.state = Skeleton::State::RIGHT;
    anim_sprite[1].getSpriteComponent()->getSprite()->setFlipFlags(static_cast<ASGE::Sprite::FlipFlags>(anim_sprite[1].getSpriteComponent()->getSprite()->flipFlags() * 2));
    anim_sprite[2].getSpriteComponent()->getSprite()->setFlipFlags(static_cast<ASGE::Sprite::FlipFlags>(anim_sprite[2].getSpriteComponent()->getSprite()->flipFlags() * 2));
  }

  if(key->action == 0)
  {
    player.state = Skeleton::State::IDLE;
  }

  if (key->key == ASGE::KEYS::KEY_ESCAPE)
  {
    signalExit();
  }
}

void ASGEGame::clickHandler(const ASGE::SharedEventData& data)
{
  const auto* click = dynamic_cast<const ASGE::ClickEvent*>(data.get());

  double x_pos = click->xpos;
  double y_pos = click->ypos;

  Logging::TRACE("x_pos: " + std::to_string(x_pos));
  Logging::TRACE("y_pos: " + std::to_string(y_pos));
}

void ASGEGame::update(const ASGE::GameTime& game_time)
{
  //auto dt_sec = game_time.delta.count() / 1000.0;
  auto dt_sec = game_time.deltaInSecs();

  if (inputs->getGamePad(0).is_connected)
  {
    camera.translateX(inputs->getGamePad(0).axis[0] * -100);
    camera.translateY(inputs->getGamePad(0).axis[1] * -100);
  }
  camera.update(game_time);

  for (int i = 0; i < 3; ++i)
  {
    camera.lookAt(ASGE::Point2D{ -anim_sprite[i].getSpriteComponent()->getSprite()->xPos() - 100,static_cast<float>(-ASGE::SETTINGS.window_height) / 2.f });
  }
  //camera.setZoom(camera.getZoom() - 0.001F);

  std::cout << anim_sprite_counter << std::endl;

  /// Move into player class?
  if(player.state == Skeleton::State::IDLE)
  {
    anim_sprite_counter = 0;
  }

  if(player.state == Skeleton::State::LEFT)
  {
    for (const auto & i : anim_sprite)
    {
      i.getSpriteComponent()->getSprite()->xPos(i.getSpriteComponent()->getSprite()->xPos() - 500 * dt_sec);
    }
  }

  if(player.state == Skeleton::State::RIGHT)
  {
    for (const auto & i : anim_sprite)
    {
      i.getSpriteComponent()->getSprite()->xPos(i.getSpriteComponent()->getSprite()->xPos() + 500 * dt_sec);
    }
  }

  /// Clock
  //auto elapsed_sec = game_time.elapsed.count() / 1000;
  //std::cout << "Time Elapsed: " << elapsed_sec << std::endl;

  /// Walking animation
  if(player.state != Skeleton::State::IDLE)
  {
    auto current_time = std::chrono::steady_clock::now();
    // Switched out seconds to milliseconds so can cycle through frames faster!
    if (duration_cast<std::chrono::milliseconds>(current_time - previous_time).count() >= 100)
    {
      anim_sprite_counter++;
      previous_time = current_time;
    }
  }

  if(anim_sprite_counter == 3)
  {
    anim_sprite_counter = 1;
  }
}

void ASGEGame::render()
{
  renderer->setFont(0);
  renderer->setProjectionMatrix(camera.getView());
  if (gameState == GameState::MENU)
  {
    renderer->renderSprite(*anim_sprite[anim_sprite_counter].getSpriteComponent()->getSprite());
    renderer->renderSprite(*terrain.getSpriteComponent()->getSprite());
    renderer->renderSprite(*tree.getSpriteComponent()->getSprite());
    //player1.render(renderer.get()); 
  }
}
