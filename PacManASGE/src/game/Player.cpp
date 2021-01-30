#include "Player.hpp"

Player::Player() {}
Player::~Player() {}

bool Player::init(ASGE::Renderer* renderer)
{
  player[0].addSpriteComponent(renderer, "data/images/Male adventurer/PNG/Poses HD/character_maleAdventurer_idle.png");
  for (int i = 1; i < 3; ++i)
  {
    player[i].addSpriteComponent(renderer, "data/images/Male adventurer/PNG/Poses HD/character_maleAdventurer_run" + std::to_string(i-1) + ".png");
  }
  for (const auto & i : player)
  {
    i.getSpriteComponent()->getSprite()->xPos(200);
    i.getSpriteComponent()->getSprite()->yPos(300);
  }
  //anim_sprite_counter = 0;
  return false;
}

void Player::keyHandler() {}
void Player::update() {}

void Player::render(ASGE::Renderer* renderer)
{
    renderer->renderSprite(*player[0/*anim_sprite_counter*/].getSpriteComponent()->getSprite());
}
