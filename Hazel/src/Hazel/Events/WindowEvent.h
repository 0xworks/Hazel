#pragma once

#include "Hazel/Events/Event.h"

namespace Hazel {

   namespace Events {
      namespace Window {
         const EventType RESIZE = "Events::Window::RESIZE"_hash;
         const EventType CLOSE = "Events::Window::CLOSE"_hash;

         namespace Resize {
            const ParamId WIDTH = "Events::Window::Resize::WIDTH"_hash;
            const ParamId HEIGHT = "Events::Window::Resize::HEIGHT"_hash;
         }
      }
   }


   Event WindowResizeEvent(int width, int height) {
      Event event(Events::Window::RESIZE);
      event.SetParam<int>(Events::Window::Resize::WIDTH, width);
      event.SetParam<int>(Events::Window::Resize::HEIGHT, height);
      return event;
   }


   Event WindowCloseEvent() {
      Event event(Events::Window::CLOSE);
      return event;
   }

}
