#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

   LayerStack::LayerStack() {}


   LayerStack::~LayerStack() {
      for(Layer* layer : m_Layers) {
         delete layer;
      }
   }


   void LayerStack::PushLayer(Layer* pLayer) {
      m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex++, pLayer);
      pLayer->OnAttach();
      
   }


   void LayerStack::PushOverlay(Layer* pOverlay) {
      m_Layers.emplace_back(pOverlay);
      pOverlay->OnAttach();
   }


   void LayerStack::PopLayer(Layer* pLayer) {
      auto it = std::find(m_Layers.begin(), m_Layers.end(), pLayer);
      if(it != m_Layers.end()) {
         m_Layers.erase(it); 
         --m_LayerInsertIndex;
         pLayer->OnDetach();
      }
   }


   void LayerStack::PopOverlay(Layer* pOverlay) {
      auto it = std::find(m_Layers.begin(), m_Layers.end(), pOverlay);
      if(it != m_Layers.end()) {
         m_Layers.erase(it);
         pOverlay->OnDetach();
      }
   }

}