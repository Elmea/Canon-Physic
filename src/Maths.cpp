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

Float2 Float2::operator+(Float2& other)
{
    Float2 result;
    result.x = x + other.x;
    result.y = y + other.y;
    return result;
}

Float2 Float2::operator*(double& multiplicator)
{
    return { x * multiplicator, y * multiplicator };
}

Float2 Float2::operator-(Float2& other)
{
    return { x - other.x, y - other.y };
}

Float2 Float2::operator/(double divider)
{
    Float2 result;
    result.x = x / divider;
    result.y = y / divider;
    return result;
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