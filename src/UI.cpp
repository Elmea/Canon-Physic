#include "UI.h"
#include "Canon.h"
#include <iostream>

double UI::length = 0;
double UI::height = 0;
double UI::timeAir = 0;

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

    if (ImGui::TreeNodeEx("Projectile parameters ", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (SliderDouble("Weight##Projectile", &weight, 0.0001, 1000))
        {

        }

        if (SliderDouble("Size##Projectile", &sizeP, 4, 50))
        {

        }
        ImGui::TreePop();

    }
}

void UI::CanonParameters(Core::Canon* canon)
{
    if (ImGui::TreeNodeEx("Canon parameters ", ImGuiTreeNodeFlags_DefaultOpen))
    {
        SliderDouble("Height##Canon", &canon->position.y, minHeightCanon, maxHeightCanon);
        SliderDouble("Strength##Canon", &canon->power, 15 *(10.0/ Data::WorldSetting::pixelPerMeter), 900 * (10.0 / Data::WorldSetting::pixelPerMeter));
        SliderDouble("Shoot direction##Canon", &canon->angle, minAngleCanon, maxAngleCanon);
        SliderDouble("Speed Drag", &speedDrag, 0.01, 100);
        ImGui::TreePop();
    }
}

void UI::WorldParameters()
{
    if (ImGui::TreeNodeEx("World config",ImGuiTreeNodeFlags_DefaultOpen ))
    {
        SliderDouble("Gravity", &Data::WorldSetting::GRAVITY, -1, 50);
        SliderDouble("Air Resistance", &Data::WorldSetting::airResistance, 0.0001, 10);
        SliderDouble("Air Viscosity", &Data::WorldSetting::airViscosity, 0, 10);
        SliderDouble("Size Repere", &Data::WorldSetting::pixelPerMeter, 0.0001f, 10);

        ImGui::TreePop();
    }
}

void UI::Shoot(Core::Canon* canon, Renderer::RendererManager& objectManager)
{
    if (ImGui::Button("Shoot", ImVec2(150,75)))
        canon->Shoot(sizeP,weight);
}

void UI::ShowValuesBeforeShoot(Core::Canon* canon)
{
    NewWindow("Pre calculated values");
    Float2 vZero = { canon->power * cos(canon->angle), canon->power * sin(canon->angle) };
    double maxW = (2 * vZero.x * (-vZero.y)) / Data::WorldSetting::GRAVITY;
    double maxH = (vZero.y * vZero.y) / (2 * Data::WorldSetting::GRAVITY);
    double timeInAir = (2 * (-vZero.y)) / Data::WorldSetting::GRAVITY;

    ImGui::Text(TextFormat("Max Horizontal length : %.2f" , maxW     ));
    ImGui::Text(TextFormat("Max Height     length : %.2f" , maxH     ));
    ImGui::Text(TextFormat("Flight time    length : %.2f" , timeInAir));

    CloseWindow();
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
        if (lastMousePos.x != -100 && lastMousePos.y != -100)
        {
            Float2 delta = mousePos - lastMousePos;

            if (ClickInRectangle(mousePos, { (float)(canon->position.x - 200.f) ,(float)(canon->position.y - 200), (float)(canon->position.x + canon->size.x + 200) , (float)(canon->position.y + canon->size.y + 200) }))
            {
                canon->angle += delta.y * speedDrag;
                if (canon->angle < minAngleCanon)
                    canon->angle = minAngleCanon;
                if (canon->angle > maxAngleCanon)
                    canon->angle = maxAngleCanon;
            }
        }
        lastMousePos = mousePos;
    }
    else
    {
        lastMousePos = { -100,-100 };
    }
}

void UI::ShowValuesAfterShoot()
{
    ImGui::Begin("Real values");
    
    ImGui::Text(TextFormat("Real Horizontal length : %.2f", length));
    ImGui::Text(TextFormat("Real Height length     : %.2f", height));
    ImGui::Text(TextFormat("Real Flight time       : %.2f", timeAir));

    ImGui::End();
}

