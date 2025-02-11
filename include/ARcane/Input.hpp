#pragma once

#include "ARcane/Core.hpp"

namespace ARcane {

namespace Mouse {
constexpr int Left = 0;
constexpr int Right = 1;
constexpr int Middle = 2;
}  // namespace Mouse

// Keycodes
namespace Key {
constexpr int Space = 32;
constexpr int Apostrophe = 39; /* ' */
constexpr int Comma = 44;      /* , */
constexpr int Minus = 45;      /* - */
constexpr int Period = 46;     /* . */
constexpr int Slash = 47;      /* / */
constexpr int Num0 = 48;
constexpr int Num1 = 49;
constexpr int Num2 = 50;
constexpr int Num3 = 51;
constexpr int Num4 = 52;
constexpr int Num5 = 53;
constexpr int Num6 = 54;
constexpr int Num7 = 55;
constexpr int Num8 = 56;
constexpr int Num9 = 57;
constexpr int Semicolon = 59; /* ; */
constexpr int Equal = 61;     /* = */
constexpr int A = 65;
constexpr int B = 66;
constexpr int C = 67;
constexpr int D = 68;
constexpr int E = 69;
constexpr int F = 70;
constexpr int G = 71;
constexpr int H = 72;
constexpr int I = 73;
constexpr int J = 74;
constexpr int K = 75;
constexpr int L = 76;
constexpr int M = 77;
constexpr int N = 78;
constexpr int O = 79;
constexpr int P = 80;
constexpr int Q = 81;
constexpr int R = 82;
constexpr int S = 83;
constexpr int T = 84;
constexpr int U = 85;
constexpr int V = 86;
constexpr int W = 87;
constexpr int X = 88;
constexpr int Y = 89;
constexpr int Z = 90;
constexpr int LeftBracket = 91;  /* [ */
constexpr int Backslash = 92;    /* \ */
constexpr int RightBracket = 93; /* ] */
constexpr int GraveAccent = 96;  /* ` */
constexpr int World1 = 161;      /* non-US #1 */
constexpr int World2 = 162;      /* non-US #2 */
constexpr int Escape = 256;
constexpr int Enter = 257;
constexpr int Tab = 258;
constexpr int Backspace = 259;
constexpr int Insert = 260;
constexpr int Delete = 261;
constexpr int Right = 262;
constexpr int Left = 263;
constexpr int Down = 264;
constexpr int Up = 265;
constexpr int PageUp = 266;
constexpr int PageDown = 267;
constexpr int Home = 268;
constexpr int End = 269;
constexpr int CapsLock = 280;
constexpr int ScrollLock = 281;
constexpr int NumLock = 282;
constexpr int PrintScreen = 283;
constexpr int Pause = 284;
constexpr int F1 = 290;
constexpr int F2 = 291;
constexpr int F3 = 292;
constexpr int F4 = 293;
constexpr int F5 = 294;
constexpr int F6 = 295;
constexpr int F7 = 296;
constexpr int F8 = 297;
constexpr int F9 = 298;
constexpr int F10 = 299;
constexpr int F11 = 300;
constexpr int F12 = 301;
constexpr int F13 = 302;
constexpr int F14 = 303;
constexpr int F15 = 304;
constexpr int F16 = 305;
constexpr int F17 = 306;
constexpr int F18 = 307;
constexpr int F19 = 308;
constexpr int F20 = 309;
constexpr int F21 = 310;
constexpr int F22 = 311;
constexpr int F23 = 312;
constexpr int F24 = 313;
constexpr int F25 = 314;
constexpr int KP_0 = 320;
constexpr int KP_1 = 321;
constexpr int KP_2 = 322;
constexpr int KP_3 = 323;
constexpr int KP_4 = 324;
constexpr int KP_5 = 325;
constexpr int KP_6 = 326;
constexpr int KP_7 = 327;
constexpr int KP_8 = 328;
constexpr int KP_9 = 329;
constexpr int KP_Decimal = 330;
constexpr int KP_Divide = 331;
constexpr int KP_Multiply = 332;
constexpr int KP_Subtract = 333;
constexpr int KP_Add = 334;
constexpr int KP_Enter = 335;
constexpr int KP_Equal = 336;
constexpr int LeftShift = 340;
constexpr int LeftControl = 341;
constexpr int LeftAlt = 342;
constexpr int LeftSuper = 343;
constexpr int RightShift = 344;
constexpr int RightControl = 345;
constexpr int RightAlt = 346;
constexpr int RightSuper = 347;
constexpr int Menu = 348;
}  // namespace Key

/**
 * @class Input
 * @brief Provides functions for input polling, such as checking keyboard and mouse state.
 *
 * The Input class allows querying for key presses, mouse button presses, and mouse position.
 */
class Input {
   public:
    /**
     * @brief Checks if a specific key is currently pressed.
     * @param keycode The key to check.
     * @return True if the key is pressed, false otherwise.
     */
    static bool IsKeyPressed(KeyCode keycode);

    /**
     * @brief Checks if a specific mouse button is currently pressed.
     * @param button The mouse button index.
     * @return True if the button is pressed, false otherwise.
     */
    static bool IsMouseButtonPressed(int button);

    /**
     * @brief Retrieves the current mouse cursor position.
     * @return A pair containing the X and Y coordinates of the mouse.
     */
    static std::pair<float, float> GetMousePosition();

    /**
     * @brief Retrieves the current X-coordinate of the mouse cursor.
     * @return The X position of the mouse.
     */
    static float GetMouseX();

    /**
     * @brief Retrieves the current Y-coordinate of the mouse cursor.
     * @return The Y position of the mouse.
     */
    static float GetMouseY();
};

}  // namespace ARcane

/**
    ============================
    Example Usage:
    ============================
    #include "ARcane/Input.hpp"

    void ProcessInput() {
        using namespace ARcane;

        if (ARcane::Input::IsKeyPressed(Key::W)) {
            std::cout << "Moving forward!" << std::endl;
        }

        if (Input::IsMouseButtonPressed(Mouse::Left)) {
            std::cout << "Mouse clicked!" << std::endl;
        }

        auto [mouseX, mouseY] = ARcane::Input::GetMousePosition();
        std::cout << "Mouse Position: (" << mouseX << ", " << mouseY << ")" << std::endl;
    }
 */
