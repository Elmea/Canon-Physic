#include "UI.h"
#include "Canon.h"

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

void UI::CanonParameters(Core::Canon* canon)
{
    if (ImGui::TreeNodeEx("Canon parameters "))
    {
        SliderDouble("Height##Canon", &canon->position.y, 100, 1000);
        SliderDouble("Strength##Canon", &canon->power, 0.001, 1000);
        SliderDouble("Shoot direction##Canon", &canon->angle, -45, 45);

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

