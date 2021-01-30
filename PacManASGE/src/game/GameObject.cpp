#include "GameObject.hpp"
#include <cmath>

bool GameObject::addSpriteComponent(ASGE::Renderer* rend, const std::string& filepath)
{
  sprite_component = std::make_unique<SpriteComponent>();
  if (sprite_component->loadSprite(rend, filepath))
  {
    return true;
  }
  return false;
}

const std::unique_ptr<SpriteComponent>& GameObject::getSpriteComponent() const
{
  return sprite_component;
}

const Vector2& GameObject::getVector() const
{
  return vector;
}

void GameObject::setVector(const Vector2& vector_var)
{
  GameObject::vector = vector_var;
}

bool GameObject::isVisible() const
{
  return is_visible;
}
void GameObject::setIsVisible(bool isVisible)
{
  is_visible = isVisible;
}

bool GameObject::isOccupied() const
{
  return is_occupied;
}

void GameObject::setOccupied(bool occupation)
{
  is_occupied = occupation;
}
