#include <iostream> 

int main() {
    const int screenWidth = 1350;
    const int screenHeight = 1350;
    InitWindow(screenWidth, screenHeight, "The Deep Sea");
    Camera3D camera = { 0 };
    camera.position = {Vector3} {0.0f, 10.0f, 10.f};
    camera.target = (Vector3) {0.0,0.0f,0.0f};
    camera.up = (Vector3) {0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f; 
    camera.projection = CAMERA_PERSPECTIVE;
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    setTargetFPS(60);
    while(!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("Welcome to the third dimension!", 10, 40, 20, DARKGRAY);

            DrawFPS(10, 10);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;

    }

    }