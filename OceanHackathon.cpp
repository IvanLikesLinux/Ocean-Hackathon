#include <iostream> 
#include "raylib.h"

// void beginGame() {
//     BeginMode3DCamera();
//         DrawGrid(100, 2.0f);
//         DrawCube(cubePosition, 20.0f, 1.0f, 20.0f, BLUE);  
//     EndMode3D();
// }

void DrawPixelGrid(int width, int height, int spacing, int labelEvery) {
    const Color minor = {40, 40, 40, 255};
    const Color major = {80, 80, 80, 255};

    // Vertical lines, labeled with their x pixel along the top edge
    for (int x = 0; x <= width; x += spacing) {
        bool isMajor = (x % (spacing * labelEvery) == 0);
        DrawLine(x, 0, x, height, isMajor ? major : minor);
        if (isMajor) DrawText(TextFormat("%d", x), x + 3, 3, 10, GRAY);
    }

    // Horizontal lines, labeled with their y pixel along the left edge
    for (int y = 0; y <= height; y += spacing) {
        bool isMajor = (y % (spacing * labelEvery) == 0);
        DrawLine(0, y, width, y, isMajor ? major : minor);
        if (isMajor) DrawText(TextFormat("%d", y), 3, y + 3, 10, GRAY);
    }
}

int main() {
   //g++ OceanHackathon.cpp -o Trajectory $(pkg-config --cflags --libs raylib) 
    InitWindow(800, 600, "Ocean Hackathon");   // temporary size, must come first

    int monitor = GetCurrentMonitor();
    int screenWidth  = GetMonitorWidth(monitor);
    int screenHeight = GetMonitorHeight(monitor);
    SetWindowSize(screenWidth, screenHeight);
    SetWindowPosition((GetMonitorWidth(monitor) - screenWidth) / 2,
                      (GetMonitorHeight(monitor) - screenHeight) / 2);

    Texture2D bg = LoadTexture("TitleScreenBackground.png");
    if (bg.id == 0) TraceLog(LOG_ERROR, "Background failed to load!");
    Camera3D camera = { 0 };
    camera.position = (Vector3){ 0.0f, 10.0f, 10.0f };  // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f; 
    camera.projection = CAMERA_PERSPECTIVE;
    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector2 cubeScreenPosition = { 0.0f, 0.0f };
    float scale = (float)screenWidth / bg.width;
    if ((float)screenHeight / bg.height > scale) scale = (float)screenHeight / bg.height;

    float srcW = screenWidth / scale;
    float srcH = screenHeight / scale;
    int fontSize = screenHeight / 10;     // text is 1/10 of the screen height
    float textX    = (screenWidth * 3.0) / 10;   // starts 2/5 of the way across
    int textY    = screenHeight / 10;     // pick whatever y you want


    Rectangle src = { (bg.width - srcW) / 2.0f, (bg.height - srcH) / 2.0f, srcW, srcH };
    Rectangle dst = { 0, 0, (float)screenWidth, (float)screenHeight };

    //DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(60);
    while(!WindowShouldClose()) {
        //UpdateCamera(&camera, CAMERA_THIRD_PERSON);
        //cubeScreenPosition = GetWorldToScreen((Vector3){cubePosition.x, cubePosition.y + 2.5f, cubePosition.z}, camera);
        BeginDrawing();
            ClearBackground(RAYWHITE); 
            DrawTexturePro(bg, src, dst, (Vector2){ 0, 0 }, 0.0f, WHITE);
            DrawPixelGrid(screenWidth,screenHeight,100,2);
            DrawText("The Deep Sea", textX, textY, fontSize, WHITE);
            DrawFPS(10, 10);
        EndDrawing();
    }
    UnloadTexture(bg); 
    CloseWindow();
    return 0;
}