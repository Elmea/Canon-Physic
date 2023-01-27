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
bool UI::drawProjectilePath = true;
bool UI::drawShootPrediction = true;

Color UI::backgroundColor = SKYBLUE;
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
    if (m_drawClouds)
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
    ImGui::PushItemWidth(ImGui::GetWindowWidth() * 0.5f);
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
        SliderDouble("Weight (kg)##Projectile", &weight, 0.1, 1000);
        SliderDouble("Size (m)##Projectile", &sizeP, 4, 50);
        SliderDouble("Life Time (s)##Projectile", &Core::Projectile::lifeTimeAfterCollision, 0, 10);
        ImGui::Checkbox("Draw forces", &drawProjectileForces);
        ImGui::Checkbox("Draw path", &drawProjectilePath);
        ImGui::TreePop();
    }
}

void UI::CanonParameters(Core::Canon* canon)
{
    if (ImGui::TreeNodeEx("Canon parameters ", ImGuiTreeNodeFlags_DefaultOpen))
    {
        Core::Rigidbody& canonRbody = canon->GetRigidbody();
        if (SliderDouble("Height (m) ##Canon", &canon->position.y, minHeightCanon, maxHeightCanon))
        {
            canon->initPos = canon->position;
            canonRbody.SetStartPos(canon->position);
            canon->valueChanged = true;
        }
        if (SliderDouble("Bullet speed (m/s) ##Canon", &canon->power, 15 * (10.0 / Data::WorldSetting::pixelPerMeter), 900 * (10.0 / Data::WorldSetting::pixelPerMeter)))
        {
            canon->valueChanged = true;
        }
        if (SliderDouble("Angle (Degree)##Canon", &canon->angle, minAngleCanon, maxAngleCanon))
        {
            canon->valueChanged = true;

        }
        if (SliderDouble("Weight (kg)##Canon", &canon->weight, 1, 1000))
        {
            canon->valueChanged = true;

        }
        if (SliderDouble("Canon Lengh (m) ##Canon", &canon->canonLength, 0, 3))
        {
            canon->valueChanged = true;
        }

        ImGui::Checkbox("Shoot prediction##Canon", &drawShootPrediction);
        ImGui::Checkbox("Canon Collision##Canon", &canon->isCollisionActive);
       
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

        SliderDouble("Air Resistance", &Data::WorldSetting::airResistance, 0, 10);
        SliderDouble("Air Viscosity", &Data::WorldSetting::airViscosity, 0, 10);
        if (ImGui::Combo("Precalculted values", &usedOption, preCalcultedOption, WORLD_OPTION_NB))
        {
            LoadWorldOption();
            canon->valueChanged = true;
        }

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
        m_drawClouds = true;
        backgroundColor = SKYBLUE;
        background = LoadTexture("assets/cloud.png");
        break;

    case 1: // Moon
        Data::WorldSetting::GRAVITY = -1.62;
        Data::WorldSetting::airResistance = 0.0;
        Data::WorldSetting::airViscosity = 0.0;
        m_drawClouds = true;
        backgroundColor = BLACK;
        background = LoadTexture("assets/star.png");
        break;

    case 2: // Mars
        Data::WorldSetting::GRAVITY = -3.721;
        Data::WorldSetting::airResistance = 0.118;
        Data::WorldSetting::airViscosity = 1.56;
        m_drawClouds = false;
        backgroundColor = { 209, 145, 86 };
        break;


    case 3: // Water
        Data::WorldSetting::GRAVITY = -9.81;
        Data::WorldSetting::airResistance = 1.0;
        Data::WorldSetting::airViscosity = 10.0;
        m_drawClouds = true;
        backgroundColor = DARKBLUE;
        background = LoadTexture("assets/bubble.png");
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
        ImGui::Text(TextFormat("Velocity   : x = %2.f , y = %2.f", projectileParameters[itr->first].velocity.x, projectileParameters[itr->first].velocity.y));
        ImGui::Text(TextFormat("Speed      : %2.f m/s", projectileParameters[itr->first].velocity.Magnitude()));
        ImGui::Text(TextFormat("Position   : %2.f , %2.f", projectileParameters[itr->first].position.x, projectileParameters[itr->first].position.y));
        ImGui::Text(TextFormat("Current life time : %2.f s", projectileParameters[itr->first].currentLifeTime));

        ImGui::Checkbox(TextFormat("Should projectile die ##%d", itr->first), &projectileParameters[itr->first].shouldDie );
        ImGui::Checkbox(TextFormat("Control pos manually ##%d", itr->first), &(projectileParameters[itr->first].controlPos));

        if (projectileParameters[itr->first].controlPos)
        {
            SliderDouble(TextFormat("Lock position X ##%d", itr->first), &projectileParameters[itr->first].position.x, 0 , 1920/Data::WorldSetting::pixelPerMeter);
            SliderDouble(TextFormat("Lock position Y ##%d", itr->first), &projectileParameters[itr->first].position.y, 0.1, 1080 / Data::WorldSetting::pixelPerMeter);
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
        canon->valueChanged = true;
    }
}

void UI::ShowValuesBeforeShoot(Core::Canon* canon)
{
    NewWindow("Pre calculated values");

    /* Show values */
    ImGui::Text(TextFormat("Max Horizontal length : %.2f m" , canon->maxW     ));
    ImGui::Text(TextFormat("Max Height     length : %.2f m" , canon->maxH     ));
    ImGui::Text(TextFormat("Flight time    length : %.2f s" , canon->timeInAir));

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
    
    ImGui::Text(TextFormat("Real Horizontal length : %.2f m", length));
    ImGui::Text(TextFormat("Real Height length     : %.2f m", height));
    ImGui::Text(TextFormat("Real Flight time       : %.2f s", timeAir));

    ImGui::End();
}

