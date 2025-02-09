#pragma once

#include "ARcane/Core.hpp"

namespace ARcane {

enum class EventType {
    None,
    WindowClose,
    WindowResize,
    WindowFocus,
    WindowLostFocus,
    WindowMoved,
    AppTick,
    AppUpdate,
    AppRender,
    KeyPressed,
    KeyReleased,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

// For filtering events by category. Bitfield used for multiple categories a single event
enum class EventCategory {
    None = 0,
    Application = BIT(0),
    Input = BIT(1),
    Keyboard = BIT(2),
    Mouse = BIT(3),
    MouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

class Event {
    friend class EventDispatcher;

   public:
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    inline bool IsInCategory(EventCategory category) {
        return GetCategoryFlags() & static_cast<int>(category);
    }

   protected:
    bool m_Handled = false;
};

class EventDispatcher {
    template <typename T>
    using EventFn = std::function<bool(T&)>;

   public:
    EventDispatcher(Event& event) : m_Event(event) {}

    template <typename T>
    bool Dispatch(EventFn<T> func) {
        if (m_Event.GetEventType() == T::GetStaticType()) {
            m_Event.m_Handled = func(*(T*)&m_Event);
            return true;
        }
        return false;
    }

   private:
    Event& m_Event;
};

}  // namespace ARcane