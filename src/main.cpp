#include <stdio.h>

#include "raylib.h"
#include <imgui.h>
#include "rlImGui.h"

int main(int argc, char* argv[])
{
    // Initialization
   //--------------------------------------------------------------------------------------
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    rlImGuiSetup(true); 

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);

        /* Raylib Draws */
        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

        /* ========================  */
        /* ImGui */
        rlImGuiBegin();
        ImGui::Begin("Test");
        ImGui::Button("button");
        ImGui::End();

        rlImGuiEnd();
        /* ========================  */

        EndDrawing();
        //----------------------------------------------------------------------------------
    }
    rlImGuiShutdown();

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
