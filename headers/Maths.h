#pragma once

#define PI 3.14159265f
#define DEG2RAD PI/180.0f
#define RAD2DEG 180/PI

#include <string>
#include "raylib.h"


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

    Float2 operator+(const Float2& other) const;
    Float2 operator-(const Float2& other) const;
    Float2 operator*(const double& multiplicator)const ;
    Float2 operator/(const double& divider)const ;
    operator Vector2()const;

    bool operator==(Float2& other) { return (x == other.x) && (y == other.y); }

    double Magnitude();

    void Normalize();
    Float2 GetNormalized();

    std::string ToString();

    static Float2 LineIntersection(const Float2& origin1, const Float2& dir1, const Float2& origin2, const Float2& dir2);
    
};
