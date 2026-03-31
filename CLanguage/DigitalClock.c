//DigitalClock.c is a YT Tutorial from https://www.youtube.com/watch?v=4GeYKi7IWDA 

#include <stdio.h>
#include <time.h>
#include <raylib.h>
// Notes to self (NTS): 
/* * HOW TO SET UP RAYLIB IN C:
 * 1. LIBRARY FILES: You need two main components:
 * - 'raylib.h' (Header): Defines the functions. Place it in your compiler's /include folder or your project folder.
 * - 'raylib.lib' or 'libraylib.a' (Static Library): The pre-compiled code. Place it in the /lib folder.
 * * 2. COMPILATION FLAGS: When compiling, you MUST link Raylib and its dependencies:
 * Command: gcc main.c -lraylib -lopengl32 -lgdi32 -lwinmm
 * * 3. VS CODE SETUP: If you see red squiggles (#include errors):
 * - Press Ctrl+Shift+P -> "C/C++: Edit Configurations (UI)"
 * - Add the path to the folder containing 'raylib.h' to the "Include path" section.
 * * Official Repository: https://github.com/raysan5/raylib
 */
#include <stdbool.h>

#define WIDTH 1040
#define HEIGHT 600
#define SEGMENT_LENGTH 40
#define SEGMENT_HEIGHT 27
#define OFFSET 50
#define STARTING_X 100
#define DIGIT_SPACING 130
#define COLON_SPACING 110
#define COLON_RADIUS 18

#define ONCOLOR RED
#define OFFCOLOR DARKGRAY

int digits[10][7] = {
    {1, 1, 1, 0, 1, 1, 1}, //0
    {0, 0, 1, 0, 0, 1, 0}, //1
    {1, 0, 1, 1, 1, 0, 1}, //2
    {1, 0, 1, 1, 0, 1, 1}, //3
    {0, 1, 1, 1, 0, 1, 0}, //4
    {1, 1, 0, 1, 0, 1, 1}, //5
    {1, 1, 0, 1, 1, 1, 1}, //6
    {1, 0, 1, 0, 0, 1, 0}, //7
    {1, 1, 1, 1, 1, 1, 1}, //8
    {1, 1, 1, 1, 0, 1, 1} //9
};

