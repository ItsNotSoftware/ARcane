#pragma once

#include "ARcane/Core.hpp"

#define BIT(x) (1 << x)

namespace ARcane {

/**
 * @enum EventType
 * @brief Defines different types of events in the engine.
 */
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
    KeyTyped,
    MouseButtonPressed,
    MouseButtonReleased,
    MouseMoved,
    MouseScrolled
};

/**
 * @enum EventCategory
 * @brief Defines categories for event filtering.
 *
 * Uses bitwise flags to allow multiple categories for a single event.
 */
enum class EventCategory {
    None = 0,
    Application = BIT(0),
    Input = BIT(1),
    Keyboard = BIT(2),
    Mouse = BIT(3),
    MouseButton = BIT(4)
};

/**
 * @def EVENT_CLASS_TYPE(type)
 * @brief Defines the required functions for getting the event type.
 */
#define EVENT_CLASS_TYPE(type)                                                  \
    static EventType GetStaticType() { return EventType::type; }                \
    virtual EventType GetEventType() const override { return GetStaticType(); } \
    virtual const char* GetName() const override { return #type; }

/**
 * @def EVENT_CLASS_CATEGORY(category)
 * @brief Defines the required function for getting the event category flags.
 */
#define EVENT_CLASS_CATEGORY(category) \
    virtual int GetCategoryFlags() const override { return category; }

/**
 * @class Event
 * @brief Base class for all events in the engine.
 *
 * The `IsInCategory()` function allows filtering by event category.
 */
class Event {
    friend class EventDispatcher;

   public:
    // Virtual functions for event handling. (to be overridden by derived classes)
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual int GetCategoryFlags() const = 0;
    virtual std::string ToString() const { return GetName(); }

    /**
     * @brief Checks if the event belongs to a specific category.
     * @param category The category to check.
     * @return True if the event is in the category, false otherwise.
     */
    inline bool IsInCategory(EventCategory category) {
        return GetCategoryFlags() & static_cast<int>(category);
    }

    bool Handled = false;  // Indicates whether the event has been handled.
};

/**
 * @class EventDispatcher
 * @brief Dispatches events to the appropriate event handlers.
 *
 * Uses templated functions to call the correct event function when an event matches.
 */
class EventDispatcher {
    template <typename T>
    using EventFn = std::function<bool(T&)>;

   public:
    /**
     * @brief Constructs an EventDispatcher.
     * @param event The event to be dispatched.
     */
    EventDispatcher(Event& event) : m_Event(event) {}

    /**
     * @brief Dispatches an event to a matching handler function.
     * @tparam T The event type.
     * @param func The function to call if the event type matches.
     * @return True if the event was dispatched, false otherwise.
     */
    template <typename T>
    bool Dispatch(EventFn<T> func) {
        if (m_Event.GetEventType() == T::GetStaticType()) {
            m_Event.Handled = func(*(T*)&m_Event);
            return true;
        }
        return false;
    }

   private:
    Event& m_Event;  // Reference to the event being dispatched.
};

}  // namespace ARcane
