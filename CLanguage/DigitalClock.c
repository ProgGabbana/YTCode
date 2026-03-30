//DigitalClock.c is a YT Tutorial from https://www.youtube.com/watch?v=4GeYKi7IWDA 

//Notes to self (NTS):
//To use the Raylib library...

#include <stdio.h>
#include <time.h>
#include <raylib.h>
#include <stdbool.h>

#define WIDTH 900
#define HEIGHT 600

float segment_length = 200;
float segment_height = 50;

void DrawSegment(Vector2 center, bool orientation)
{
    // Create a real 7-segment display segment
    int count = 7;
    Vector2 a, b, c, d, e, f;

    if(orientation) // Horizontal
    {
        a = (Vector2) {center.x - segment_length / 2 - segment_height / 2, center.y};
        b = (Vector2) {center.x - segment_length / 2, center.y - segment_height / 2};
        c = (Vector2) {center.x - segment_length / 2, center.y + segment_height / 2};
        d = (Vector2) {center.x + segment_length / 2, center.y - segment_height / 2};
        e = (Vector2) {center.x + segment_length / 2, center.y + segment_height / 2};
        f = (Vector2) {center.x + segment_length / 2 + segment_height / 2, center.y};
    }
    else // Vertical
    {
        a = (Vector2) {center.x, center.y - segment_length / 2 - segment_height / 2};
        b = (Vector2) {center.x + segment_height / 2, center.y - segment_length / 2};
        c = (Vector2) {center.x - segment_height / 2, center.y - segment_length / 2};
        d = (Vector2) {center.x + segment_height / 2, center.y + segment_length / 2};
        e = (Vector2) {center.x - segment_height / 2, center.y + segment_length / 2};
        f = (Vector2) {center.x, center.y + segment_length / 2 + segment_height / 2};
    }
    Vector2 points[] = {a, c, b, e, d, f};
    DrawTriangleStrip(points, count, RAYWHITE);
    /* * NTS: DrawTriangleStrip requires a specific vertex sequence (Winding Order).
    * To create a continuous, visible surface, points must follow a consistent "Z" or "N" pattern.
    * * CRITICAL: Once a pattern is chosen (e.g., Even Point = Right/Bottom side, 
    * Odd Point = Left/Top side), this logic MUST be strictly maintained across all 
    * branches of the code. 
    * * Inconsistent logic between orientations will cause the mesh to "twist" or 
    * "flip" leading to zero-area triangles or Back-face Culling, which makes 
    * the geometry invisible on the screen.
    */
}

void DrawDigit(int digit, Vector2 center)
{
    // Draw first segment (top)
    Vector2 first = {center.x, center.y - segment_length / 2};
    DrawSegment(first, true);

    Vector2 second = {center.x - segment_length / 2, center.y - segment_length / 2};
    DrawSegment(second, false);
}

int main(int argc, char *argv[])
{
    time_t currentTime = time(NULL);
    char *time_string = ctime(&currentTime);

    printf("Current time: %s\n", time_string);
    InitWindow(WIDTH, HEIGHT, "Digital Clock");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        
        DrawDigit(1, (Vector2){400, 400});

        EndDrawing();
    }
    return 0;
}