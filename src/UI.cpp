#include "UI.h"
#include "Canon.h"
#include <iostream>
#include "App.h"
#include "Projectile.h"

double UI::length = 0;
double UI::height = 0;
double UI::timeAir = 0;
std::map<int, ProjectileParameters> UI::projectileParameters = {};

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
        SliderDouble("Weight##Projectile", &weight, 0.1, 1000);
        SliderDouble("Size##Projectile", &sizeP, 4, 50);
        SliderDouble("Life Time##Projectile", &Core::Projectile::lifeTimeAfterCollision, 0, 10);
        ImGui::TreePop();
    }
}

void UI::CanonParameters(Core::Canon* canon)
{
    if (ImGui::TreeNodeEx("Canon parameters ", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (SliderDouble("Height##Canon", &canon->position.y, minHeightCanon, maxHeightCanon))
            canon->valueChanged = true;
        if (SliderDouble("Strength##Canon", &canon->power, 15 * (10.0 / Data::WorldSetting::pixelPerMeter), 900 * (10.0 / Data::WorldSetting::pixelPerMeter)))   
            canon->valueChanged = true;
        if (SliderDouble("Shoot direction##Canon", &canon->angle, minAngleCanon, maxAngleCanon))
            canon->valueChanged = true;
        if (SliderDouble("Speed Drag", &speedDrag, 0.01, 100))
            canon->valueChanged = true;
        
        ImGui::TreePop();
    }
}

void UI::WorldParameters()
{
    if (ImGui::TreeNodeEx("World config",ImGuiTreeNodeFlags_DefaultOpen ))
    {
        SliderDouble("Gravity", &Data::WorldSetting::GRAVITY, -1, 50);
        SliderDouble("Air Resistance", &Data::WorldSetting::airResistance, 0, 1);
        SliderDouble("Air Viscosity", &Data::WorldSetting::airViscosity, 0, 10);
        SliderDouble("Size Repere", &Data::WorldSetting::pixelPerMeter, 0.0001f, 10);

        ImGui::TreePop();
    }
}

void UI::CurrentProjectileParam()
{
    int i = 0;
    for (auto itr = projectileParameters.begin(); itr != projectileParameters.end() && i < 5; ++itr, i++)
    {
        ImGui::Text(TextFormat("Projectile n %d", itr->first));
        ImGui::Text(TextFormat("Velocity   : %2.f , %2.f", projectileParameters[itr->first].velocity.x, projectileParameters[itr->first].velocity.y));
        ImGui::Text(TextFormat("Position   : %2.f , %2.f", projectileParameters[itr->first].position.x, projectileParameters[itr->first].position.y));
        ImGui::Text(TextFormat("Current life time : %2.f", projectileParameters[itr->first].currentLifeTime));
        ImGui::Checkbox("Should projectile die", &projectileParameters[itr->first].shouldDie);

        ImGui::Checkbox("Control pos manually", &projectileParameters[itr->first].controlPos);
        if (projectileParameters[itr->first].controlPos)
        {
            SliderDouble("Lock position X", &projectileParameters[itr->first].position.x, 0 , 1920/Data::WorldSetting::pixelPerMeter);
            SliderDouble("Lock position Y", &projectileParameters[itr->first].position.y, 0.1, 1080 / Data::WorldSetting::pixelPerMeter);
        }

        ImGui::NewLine();
        ImGui::NewLine();
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


    /* Show values */
    ImGui::Text(TextFormat("Max Horizontal length : %.2f" , canon->maxW     ));
    ImGui::Text(TextFormat("Max Height     length : %.2f" , canon->maxH     ));
    ImGui::Text(TextFormat("Flight time    length : %.2f" , canon->timeInAir));

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
            delta.y *= -1;

            if (ClickInRectangle(mousePos, { 0,0,(float)canon->position.x + 200 , 1080 }))
            {
                canon->position.y += delta.y * speedDrag;
                if (canon->position.y < minHeightCanon)
                    canon->position.y = minHeightCanon;
                if (canon->position.y > maxHeightCanon)
                    canon->position.y = maxHeightCanon;

                canon->valueChanged = true;
            }
        }

        lastMousePos = mousePos;
    }
    else if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        if (lastMousePos.x != -100 && lastMousePos.y != -100)
        {
            Float2 delta = mousePos - lastMousePos;

            Float2 posRaylib = Data::WorldSetting::GetRaylibPos(canon->position);

            if (ClickInRectangle(mousePos, { (float)(canon->position.x - 200.f) ,(float)(posRaylib.y - 200), (float)(canon->position.x + canon->size.x + 200) , (float)(posRaylib.y + canon->size.y + 200) }))
            {
                canon->angle += delta.y * speedDrag;
                if (canon->angle < minAngleCanon)
                    canon->angle = minAngleCanon;
                if (canon->angle > maxAngleCanon)
                    canon->angle = maxAngleCanon;

                canon->valueChanged = true;
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

