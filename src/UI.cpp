#include "UI.h"
#include "Canon.h"
#include <iostream>
#include "App.h"
#include "Projectile.h"

#define WORLD_OPTION_NB 4 

double UI::length = 0;
double UI::height = 0;
double UI::timeAir = 0;
bool UI::drawProjectileForces = false;
std::map<int, ProjectileParameters> UI::projectileParameters = {};

static const char* preCalcultedOption[WORLD_OPTION_NB]
{
    "Earth",
    "Moon",
    "Mars",
    "Water"
};

static int usedOption;

float RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

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

void UI::DrawBackGround()
{
    if (clouds.size() < 15)
    { 
        clouds.push_back(Clouds{ RandomFloat(0.35 , 0.65), Float2 {RandomFloat(0,1920) , RandomFloat(0,300)}, RandomFloat(0.05f , 0.2f)  , (int)RandomFloat(75,255) });
    }

    for (Clouds& cl : clouds)
    {
        cl.pos.x -= cl.speed;
        if (cl.pos.x <= -(background.width * cl.scale))
            cl.pos.x = 1900;

        Color color = { 255,255,255, cl.opacity };
        DrawTextureEx(background, cl.pos, 0.0f, cl.scale, color);
    }  
}

void UI::Init()
{
    background = LoadTexture("assets/cloud.png");
    rlImGuiSetup(true);
}

UI::~UI()
{
}

void UI::Draw(Core::Canon* canon, Renderer::RendererManager& objectManager)
{
    ShowFPS();
    NewFrame();

    MoveCannon(canon);
    NewWindow("MainWindow");

    ProjectileParameters();
    ImGui::Spacing();
    CanonParameters(canon);
    ImGui::Spacing();
    WorldParameters(canon);
    ImGui::Spacing();
    CurrentProjectileParam();

    CloseWindow();

    ShowValuesBeforeShoot(canon);
    ShowValuesAfterShoot();
    NewWindow("Game");
    CanonAction(canon, objectManager);
    CloseWindow();

    EndFrame();
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
        ImGui::Checkbox("Draw forces", &drawProjectileForces);
        ImGui::TreePop();
    }
}

void UI::CanonParameters(Core::Canon* canon)
{
    if (ImGui::TreeNodeEx("Canon parameters ", ImGuiTreeNodeFlags_DefaultOpen))
    {
        Core::Rigidbody& canonRbody = canon->GetRigidbody();
        if (SliderDouble("Height##Canon", &canon->position.y, minHeightCanon, maxHeightCanon))
        {
            canon->initPos = canon->position;
            canonRbody.SetStartPos(canon->position);
            canon->valueChanged = true;
        }
        if (SliderDouble("Strength##Canon", &canon->power, 15 * (10.0 / Data::WorldSetting::pixelPerMeter), 900 * (10.0 / Data::WorldSetting::pixelPerMeter)))
        {
            canon->valueChanged = true;
        }
        if (SliderDouble("Shoot direction##Canon", &canon->angle, minAngleCanon, maxAngleCanon))
        {
            canon->valueChanged = true;

        }
        if (SliderDouble("Weight", &canon->weight, 1, 1000))
        {
            canon->valueChanged = true;

        }
        if (SliderDouble("Speed Drag", &speedDrag, 0.01, 100))
        {

            canon->valueChanged = true;
        }
        if (SliderDouble("Canon Lengh", &canon->canonLength, 0, 10))
        {
            canon->valueChanged = true;
        }
        ImGui::Checkbox("Canon Collision", &canon->isCollisionActive);
       
         
       

        ImGui::Text("Canon x delta : %f", (canon->position.x - canon->GetInitPos().x) / Data::WorldSetting::pixelPerMeter);
        ImGui::Text("Canon x velocity : %f", canonRbody.GetVelocity().x / Data::WorldSetting::pixelPerMeter);

        ImGui::TreePop();
    }
}

void UI::WorldParameters(Core::Canon* canon)
{
    if (ImGui::TreeNodeEx("World config",ImGuiTreeNodeFlags_DefaultOpen ))
    {
        if (SliderDouble("Gravity", &Data::WorldSetting::GRAVITY, -0.01, -50))
        {
            canon->valueChanged = true;
        }

        SliderDouble("Air Resistance", &Data::WorldSetting::airResistance, 0, 100);
        SliderDouble("Air Viscosity", &Data::WorldSetting::airViscosity, 0, 10);
        if (ImGui::Combo("Precalculted values", &usedOption, preCalcultedOption, WORLD_OPTION_NB))
            LoadWorldOption();

        ImGui::TreePop();
    }
}

void UI::LoadWorldOption()
{
    switch (usedOption)
    {
    case 0: // Earth
        Data::WorldSetting::GRAVITY = -9.81;
        Data::WorldSetting::airResistance = 0.1;
        Data::WorldSetting::airViscosity = 1.56;
        break;

    case 1: // Moon
        Data::WorldSetting::GRAVITY = -1.62;
        Data::WorldSetting::airResistance = 0.0;
        Data::WorldSetting::airViscosity = 0.0;
        break;

    case 2: // Mars
        Data::WorldSetting::GRAVITY = -3.721;
        Data::WorldSetting::airResistance = 0.118;
        Data::WorldSetting::airViscosity = 1.56;
        break;


    case 3: // Water
        Data::WorldSetting::GRAVITY = -9.81;
        Data::WorldSetting::airResistance = 1.0;
        Data::WorldSetting::airViscosity = 10.0;
        break;

    default:
        break;
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

void UI::CanonAction(Core::Canon* canon, Renderer::RendererManager& objectManager)
{
    if (ImGui::Button("Shoot", ImVec2(150,75)) || ImGui::IsKeyPressed(ImGuiKey::ImGuiKey_Space))
        canon->Shoot(sizeP,weight);
    if (ImGui::Button("Reset Position", ImVec2(150, 75)))
    {
        canon->ResetPosition();
    }
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
    Core::Rigidbody& canonRbody = canon->GetRigidbody();

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

                canon->initPos = canon->position;
                canonRbody.SetStartPos(canon->position);
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

