/* write your class interface in this file
   write function definitions only if they are very short
 */

class Vector2D {
 private:
  double x;
  double y;

 public:
  // Define default constructor (no arguments)
  Vector2D() : x(0), y(0){};
  // Define a constructor that takes 2 arguments representing x and y
  Vector2D(double a, double b) : x(a), y(b){};
  void initVector(double x_init, double y_init);
  double getMagnitude() const;
  Vector2D operator+(const Vector2D & rhs) const {
    Vector2D new_vec;
    new_vec.initVector(x, y);
    new_vec.x += rhs.x;
    new_vec.y += rhs.y;
    return new_vec;
  }
  Vector2D & operator+=(const Vector2D & rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  double dot(const Vector2D & rhs) const;
  void print() const;
};
