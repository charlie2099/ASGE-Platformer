#ifndef HELLOASGE_VECTOR2_HPP
#define HELLOASGE_VECTOR2_HPP

struct Vector2
{
  // construction
  Vector2() = default;
  Vector2(float x_, float y_);
  Vector2(const Vector2& rhs);

  // operations
  Vector2 operator*(float scalar);
  Vector2& operator=(const Vector2& rhs);
  void normalise();

  // data
  float x = 0;
  float y = 0;
};

#endif // HELLOASGE_VECTOR2_HPP
