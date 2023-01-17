#include "UI.h"

bool UI::SliderDouble(const char* text, double* v, double min, double max)
{
    return ImGui::SliderScalar(text, ImGuiDataType_Double, v, &min, &max);
}

bool UI::SliderDoubleN(const char* text, int nbValues, double* v, double min, double max)
{
    return ImGui::SliderScalarN(text, ImGuiDataType_Double, v, nbValues, &min, &max);
}

bool UI::ClickInRectangle(Vector2 mousePos, Rectangle rec)
{
    if (mousePos.x > rec.x && mousePos.x < (rec.x + rec.width))
        return true;
    else if (mousePos.y > rec.y && mousePos.y < (rec.y + rec.height))
        return true;
    
    return false;
}

void UI::Init()
{
    rlImGuiSetup(true);
    cannon = LoadTexture("assets/Cannon.png");
    cannonBase = LoadTexture("assets/Cannonbase.png");
}

UI::~UI()
{
}

void UI::NewFrame() 
{
    rlImGuiBegin();
}

void UI::EndFrame()
{
    rlImGuiEnd();
}

void UI::NewWindow(const char* windowName)
{
    ImGui::Begin(windowName);
}

void UI::CloseWindow()
{
    ImGui::End();
}

void UI::ProjectileParameters()
{

    if (ImGui::TreeNodeEx("Projectile parameters "))
    {
        if (SliderDouble("Weight##Projectile", &weight, 0.0001, 1000))
        {

        }

        if (SliderDouble("Size##Projectile", &sizeP, 1, 10))
        {

        }
        ImGui::TreePop();

    }
}

void UI::CanonParameters()
{
    /*Temporary values waiting for canon class */
    static double power = 5;


    if (ImGui::TreeNodeEx("Canon parameters "))
    {
        ImGui::SliderInt("Height##Canon", &height, 300, 1000);
        SliderDouble("Strength##Canon", &power, 0.001, 1000);
        SliderDouble("Shoot direction##Canon", &angle, -45, 45);

        ImGui::TreePop();
    }
}

void UI::WorldParameters(WorldParam& world)
{
    if (ImGui::TreeNodeEx("World config"))
    {
        SliderDouble("Gravity", &world.gravity, -1, 50);
        SliderDouble("Air Resistance", &world.airResistance, 0, 10);

        ImGui::TreePop();
    }
}

void UI::MoveCannon()
{
    //Vector2 mousePos = GetMousePosition();
    //if (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && ClickInRectangle(mousePos, destRec))
    //{

    //}
}

void UI::DrawCanon()
{
    int frameWidth = cannon.width;
    int frameHeight = cannon.height;

    // Source rectangle (part of the texture to use for drawing)
    Rectangle sourceRec = { 0.0f, 0.0f, (float)frameWidth, (float)frameHeight };
    // Destination rectangle (screen rectangle where drawing part of texture)
    Rectangle newDestRec = { 200, height, frameWidth , frameHeight  };
    destRec = newDestRec;

    // Origin of the texture (rotation/scale point), it's relative to destination rectangle size
    Vector2 origin = { (float)frameWidth/2, (float)frameHeight/2 };

    /* Draw cannon and it's base */
    DrawTexturePro(cannon, sourceRec, destRec, origin, angle, WHITE);
    DrawTexture(cannonBase, destRec.x - frameWidth/2 + 25, destRec.y, WHITE);

    /* Draw support of the cannon */
    DrawRectangle(destRec.x - frameWidth / 2 , height + cannonBase.height, frameWidth, 1080, BLACK);
}
