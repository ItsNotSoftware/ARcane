#pragma once

#include "ARcane/Core/Core.hpp"

namespace ARcane {

class Mouse {
   public:
    static const int Left = 0;
    static const int Right = 1;
    static const int Middle = 2;
};

// Keycodes
class Key {
   public:
    static const int Space = 32;
    static const int Apostrophe = 39; /* ' */
    static const int Comma = 44;      /* , */
    static const int Minus = 45;      /* - */
    static const int Period = 46;     /* . */
    static const int Slash = 47;      /* / */
    static const int Num0 = 48;
    static const int Num1 = 49;
    static const int Num2 = 50;
    static const int Num3 = 51;
    static const int Num4 = 52;
    static const int Num5 = 53;
    static const int Num6 = 54;
    static const int Num7 = 55;
    static const int Num8 = 56;
    static const int Num9 = 57;
    static const int Semicolon = 59; /* ; */
    static const int Equal = 61;     /* = */
    static const int A = 65;
    static const int B = 66;
    static const int C = 67;
    static const int D = 68;
    static const int E = 69;
    static const int F = 70;
    static const int G = 71;
    static const int H = 72;
    static const int I = 73;
    static const int J = 74;
    static const int K = 75;
    static const int L = 76;
    static const int M = 77;
    static const int N = 78;
    static const int O = 79;
    static const int P = 80;
    static const int Q = 81;
    static const int R = 82;
    static const int S = 83;
    static const int T = 84;
    static const int U = 85;
    static const int V = 86;
    static const int W = 87;
    static const int X = 88;
    static const int Y = 89;
    static const int Z = 90;
    static const int LeftBracket = 91;  /* [ */
    static const int Backslash = 92;    /* \ */
    static const int RightBracket = 93; /* ] */
    static const int GraveAccent = 96;  /* ` */
    static const int World1 = 161;      /* non-US #1 */
    static const int World2 = 162;      /* non-US #2 */
    static const int Escape = 256;
    static const int Enter = 257;
    static const int Tab = 258;
    static const int Backspace = 259;
    static const int Insert = 260;
    static const int Delete = 261;
    static const int Right = 262;
    static const int Left = 263;
    static const int Down = 264;
    static const int Up = 265;
    static const int PageUp = 266;
    static const int PageDown = 267;
    static const int Home = 268;
    static const int End = 269;
    static const int CapsLock = 280;
    static const int ScrollLock = 281;
    static const int NumLock = 282;
    static const int PrintScreen = 283;
    static const int Pause = 284;
    static const int F1 = 290;
    static const int F2 = 291;
    static const int F3 = 292;
    static const int F4 = 293;
    static const int F5 = 294;
    static const int F6 = 295;
    static const int F7 = 296;
    static const int F8 = 297;
    static const int F9 = 298;
    static const int F10 = 299;
    static const int F11 = 300;
    static const int F12 = 301;
    static const int F13 = 302;
    static const int F14 = 303;
    static const int F15 = 304;
    static const int F16 = 305;
    static const int F17 = 306;
    static const int F18 = 307;
    static const int F19 = 308;
    static const int F20 = 309;
    static const int F21 = 310;
    static const int F22 = 311;
    static const int F23 = 312;
    static const int F24 = 313;
    static const int F25 = 314;
    static const int KP_0 = 320;
    static const int KP_1 = 321;
    static const int KP_2 = 322;
    static const int KP_3 = 323;
    static const int KP_4 = 324;
    static const int KP_5 = 325;
    static const int KP_6 = 326;
    static const int KP_7 = 327;
    static const int KP_8 = 328;
    static const int KP_9 = 329;
    static const int KP_Decimal = 330;
    static const int KP_Divide = 331;
    static const int KP_Multiply = 332;
    static const int KP_Subtract = 333;
    static const int KP_Add = 334;
    static const int KP_Enter = 335;
    static const int KP_Equal = 336;
    static const int LeftShift = 340;
    static const int LeftControl = 341;
    static const int LeftAlt = 342;
    static const int LeftSuper = 343;
    static const int RightShift = 344;
    static const int RightControl = 345;
    static const int RightAlt = 346;
    static const int RightSuper = 347;
    static const int Menu = 348;
};

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
