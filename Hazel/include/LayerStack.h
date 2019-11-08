#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Hazel {

   class LayerStack {
   public:
      LayerStack();
      ~LayerStack();

      void PushLayer(Layer* layer);
      void PushOverlay(Layer* overlay);
      void PopLayer(Layer* layer);
      void PopOverlay(Layer* overlay);

      auto begin() { return m_Layers.begin(); }
      auto end() { return m_Layers.end(); }

      auto rbegin() { return m_Layers.rbegin(); }
      auto rend() { return m_Layers.rend(); }

   private:
      std::vector<Layer*> m_Layers;
      unsigned int m_LayerInsertIndex = 0;
   };

}