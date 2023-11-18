#include "raylib.h"

#define GRID_X 4
#define GRID_Y 4
#define  GRID_SIZE 100
#define  GAP_SIZE 20
#define MAX_RECS GRID_X * GRID_Y


int clamp(int val, int max, int min) {
    if (val > max) {
        return max;
    } else if (val < min) {
        return min;
    } else {
        return val;
    }
}


int main(void)
{
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    bool toggled_rectangles[MAX_RECS];
    int total_toggled = MAX_RECS;
    for (int i = 0; i < MAX_RECS; i++){
        toggled_rectangles[i] = true;
    }

    InitWindow(screenWidth, screenHeight, "raylib [textures] example - mouse painting");
    MaximizeWindow();


    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        if (total_toggled == 0){
            return 0;
        }
        // Update
        //----------------------------------------------------------------------------------
        int max_space = 0;
        if (GetScreenHeight() > GetScreenWidth()){
            max_space = GetScreenWidth();
        } else {
            max_space = GetScreenHeight();
        }
        int tot_grid_size = GRID_X * GRID_SIZE + (GRID_X - 1) * GAP_SIZE;
        int grid_start_x = (GetScreenWidth() - tot_grid_size) / 2;
        int grid_start_y = (GetScreenHeight() - tot_grid_size) / 2;
        Rectangle rectangles[MAX_RECS] = {0};
        for (int y = 0; y < GRID_Y; y++){
            for (int x = 0; x < GRID_X; x++){
                rectangles[y * GRID_X + x].height = GRID_SIZE;
                rectangles[y * GRID_X + x].width = GRID_SIZE;
                rectangles[y * GRID_X + x].x = grid_start_x + GRID_SIZE * x + x * GAP_SIZE;
                rectangles[y * GRID_X + x].y = grid_start_y + GRID_SIZE * y + y * GAP_SIZE;
            }
        }

        // calculating collisions
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
            for (int i = 0; i < MAX_RECS; i++){
                bool colliding = CheckCollisionPointRec(GetMousePosition(), rectangles[i]);
                if (colliding && toggled_rectangles[i]){
                    toggled_rectangles[i] = false;
                    total_toggled--;
                }
            }
        }
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // draw rectangles that are toggled
        for (int i = 0; i < MAX_RECS; i++){
            if (toggled_rectangles[i]) {
                DrawRectangleRec(rectangles[i], BLACK);
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}