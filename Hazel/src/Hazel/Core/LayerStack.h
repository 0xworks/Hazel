

#include "Hazel/Core/Layer.h"

#include <memory>
#include <vector>

namespace Hazel {

	class LayerStack {
	public:
		~LayerStack();

		void PushLayer(std::unique_ptr<Layer> layer);
		void PushOverlay(std::unique_ptr<Layer> layer);
		//       void PopLayer(Layer* layer);
		//       void PopOverlay(Layer* overlay);

		auto begin() { return m_layers.begin(); }
		auto end() { return m_layers.end(); }

		auto rbegin() { return m_layers.rbegin(); }
		auto rend() { return m_layers.rend(); }

	private:
		std::vector<std::unique_ptr<Layer>> m_layers;
		uint32_t m_layerInsertIndex = 0;
	};

}
