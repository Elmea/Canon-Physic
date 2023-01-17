#pragma once

#define PI 3.14159265f
#define DEG2RAD PI/180.0f
#define RAD2DEG 180/PI

#include <string>

class Float2
{
public:
    union
    {
        struct
        {
            double x;
            double y;
        };

        float coord[2];
    };

    double CrossProduct2D(Float2 other) const;

    double DotProduct(const Float2* other) const;

    void PlanRotation(double angle);

    Float2 operator+(Float2& other);
    Float2 operator-(Float2& other);
    Float2 operator*(double& multiplicator);
    Float2 operator/(double divider);

    bool operator==(Float2& other) { return (x == other.x) && (y == other.y); }

    double Magnitude();

    void Normalize();
    Float2 GetNormalized();

    std::string ToString();
};
