#include "hzpch.h"
#include "Hazel/Core/Layer.h"

namespace Hazel {

   Layer::Layer(const std::string& debugName)
   : m_debugName(debugName) {}

   Layer::~Layer() {}

   const std::string& Layer::GetName() const {
      return m_debugName;
   }

}