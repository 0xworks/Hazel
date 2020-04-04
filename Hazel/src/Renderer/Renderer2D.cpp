#include "hzpch.h"
#include "Renderer/Renderer2D.h"

#include "Renderer/RenderCommand.h"
#include "glm/ext.hpp"

namespace Hazel {

   struct QuadVertex {
      glm::vec3 Position;
      glm::vec4 Color;
      glm::vec2 TexCoord;
   };


   struct Renderer2DData {
      static const uint32_t MaxQuads = 10000;
      static const uint32_t MaxVertices = 4 * MaxQuads;
      static const uint32_t MaxIndices = 6 * MaxQuads;

      std::unique_ptr<Shader> TextureShader;
      std::unique_ptr<Texture> WhiteTexture;
      std::unique_ptr<VertexArray> QuadVertexArray;

      uint32_t QuadIndexCount = 0;
      std::unique_ptr<QuadVertex[]> QuadVertices = std::make_unique<QuadVertex[]>(Renderer2DData::MaxVertices);
      uint32_t CurrentQuad = 0;
   };

   static std::unique_ptr<Renderer2DData> s_data;


   void Renderer2D::Init() {
      s_data = std::make_unique<Renderer2DData>();
      s_data->QuadVertexArray = VertexArray::Create();

      std::unique_ptr<VertexBuffer> quadVB = Hazel::VertexBuffer::Create(Renderer2DData::MaxVertices * sizeof(QuadVertex));
      quadVB->SetLayout({
         { "a_position", ShaderDataType::Float3 },
         { "a_color", ShaderDataType::Float4 },
         { "a_texCoord", ShaderDataType::Float2 }
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
      s_data->TextureShader->SetUInt32("u_Texture", 0);
   }


   void Renderer2D::ShutDown() {
      s_data = nullptr;
   }


   void Renderer2D::BeginScene(const OrthographicCamera& camera) {
      s_data->TextureShader->Bind();
      s_data->TextureShader->SetMat4("u_viewProjection", camera.GetViewProjectionMatrix());
      s_data->CurrentQuad = 0;
      s_data->QuadIndexCount = 0;
   }


   void Renderer2D::EndScene() {
      Flush();
   }


   void Renderer2D::Flush() {
      HZ_PROFILE_FUNCTION();
      s_data->QuadVertexArray->GetVertexBuffer().SetData(s_data->QuadVertices.get(), (s_data->CurrentQuad + 1) * sizeof(QuadVertex));
      RenderCommand::DrawIndexed(*s_data->QuadVertexArray, s_data->QuadIndexCount);
   }


   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color) {
      DrawQuad({position.x, position.y, 0.0f}, size, *s_data->WhiteTexture, color);
   }


   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color) {
      DrawQuad(position, size, *s_data->WhiteTexture, color);
   }


   void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Texture& texture, const glm::vec4& color) {
      DrawQuad({position.x, position.y, 0.0f}, size, texture, color);
   }


   void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Texture& texture, const glm::vec4& color) {
      //   texture.Bind(0);
      //   s_data->TextureShader->SetVec4("u_color", color);
      //   s_data->TextureShader->SetMat4("u_transform", glm::translate(glm::identity<glm::mat4>(), position) * glm::scale(glm::identity<glm::mat4>(), {size.x, size.y, 1.0f}));
      //   s_data->QuadVertexArray->Bind();
      //   RenderCommand::DrawIndexed(*s_data->QuadVertexArray);

      const glm::vec2 halfSize = size / 2.0f;
      s_data->QuadVertices[s_data->CurrentQuad++] = {{position.x - halfSize.x, position.y - halfSize.y, 0.0f}, color, {0.0f, 0.0f}};
      s_data->QuadVertices[s_data->CurrentQuad++] = {{position.x - halfSize.x, position.y + halfSize.y, 0.0f}, color, {0.0f, 1.0f}};
      s_data->QuadVertices[s_data->CurrentQuad++] = {{position.x + halfSize.x, position.y + halfSize.y, 0.0f}, color, {1.0f, 1.0f}};
      s_data->QuadVertices[s_data->CurrentQuad++] = {{position.x + halfSize.x, position.y - halfSize.y, 0.0f}, color, {1.0f, 0.0f}};
      s_data->QuadIndexCount += 6;
   };

}