#pragma once

#include "Hazel/Events/EventType.h"

namespace Hazel {

   namespace Events {
      namespace Mouse {
         const EventType MOVED = "Events::Mouse::MOVED"_hash;
         const EventType SCROLLED = "Events::Mouse::SCROLLED"_hash;
         const EventType BUTTONPRESSED = "Events::Mouse::BUTTONPRESSED"_hash;
         const EventType BUTTONRELEASED = "Events::Mouse::BUTTONRELEASED"_hash;

         namespace Moved {
            const ParamId X = "Events::Mouse::Moved::X"_hash;
            const ParamId Y = "Events::Mouse::Moved::Y"_hash;
         }

         namespace Scrolled {
            const ParamId XOFFSET = "Events::Mouse::Moved::XOFFSET"_hash;
            const ParamId YOFFSET = "Events::Mouse::Moved::YOFFSET"_hash;
         }

         namespace ButtonPressed {
            const ParamId BUTTON = "Events::Mouse::ButtonPressed::BUTTON"_hash;
         }

         namespace ButtonReleased {
            const ParamId BUTTON = "Events::Mouse::ButtonReleased::BUTTON"_hash;
         }
      }
   }


   inline Event MouseMovedEvent(float x, float y) {
      Event event(Events::Mouse::MOVED);
      event.SetParam<float>(Events::Mouse::Moved::X, x);
      event.SetParam<float>(Events::Mouse::Moved::Y, y);
      return event;
   }


   inline Event MouseScrolledEvent(float xOffset, float yOffset) {
      Event event(Events::Mouse::SCROLLED);
      event.SetParam<float>(Events::Mouse::Scrolled::XOFFSET, xOffset);
      event.SetParam<float>(Events::Mouse::Scrolled::YOFFSET, yOffset);
      return event;
   }


   inline Event MouseButtonPressedEvent(int button) {
      Event event(Events::Mouse::BUTTONPRESSED);
      event.SetParam<int>(Events::Mouse::ButtonPressed::BUTTON, button);
      return event;
   }


   inline Event MouseButtonReleasedEvent(int button) {
      Event event(Events::Mouse::BUTTONRELEASED);
      event.SetParam<int>(Events::Mouse::ButtonReleased::BUTTON, button);
      return event;
   }

}
