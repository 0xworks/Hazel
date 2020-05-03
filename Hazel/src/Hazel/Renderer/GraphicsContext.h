#pragma once

namespace Hazel {

	class GraphicsContext {
	public:
		virtual ~GraphicsContext() = default;

		virtual void SwapBuffers() = 0;
	};

}
