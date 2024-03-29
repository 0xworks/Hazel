#include "hzpch.h"
#include "Core/Window.h"

namespace Hazel {

   WindowProps::WindowProps(const std::string& title /*= "Hazel Engine"*/, uint32_t width /*= 1280*/, uint32_t height /*= 720*/) : Title(title), Width(width), Height(height) {}

}