#pragma once

#include "ARcane/Events/Event.hpp"

namespace ARcane {

/**
 * @class KeyEvent
 * @brief Base class for keyboard events.
 */
class KeyEvent : public Event {
   public:
    /**
     * @brief Gets the key code of the event.
     * @return The key code.
     */
    inline int GetKeyCode() const { return m_KeyCode; }

    EVENT_CLASS_CATEGORY((int)EventCategory::Keyboard | (int)EventCategory::Input)

   protected:
    /**
     * @brief Constructs a KeyEvent.
     * @param keycode The key code of the event.
     */
    KeyEvent(int keycode) : m_KeyCode(keycode) {}

    int m_KeyCode;  // The key code associated with the event.
};

/**
 * @class KeyPressedEvent
 * @brief Event for when a key is pressed.
 */
class KeyPressedEvent : public KeyEvent {
   public:
    /**
     * @brief Constructs a KeyPressedEvent.
     * @param keycode The key that was pressed.
     * @param repeatCount The number of times the key was repeated.
     */
    KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

    /**
     * @brief Gets the repeat count of the key press.
     * @return The number of times the key was repeated.
     */
    inline int GetRepeatCount() const { return m_RepeatCount; }

    /**
     * @brief Converts the event to a string. Used for debugging/logging.
     * @return The event as a string.
     */
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyPressed)

   private:
    int m_RepeatCount;  // Number of times the key was repeated.
};

/**
 * @class KeyReleasedEvent
 * @brief Event for when a key is released.
 */
class KeyReleasedEvent : public KeyEvent {
   public:
    /**
     * @brief Constructs a KeyReleasedEvent.
     * @param keycode The key that was released.
     */
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

    /**
     * @brief Converts the event to a string. Used for debugging/logging.
     * @return The event as a string.
     */
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << m_KeyCode;
        return ss.str();
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

}  // namespace ARcane