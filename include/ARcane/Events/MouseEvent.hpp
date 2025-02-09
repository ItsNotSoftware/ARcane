#pragma once

#include "ARcane/Events/Event.hpp"

namespace ARcane {

class MouseMovedEvent : public Event {
   public:
    MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) {}

    inline float GetX() const { return m_MouseX; }
    inline float GetY() const { return m_MouseY; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::Input)

   private:
    float m_MouseX, m_MouseY;
};

class MouseScrolledEvent : public Event {
   public:
    MouseScrolledEvent(float xOffset, float yOffset) : m_XOffset(xOffset), m_YOffset(yOffset) {}

    inline float GetXOffset() const { return m_XOffset; }
    inline float GetYOffset() const { return m_YOffset; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << m_XOffset << ", " << m_YOffset;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::Input)

   private:
    float m_XOffset, m_YOffset;
};

class MouseButtonPressedEvent : public Event {
   public:
    MouseButtonPressedEvent(int button) : m_Button(button) {}

    inline int GetButton() const { return m_Button; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::MouseButton |
                         (int)EventCategory::Input)

   private:
    int m_Button;
};

class MouseButtonReleasedEvent : public Event {
   public:
    MouseButtonReleasedEvent(int button) : m_Button(button) {}

    inline int GetButton() const { return m_Button; }

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << m_Button;
        return ss.str();
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
    EVENT_CLASS_CATEGORY((int)EventCategory::Mouse | (int)EventCategory::MouseButton |
                         (int)EventCategory::Input)

   private:
    int m_Button;
};

}  // namespace ARcane