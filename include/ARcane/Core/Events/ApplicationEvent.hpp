#pragma once

#include "ARcane/Core/Events/Event.hpp"

namespace ARcane {

/**
 * @class WindowResizeEvent
 * @brief Event triggered when the window is resized.
 */
class WindowResizeEvent : public Event {
   public:
    /**
     * @brief Constructs a WindowResizeEvent.
     * @param width The new width of the window.
     * @param height The new height of the window.
     */
    WindowResizeEvent(unsigned int width, unsigned int height) : m_Width(width), m_Height(height) {}

    /** @brief Gets the new width of the window. */
    inline unsigned int GetWidth() const { return m_Width; }

    /** @brief Gets the new height of the window. */
    inline unsigned int GetHeight() const { return m_Height; }

    /**
     * @brief Converts the event to a string. Used for debugging/logging.
     * @return The event as a string.
     */
    std::string ToString() const override {
        std::stringstream ss;
        ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
        return ss.str();
    }

    EVENT_CLASS_TYPE(WindowResize)
    EVENT_CLASS_CATEGORY((int)EventCategory::Application)

   private:
    unsigned int m_Width, m_Height;  // New dimensions of the window.
};

/**
 * @class WindowCloseEvent
 * @brief Event triggered when the window is closed.
 */
class WindowCloseEvent : public Event {
   public:
    /** @brief Constructs a WindowCloseEvent. */
    WindowCloseEvent() {}

    EVENT_CLASS_TYPE(WindowClose)
    EVENT_CLASS_CATEGORY((int)EventCategory::Application)
};

/**
 * @class AppTickEvent
 * @brief Event triggered when the application ticks (frame update).
 */
class AppTickEvent : public Event {
   public:
    /** @brief Constructs an AppTickEvent. */
    AppTickEvent() {}

    EVENT_CLASS_TYPE(AppTick)
    EVENT_CLASS_CATEGORY((int)EventCategory::Application)
};

/**
 * @class AppUpdateEvent
 * @brief Event triggered when the application updates.
 */
class AppUpdateEvent : public Event {
   public:
    /** @brief Constructs an AppUpdateEvent. */
    AppUpdateEvent() {}

    EVENT_CLASS_TYPE(AppUpdate)
    EVENT_CLASS_CATEGORY((int)EventCategory::Application)
};

/**
 * @class AppRenderEvent
 * @brief Event triggered when the application renders.
 */
class AppRenderEvent : public Event {
   public:
    /** @brief Constructs an AppRenderEvent. */
    AppRenderEvent() {}

    EVENT_CLASS_TYPE(AppRender)
    EVENT_CLASS_CATEGORY((int)EventCategory::Application)
};

}  // namespace ARcane
