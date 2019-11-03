#pragma once

#include "Core.h"

#define EVENT_CLASS_TYPE(type) public:                            \
static EventType GetStaticType() {                                \
   return EventType::##type;                                      \
}                                                                 \
                                                                  \
virtual EventType GetEventType() const override {                 \
   return GetStaticType();                                        \
}                                                                 \
                                                                  \
virtual const char* GetName() const override {                    \
   return #type;                                                  \
}                                                                 \

#define EVENT_CLASS_CATEGORY(category) public:                         \
   virtual int GetCategoryFlags() const override { return category; }  \


namespace Hazel {

   // Events in Hazel are currently blocking, meaning when an event occurs it
   // immediately gets dispatched and must be dealt with right then and there.
   // For the future, a better strategy might be to buffer events in an event
   // bus and process them during the "event" part of the update stage.


   // JRW: I am really not a fan of this.
   // It means that every time you want to add a new event type.. then you have to modify this "base class" Event.h file.
   // Adding a derived type should not force you to change the parent!
   // (and aside from that, it will also then force a full recompile of all other events) 
   enum class EventType {
      None = 0,
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

   enum EventCategory {
      None = 0,
      EventCategoryApplication = BIT(0),
      EventCategoryInput       = BIT(1),
      EventCategoryKeyboard    = BIT(2),
      EventCategoryMouse       = BIT(3),
      EventCategoryMouseButton = BIT(4)
   };


   class Event {
      friend class EventDispatcher;
   public:
      virtual EventType GetEventType() const = 0;
      virtual const char* GetName() const = 0;
      virtual int GetCategoryFlags() const = 0;
      virtual std::string ToString() const;

      bool IsInCategory(EventCategory category);

      bool IsHandled();

   protected:
      bool m_Handled = false;
   };

   class EventDispatcher {
      template<typename T> using EventFn = std::function<bool(T&)>;
   public:
      EventDispatcher(Event& event);

      template<typename T> bool Dispatch(EventFn<T> func);

   private:
      Event& m_Event;
   };


   template<typename T>
   bool Hazel::EventDispatcher::Dispatch(EventFn<T> func) {
      if(m_Event.GetEventType() == T::GetStaticType()) {
         m_Event.m_Handled = func(*(T*)&m_Event);
         return true;
      }
      return false;
   }


   inline std::ostream& operator<<(std::ostream& os, const Event& e) {
      return os << e.ToString();
   }

}