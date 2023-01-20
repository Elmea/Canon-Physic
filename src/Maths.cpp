#include "Maths.h"
#include <math.h>


double Float2::CrossProduct2D(Float2 other) const
{
    return this->x * other.y - this->y * other.x;
}

double Float2::DotProduct(const Float2* other) const
{
    return (this->x * other->x) + (this->y * other->y);
}

void Float2::PlanRotation(double angle)
{
    float tmpx = this->x;
    this->x = this->x * cos(angle) - this->y * sin(angle);
    this->y = tmpx * sin(angle) + this->y * cos(angle);
}

void Float2::operator+=(const Float2& other)
{
    x += other.x;
    y += other.y;
}

void Float2::operator-=(const Float2& other)
{
    x -= other.x;
    y -= other.y;
}

void Float2::operator*=(const Float2& other)
{
    x *= other.x;
    y *= other.y;
}

void Float2::operator/=(const Float2& other)
{
    x /= other.x;
    y /= other.y;
}

Float2 Float2::operator+(const Float2& other) const
{
    Float2 result;
    result.x = x + other.x;
    result.y = y + other.y;
    return result;
}

Float2 Float2::operator*(const double& multiplicator) const
{
    return { x * multiplicator, y * multiplicator };
}

Float2 Float2::operator-(const Float2& other) const
{
    return { x - other.x, y - other.y };
}

Float2 Float2::operator/(const double& divider)const
{
    Float2 result;
    result.x = x / divider;
    result.y = y / divider;
    return result;
}

Float2::operator Vector2() const
{
    Vector2 v;
    v.x = (float)this->x;
    v.y = (float)this->y;
    return v;
}

double Float2::Magnitude()
{
    return sqrt(x * x + y * y);
}

void Float2::Normalize()
{
    double mag = Magnitude();

    x = x / mag;
    y = y / mag;
}

Float2 Float2::GetNormalized()
{
    double mag = Magnitude();

    return { x / mag, y / mag };
}

std::string Float2::ToString()
{
    std::string result;

    result = "(" + std::to_string(x) + " , " + std::to_string(y) + ")";

    return result;
}

Float2 Float2::LineIntersection(const Float2& origin1, const Float2& dir1, const Float2& origin2, const Float2& dir2)
{
    const Float2 diff = origin2 - origin1;
    const float cross = dir1.CrossProduct2D(dir2);
    const float coeff = diff.CrossProduct2D(dir2) / cross;
    return origin1 + dir1 * coeff;
}