void DrawSegment(Vector2 center, bool orientation, Color color)
{
    // Create a real 7-segment display segment
    int count = 6;
    Vector2 a, b, c, d, e, f;

    if(orientation) // Horizontal
    {
        a = (Vector2) {center.x - SEGMENT_LENGTH / 2 - SEGMENT_HEIGHT / 2, center.y};
        b = (Vector2) {center.x - SEGMENT_LENGTH / 2, center.y - SEGMENT_HEIGHT / 2};
        c = (Vector2) {center.x - SEGMENT_LENGTH / 2, center.y + SEGMENT_HEIGHT / 2};
        d = (Vector2) {center.x + SEGMENT_LENGTH / 2, center.y - SEGMENT_HEIGHT / 2};
        e = (Vector2) {center.x + SEGMENT_LENGTH / 2, center.y + SEGMENT_HEIGHT / 2};
        f = (Vector2) {center.x + SEGMENT_LENGTH / 2 + SEGMENT_HEIGHT / 2, center.y};
    }
    else // Vertical
    {
        a = (Vector2) {center.x, center.y - SEGMENT_LENGTH / 2 - SEGMENT_HEIGHT / 2};
        b = (Vector2) {center.x + SEGMENT_HEIGHT / 2, center.y - SEGMENT_LENGTH / 2};
        c = (Vector2) {center.x - SEGMENT_HEIGHT / 2, center.y - SEGMENT_LENGTH / 2};
        d = (Vector2) {center.x + SEGMENT_HEIGHT / 2, center.y + SEGMENT_LENGTH / 2};
        e = (Vector2) {center.x - SEGMENT_HEIGHT / 2, center.y + SEGMENT_LENGTH / 2};
        f = (Vector2) {center.x, center.y + SEGMENT_LENGTH / 2 + SEGMENT_HEIGHT / 2};
    }
    Vector2 points[] = {a, c, b, e, d, f};
    DrawTriangleStrip(points, count, color);
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

void DrawDigit(Vector2 center, int digit)
{
    // find out which segments to draw based on the digit
    int *digit_segments = &digits[digit][0];

    // Draw first strip
    Vector2 first = {center.x, center.y - SEGMENT_LENGTH - OFFSET};
    DrawSegment(first, true, digit_segments[0] ? ONCOLOR : OFFCOLOR);

    Vector2 second = {center.x - SEGMENT_LENGTH / 2 - OFFSET / 2, center.y - SEGMENT_LENGTH / 2 - OFFSET / 2};
    DrawSegment(second, false, digit_segments[1] ? ONCOLOR : OFFCOLOR);

    Vector2 third = {center.x + SEGMENT_LENGTH / 2 + OFFSET / 2, center.y - SEGMENT_LENGTH / 2 - OFFSET / 2};
    DrawSegment(third, false, digit_segments[2] ? ONCOLOR : OFFCOLOR);

    Vector2 fourth = {center.x, center.y};
    DrawSegment(fourth, true, digit_segments[3] ? ONCOLOR : OFFCOLOR);

    Vector2 fifth = {center.x - SEGMENT_LENGTH / 2 - OFFSET / 2, center.y + SEGMENT_LENGTH / 2 + OFFSET / 2};
    DrawSegment(fifth, false, digit_segments[4] ? ONCOLOR : OFFCOLOR);

    Vector2 sixth = {center.x + SEGMENT_LENGTH / 2 + OFFSET / 2, center.y + SEGMENT_LENGTH / 2 + OFFSET / 2};
    DrawSegment(sixth, false, digit_segments[5] ? ONCOLOR : OFFCOLOR);

    Vector2 seventh = {center.x, center.y + SEGMENT_LENGTH + OFFSET};
    DrawSegment(seventh, true, digit_segments[6] ? ONCOLOR : OFFCOLOR);

    //NTS: Some times, the segments may not render correctly due to the winding order of the vertices.
}

void DrawColon(Vector2 center, int seconds)
{   
    DrawCircleV((Vector2){center.x, center.y - 50}, COLON_RADIUS, seconds % 2 ? OFFCOLOR : ONCOLOR);
    DrawCircleV((Vector2){center.x, center.y + 50}, COLON_RADIUS, seconds % 2 ? OFFCOLOR : ONCOLOR);
     // * NTS: The colon's on/off state is determined by the parity of the seconds value.
}

void DrawTime(int hours, int minutes, int seconds)
{
    float starting_x = STARTING_X;

    // Hours
    DrawDigit((Vector2){starting_x, HEIGHT / 2}, hours / 10);
    starting_x += DIGIT_SPACING;
    DrawDigit((Vector2){starting_x, HEIGHT / 2}, hours % 10);
    starting_x += COLON_SPACING;

    // Colon (static, not part of the digits array)
    DrawColon((Vector2){starting_x, HEIGHT / 2}, seconds);

    // Minutes
    starting_x += COLON_SPACING;
    DrawDigit((Vector2){starting_x, HEIGHT / 2}, minutes / 10);
    starting_x += DIGIT_SPACING;
    DrawDigit((Vector2){starting_x, HEIGHT / 2}, minutes % 10);
    starting_x += COLON_SPACING;

    // Colon (static, not part of the digits array)
    DrawColon((Vector2){starting_x, HEIGHT / 2}, seconds);

    // Seconds
    starting_x += COLON_SPACING;
    DrawDigit((Vector2){starting_x, HEIGHT / 2}, seconds / 10);
    starting_x += DIGIT_SPACING;
    DrawDigit((Vector2){starting_x, HEIGHT / 2}, seconds % 10);
}

int main(int argc, char *argv[])
{
    time_t currentTime = time(NULL);

    SetTargetFPS(60);
    InitWindow(WIDTH, HEIGHT, "Digital Clock");

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        time_t currentTime = time(NULL);
        struct tm *timeInfo = localtime(&currentTime);
        
        DrawTime(timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec);

        EndDrawing();
    }
    return 0;
}