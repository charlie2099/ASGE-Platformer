#ifndef HELLOASGE_GAMEOBJECT_HPP
#define HELLOASGE_GAMEOBJECT_HPP
#include "SpriteComponent.hpp"
#include "Vector2.hpp"
#include <Engine/Renderer.h>
#include <Engine/Sprite.h>
#include <iostream>
#include <string>
#include <vector>

class GameObject
{
 public:
  GameObject()  = default;
  ~GameObject() = default;

  template<typename Temp>
  void printThis(Temp data)
  {
    std::cout << data << std::endl;
  }

  /// Visibility and Occupation
  [[nodiscard]] bool isVisible() const;
  void setIsVisible(bool isVisible);
  [[nodiscard]] bool isOccupied() const;
  void setOccupied(bool occupation);

  /// Vectors
  [[nodiscard]] const Vector2& getVector() const;
  void setVector(const Vector2& vector_var);

  /// Components
  bool addSpriteComponent(ASGE::Renderer* rend, const std::string& filepath);
  [[nodiscard]] const std::unique_ptr<SpriteComponent>& getSpriteComponent() const;

 private:
  std::unique_ptr<SpriteComponent> sprite_component = nullptr;
  Vector2 vector                    = { 0, 0 };
  bool is_occupied    = false;
  bool is_visible     = true;
};

#endif // HELLOASGE_GAMEOBJECT_HPP
