#include "SpriteComponent.hpp"
#include <Engine/Renderer.h>

bool SpriteComponent::loadSprite(ASGE::Renderer* renderer, const std::string& filepath)
{
  sprite_ptr = renderer->createUniqueSprite();
  return sprite_ptr->loadTexture(filepath);
}

std::unique_ptr<ASGE::Sprite>& SpriteComponent::getSprite()
{
  return sprite_ptr;
}

bool SpriteComponent::spriteCollision(
  const ASGE::Sprite* spr1, const ASGE::Sprite* spr2)
{
  return spr1->xPos() < spr2->xPos() + spr2->width() &&
         spr1->xPos() + spr1->width() > spr2->xPos() &&
         spr1->yPos() < spr2->yPos() + spr2->height() &&
         spr1->yPos() + spr1->height() > spr2->yPos();
}

// new collision
bool SpriteComponent::circleCollision(
  float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
{
  // get distance between the circle's centers
  // use the Pythagorean Theorem to compute the distance
  float distX    = c1x - c2x;
  float distY    = c1y - c2y;
  float distance = sqrt((distX * distX) + (distY * distY));

  // if the distance is less than the sum of the circle's
  // radii, the circles are touching!
  if (distance <= c1r + c2r)
  {
    return true;
  }
  return false;
}