#pragma once
#include "GameObject.hpp"
#include "Player.hpp"
#include <Engine/Camera2D.hpp>
#include <Engine/OGLGame.h>
#include <chrono>
#include <string>

class ASGEGame final: public ASGE::OGLGame
{
 public:
  explicit ASGEGame(ASGE::GameSettings settings);
  ~ASGEGame() override;
  bool init();
  void clickHandler(const ASGE::SharedEventData& data);
  void initCamera();
  void keyHandler(const ASGE::SharedEventData& data);
  void logStartup() const;
  void render() override;
  void update(const ASGE::GameTime&) override;

 private:
  std::chrono::time_point<std::chrono::steady_clock> previous_time = std::chrono::steady_clock::now();
  int key_callback_id   = -1;
  int mouse_callback_id = -1;
  int anim_sprite_counter = 0;

  struct Skeleton
  {
    /// Move inside player class / GameObject class?
    enum class State
    {
      IDLE,
      LEFT,
      RIGHT,
      JUMPING
    } state = State::IDLE;
  } player;

  enum class GameState {MENU, GAME} gameState = GameState::MENU;

  ASGE::Camera2D camera{};
  Player player1;
  GameObject object, anim_sprite[3], terrain, tree;
};