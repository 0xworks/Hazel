#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace Hazel {

   class LayerStack {
   public:
      ~LayerStack();

      void PushLayer(Layer* layer);
      void PushOverlay(Layer* overlay);
      void PopLayer(Layer* layer);
      void PopOverlay(Layer* overlay);

      auto begin() { return m_layers.begin(); }
      auto end() { return m_layers.end(); }

      auto rbegin() { return m_layers.rbegin(); }
      auto rend() { return m_layers.rend(); }

   private:
      std::vector<Layer*> m_layers;
      uint32_t m_layerInsertIndex = 0;
   };

}