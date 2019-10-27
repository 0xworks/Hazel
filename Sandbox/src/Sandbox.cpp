//#include "Hazel.h"

namespace Hazel {
   __declspec(dllimport) void PrintWelcome();
}

int main() {
   Hazel::PrintWelcome();
}
