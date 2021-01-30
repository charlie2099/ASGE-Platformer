#ifndef HELLOASGE_SPRITECOMPONENT_HPP
#define HELLOASGE_SPRITECOMPONENT_HPP
#include <Engine/Sprite.h>
#include <vector>

class SpriteComponent
{
 public:
  SpriteComponent() = default;
  ~SpriteComponent() = default;

  bool loadSprite(ASGE::Renderer* renderer, const std::string& texture_file_name);
  std::unique_ptr<ASGE::Sprite>& getSprite();

  /// Collision
  bool spriteCollision(const ASGE::Sprite* spr1, const ASGE::Sprite* spr2);
  bool circleCollision(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r);

 private:
  std::unique_ptr<ASGE::Sprite> sprite_ptr = nullptr;
};

#endif // HELLOASGE_SPRITECOMPONENT_HPP
