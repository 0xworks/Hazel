#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

   LayerStack::~LayerStack() {}


   void LayerStack::PushLayer(std::unique_ptr<Layer> layer) {
      m_layers.emplace(m_layers.begin() + m_layerInsertIndex, std::move(layer));
      m_layers[m_layerInsertIndex]->OnAttach();
      ++m_layerInsertIndex;
   }


   void LayerStack::PushOverlay(std::unique_ptr<Layer> overlay) {
      m_layers.emplace_back(std::move(overlay));
      m_layers.back()->OnAttach();
   }


//    void LayerStack::PopLayer(Layer* pLayer) {
//       auto it = std::find(m_layers.begin(), m_layers.end(), pLayer);
//       if(it != m_layers.end()) {
//          m_layers.erase(it); 
//          --m_layerInsertIndex;
//          pLayer->OnDetach();
//       }
//    }
// 
// 
//    void LayerStack::PopOverlay(Layer* pOverlay) {
//       auto it = std::find(m_layers.begin(), m_layers.end(), pOverlay);
//       if(it != m_layers.end()) {
//          m_layers.erase(it);
//          pOverlay->OnDetach();
//       }
//    }

}