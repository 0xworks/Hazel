#pragma once

#include "Hazel/Events/EventType.h"

namespace Hazel {

   namespace Events {
      namespace Key {
         const EventType PRESSED = "Events::Key::PRESSED"_hash;
         const EventType RELEASED = "Events::Key::RELEASED"_hash;
         const EventType TYPED = "Events::Key::TYPED"_hash;

         namespace Pressed {
            const ParamId KEYCODE = "Events::Key::Pressed::KEYCODE"_hash;
            const ParamId REPEATCOUNT = "Events::Key::Pressed::REPEATCOUNT"_hash;
         }

         namespace Released {
            const ParamId KEYCODE = "Events::Key::Released::KEYCODE"_hash;
         }

         namespace Typed {
            const ParamId KEYCODE = "Events::Key::Typed::KEYCODE"_hash;
         }
      }
   }


   inline Event KeyPressedEvent(int keyCode, int repeatCount) {
      Event event(Events::Key::PRESSED);
      event.SetParam<int>(Events::Key::Pressed::KEYCODE, keyCode);
      event.SetParam<int>(Events::Key::Pressed::REPEATCOUNT, repeatCount);
      return event;
   }


   inline Event KeyReleasedEvent(int keyCode) {
      Event event(Events::Key::RELEASED);
      event.SetParam<int>(Events::Key::Released::KEYCODE, keyCode);
      return event;
   }


   inline Event KeyTypedEvent(int keyCode) {
      Event event(Events::Key::TYPED);
      event.SetParam<int>(Events::Key::Typed::KEYCODE, keyCode);
      return event;
   }

}