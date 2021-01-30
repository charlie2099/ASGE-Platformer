#ifndef HELLOASGE_PLAYER_HPP
#define HELLOASGE_PLAYER_HPP
#include "GameObject.hpp"

class Player
{
 public:
  Player();
  ~Player();

  enum class State
  {
    IDLE,
    LEFT,
    RIGHT,
    JUMPING
  } state = State::IDLE;

  bool init(ASGE::Renderer* renderer);
  void keyHandler();
  void update();
  void render(ASGE::Renderer* renderer);
 private:
  GameObject player[3];
};

#endif // HELLOASGE_PLAYER_HPP
