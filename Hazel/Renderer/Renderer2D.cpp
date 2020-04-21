#include "hzpch.h"
#include "Renderer/Renderer2D.h"

#include "Renderer/RenderCommand.h"
#include "glm/ext.hpp"

namespace Hazel {

   struct QuadVertex {
      glm::vec3 Position;
      glm::vec4 Color;
      glm::vec2 TextureCoord;
      float TextureIndex;
      float TilingFactor;
   };


   struct Renderer2DData {
      static const uint32_t MaxQuads = 10000;
      static const uint32_t MaxVertices = 4 * MaxQuads;
      static const uint32_t MaxIndices = 6 * MaxQuads;
      static const uint32_t MaxTextureSlots = 32;

      std::array<glm::vec4, 4> QuadVertexPostitions = {
         glm::vec4{-0.5f, -0.5f, 0.0f, 1.0f},
         glm::vec4{ 0.5f, -0.5f, 0.0f, 1.0f},
         glm::vec4{ 0.5f,  0.5f, 0.0f, 1.0f},
         glm::vec4{-0.5f,  0.5f, 0.0f, 1.0f}
      };

      std::array<glm::vec2, 4> QuadTextureCoordinates = {
         glm::vec2{0.0f, 0.0f},
         glm::vec2{0.0f, 1.0f},
         glm::vec2{1.0f, 1.0f},
         glm::vec2{1.0f, 0.0f}
      };

      std::unique_ptr<Shader> TextureShader;
      std::unique_ptr<Texture> WhiteTexture;
      std::unique_ptr<VertexArray> QuadVertexArray;

      uint32_t QuadIndexCount = 0;
      std::unique_ptr<QuadVertex[]> QuadVertices = std::make_unique<QuadVertex[]>(Renderer2DData::MaxVertices);
      uint32_t CurrentVertex = 0;

      std::array<uint32_t, MaxTextureSlots> TextureSlots;
      uint32_t TextureSlotIndex = 0;
   };

   static std::unique_ptr<Renderer2DData> s_data;


   void Renderer2D::Init() {
      s_data = std::make_unique<Renderer2DData>();
      s_data->QuadVertexArray = VertexArray::Create();

      std::unique_ptr<VertexBuffer> quadVB = Hazel::VertexBuffer::Create(Renderer2DData::MaxVertices * sizeof(QuadVertex));
      quadVB->SetLayout({
         { "a_position", ShaderDataType::Float3 },
         { "a_color", ShaderDataType::Float4 },
         { "a_textureCoord", ShaderDataType::Float2 },
         { "a_textureIndex", ShaderDataType::Float },
         { "a_tilingFactor", ShaderDataType::Float }
      });
      s_data->QuadVertexArray->SetVertexBuffer(std::move(quadVB));

      std::unique_ptr<uint32_t[]> quadIndices = std::make_unique<uint32_t[]>(Renderer2DData::MaxIndices);
      for (uint32_t i = 0, offset=0; i < Renderer2DData::MaxIndices; i += 6, offset += 4) {
         quadIndices[i + 0] = offset + 0;
         quadIndices[i + 1] = offset + 1;
         quadIndices[i + 2] = offset + 2;
         quadIndices[i + 3] = offset + 2;
         quadIndices[i + 4] = offset + 3;
         quadIndices[i + 5] = offset + 0;
      }
      std::unique_ptr<IndexBuffer> quadIB = Hazel::IndexBuffer::Create(quadIndices.get(), Renderer2DData::MaxIndices);
      s_data->QuadVertexArray->SetIndexBuffer(std::move(quadIB));

      s_data->WhiteTexture = Texture2D::Create(1, 1);
      uint32_t data = 0xFFFFFFFF;
      s_data->WhiteTexture->SetData(&data, sizeof(data));

#include "Texture.glsl.h"
      s_data->TextureShader = Shader::Create("Texture", vertexSrc, fragmentSrc);
      s_data->TextureShader->Bind();

      std::array<int, Renderer2DData::MaxTextureSlots> textures;
      for (int i = 0; i < textures.size(); ++i) {
         textures[i] = i;
      }
      s_data->TextureShader->SetIntArray("u_textures", textures.data(), static_cast<uint32_t>(textures.size()));

   }


   void Renderer2D::ShutDown() {
      s_data = nullptr;
   }


   void Renderer2D::BeginScene(const OrthographicCamera& camera) {
      s_data->TextureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
      s_data->CurrentVertex = 0;
      s_data->QuadIndexCount = 0;
      s_data->TextureSlotIndex = 0;
   }


   void Renderer2D::EndScene() {
      Flush();
   }


   void Renderer2D::Flush() {
      HZ_PROFILE_FUNCTION();

      s_data->QuadVertexArray->GetVertexBuffer().SetData(s_data->QuadVertices.get(), (s_data->CurrentVertex + 1) * sizeof(QuadVertex));
      RenderCommand::DrawIndexed(*s_data->QuadVertexArray, s_data->QuadIndexCount);
   }


   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const float rotationRadians, const glm::vec4& color) {
      DrawQuad({position.x, position.y, 0.0f}, size, rotationRadians, *s_data->WhiteTexture, 1.0f, color);
   }


   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotationRadians, const glm::vec4& color) {
      DrawQuad(position, size, rotationRadians, *s_data->WhiteTexture, 1.0f, color);
   }


   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const float rotationRadians, const Texture& texture, const float tilingFactor, const glm::vec4& color) {
      DrawQuad({position.x, position.y, 0.0f}, size, rotationRadians, texture, tilingFactor, color);
   }


   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const float rotationRadians, const Texture& texture, const float tilingFactor, const glm::vec4& color) {
      if (s_data->CurrentVertex >= s_data->MaxVertices - 4) {
         Flush();
      }

      float textureIndex = -1.0f;
      for (uint32_t i = 0; i < s_data->TextureSlotIndex; ++i) {
         if (s_data->TextureSlots[i] == texture.GetId()) {
            textureIndex = (float)i;
            break;
         }
      }
      if (textureIndex < 0.0f) {
         if (s_data->TextureSlotIndex == s_data->MaxTextureSlots) {
            Flush();
         }
         s_data->TextureSlots[s_data->TextureSlotIndex] = texture.GetId();
         textureIndex = (float)s_data->TextureSlotIndex;
         texture.Bind(s_data->TextureSlotIndex++); // Would probably be nicer in Flush(), but that makes the s_data->TextureSlots data structure more complicated
      }

      const glm::vec2 halfSize = size / 2.0f;

      const glm::mat4 transform = glm::translate(glm::identity<glm::mat4>(), position) * glm::rotate(glm::identity<glm::mat4>(), rotationRadians, {0.0f, 0.0f, 1.0f}) * glm::scale(glm::identity<glm::mat4>(), glm::vec3{size, 1.0f});

      for (int i = 0; i < 4; ++i) {
         s_data->QuadVertices[s_data->CurrentVertex++] = {transform * s_data->QuadVertexPostitions[i], color, s_data->QuadTextureCoordinates[i], textureIndex, tilingFactor};
      }
      s_data->QuadIndexCount += 6;
   };

}