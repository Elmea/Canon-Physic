#include "UI.h"
#include "Canon.h"
#include <iostream>

bool UI::SliderDouble(const char* text, double* v, double min, double max)
{
    return ImGui::SliderScalar(text, ImGuiDataType_Double, v, &min, &max);
}

bool UI::SliderDoubleN(const char* text, int nbValues, double* v, double min, double max)
{
    return ImGui::SliderScalarN(text, ImGuiDataType_Double, v, nbValues, &min, &max);
}

bool UI::ClickInRectangle(Float2 mousePos, Rectangle rec)
{
    return  (mousePos.x > rec.x && mousePos.x < (double)(rec.x + rec.width )) &&
            (mousePos.y > rec.y && mousePos.y < (double)(rec.y + rec.height));
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
        SliderDouble("Height##Canon", &canon->position.y, minHeightCanon, maxHeightCanon);
        SliderDouble("Strength##Canon", &canon->power, 0.001, 1000);
        SliderDouble("Shoot direction##Canon", &canon->angle, -45, 45);
        SliderDouble("Speed Drag", &speedDrag, 0.01, 100);
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

void UI::Shoot(Core::Canon* canon, Renderer::RendererManager& objectManager)
{
    if (ImGui::Button("Shoot", ImVec2(150,75)))
    {
        canon->Shoot(sizeP,weight);
        std::cout << " shoot" << std::endl;
    }
}

void UI::MoveCannon(Core::Canon* canon)
{
    Float2 mousePos = {GetMouseX(),  GetMouseY()};

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        if (lastMousePos.x != -100 && lastMousePos.y != -100)
        {
            Float2 delta = mousePos - lastMousePos;

            if (ClickInRectangle(mousePos, { 0,0,(float)canon->position.x + 200 , 1080 }))
            {
                canon->position.y += delta.y * speedDrag;
                if (canon->position.y < minHeightCanon)
                    canon->position.y = minHeightCanon;
                if (canon->position.y > maxHeightCanon)
                    canon->position.y = maxHeightCanon;
            }
        }

        lastMousePos = mousePos;
    }
    else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        Float2 delta = mousePos - lastMousePos;

        if (ClickInRectangle(mousePos, { (float)(canon->position.x - 200.f) ,(float)(canon->position.y - 200), (float)(canon->position.x + canon->size.x + 200) , (float)(canon->position.y + canon->size.y + 200) }))
        {
            canon->angle += delta.x * speedDrag;
            if (canon->angle < minAngleCanon)
                canon->angle = minAngleCanon;
            if (canon->angle > maxAngleCanon)
                canon->angle = maxAngleCanon;
        }
        lastMousePos = mousePos;
    }
    else
    {
        lastMousePos = { -100,-100 };
    }
}

