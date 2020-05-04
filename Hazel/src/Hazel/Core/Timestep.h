#pragma once

namespace Hazel {

	class Timestep {
	public:
		Timestep(float time = 0.0f) : m_time(time) {}

		operator float() const { return m_time; }

		float GetSeconds() { return m_time; }
		float GetMilliseconds() { return m_time * 1000.0f; }

		Timestep& operator+=(const float delta) { m_time += delta; return *this; }

	private:
		float m_time;
	};

}
