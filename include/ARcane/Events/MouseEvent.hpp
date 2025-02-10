#pragma once

#include "ARcane/Events/Event.hpp"

namespace ARcane {

/**
 * @class MouseMovedEvent
 * @brief Event for mouse movement.
 */
class MouseMovedEvent : public Event {
   public:
    /**
     * @brief Constructs a MouseMovedEvent.
     * @param x The new X position of the mouse.
     * @param y The new Y position of the mouse.
     */
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    /**
     * @brief Gets the X position of the mouse.
     */
    inline float GetX() const { return m_MouseX; }

    /**
     * @brief Gets the Y position of the mouse.
     */
    inline float GetY() const { return m_MouseY; }

    /**
     * @brief Converts the event to a string. Used for debugging/logging.
     * @return The event as a string.
     */
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

    // Set the event type and category
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::Input)

   private:
    float m_MouseX, m_MouseY;  // The X and Y position of the mouse.
};

/**
 * @class MouseScrolledEvent
 * @brief Event for mouse scrolling.
 */
class MouseScrolledEvent : public Event {
   public:
    /**
     * @brief Constructs a MouseScrolledEvent.
     * @param xOffset The horizontal scroll offset.
     * @param yOffset The vertical scroll offset.
     */
    MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

    /**
     * @brief Gets the horizontal scroll offset.
     */
    inline float GetXOffset() const { return m_XOffset; }

    /**
     * @brief Gets the vertical scroll offset.
     */
    inline float GetYOffset() const { return m_YOffset; }

    /**
     * @brief Converts the event to a string. Used for debugging/logging.
     * @return The event as a string.
     */
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
        return ss.str();
    }

    // Set the event type and category
    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::Input)

   private:
    float m_XOffset, m_YOffset;  // The horizontal and vertical scroll offsets.
};

/**
 * @class MouseButtonPressedEvent
 * @brief Event for mouse button presses.
 */
class MouseButtonPressedEvent : public Event {
   public:
    /**
     * @brief Constructs a MouseButtonPressedEvent.
     * @param button The mouse button that was pressed.
     */
    MouseButtonPressedEvent(int button) : m_Button(button) {}

    /**
     * @brief Gets the pressed button.
     */
    inline int GetButton() const { return m_Button; }

    /**
     * @brief Converts the event to a string. Used for debugging/logging.
     * @return The event as a string.
     */
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    // Set the event type and category
    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::MouseButton |
                         (int)EventCategory::Input)

   private:
    int m_Button;  // The button that was pressed.
};

/**
 * @class MouseButtonReleasedEvent
 * @brief Event for mouse button releases.
 */
class MouseButtonReleasedEvent : public Event {
   public:
    /**
     * @brief Constructs a MouseButtonReleasedEvent.
     * @param button The mouse button that was released.
     */
    MouseButtonReleasedEvent(int button) : m_Button(button) {}

    /**
     * @brief Gets the released button.
     */
    inline int GetButton() const { return m_Button; }

    /**
     * @brief Converts the event to a string. Used for debugging/logging.
     * @return The event as a string.
     */
    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    // Set the event type and category
    EVENT_CLASS_TYPE(MouseButtonReleased)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::MouseButton |
                         (int)EventCategory::Input)

   private:
    int m_Button;  // The button that was released.
};

}  // namespace ARcane