#pragma once

#include "../Renderer/OrthographicCamera.h"
#include "../Renderer/RenderCommand.h"
#include "../Renderer/Shader.h"
#include "../Renderer/Texture.h"

namespace Hazel {

   class Renderer2D {
   public:

      static void Init();
      static void ShutDown();

      static void BeginScene(const OrthographicCamera& camera);
      static void EndScene();

      static void Flush();

      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const float rotationDegrees, const glm::vec4& color);
      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotationDegrees, const glm::vec4& color);
      static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const float rotationDegrees, const Texture& texture, const float tilingFactor = 1.0f, const glm::vec4& color = glm::vec4(1.0f));
      static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotationDegrees, const Texture& texture, const float tilingFactor = 1.0f, const glm::vec4& color = glm::vec4(1.0f));

		// Stats
		struct Statistics {
			std::array<float, 100> FrameRenderTime; // collect render time for multiple frames
			uint32_t DrawCalls = 0;
			uint32_t QuadCount = 0;
			uint32_t TextureCount = 0;
			uint32_t FrameCount = 0;
			float CurrentFrameBeginTime = 0.0f;
			float TotalFrameRenderTime = 0.0f;

			uint32_t GetTotalVertexCount() { return QuadCount * 4; }
			uint32_t GetTotalIndexCount() { return QuadCount * 6; }
		};

		static void ResetStats();
		static void StatsBeginFrame();
		static void StatsEndFrame();
		static Statistics GetStats();
	
	};

}
