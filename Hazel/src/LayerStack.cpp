#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

   LayerStack::~LayerStack() {
      for(Layer* layer : m_layers) {
         delete layer;
      }
   }


   void LayerStack::PushLayer(Layer* pLayer) {
      m_layers.emplace(m_layers.begin() + m_layerInsertIndex++, pLayer);
      pLayer->OnAttach();
      
   }


   void LayerStack::PushOverlay(Layer* pOverlay) {
      m_layers.emplace_back(pOverlay);
      pOverlay->OnAttach();
   }


   void LayerStack::PopLayer(Layer* pLayer) {
      auto it = std::find(m_layers.begin(), m_layers.end(), pLayer);
      if(it != m_layers.end()) {
         m_layers.erase(it); 
         --m_layerInsertIndex;
         pLayer->OnDetach();
      }
   }


   void LayerStack::PopOverlay(Layer* pOverlay) {
      auto it = std::find(m_layers.begin(), m_layers.end(), pOverlay);
      if(it != m_layers.end()) {
         m_layers.erase(it);
         pOverlay->OnDetach();
      }
   }

}