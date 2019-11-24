#include "hzpch.h"
#include "Renderer/Renderer2D.h"

#include "Renderer/RenderCommand.h"
#include "glm/ext.hpp"

namespace Hazel {

   struct Renderer2DData {
      std::unique_ptr<Shader> TextureShader;
      std::unique_ptr<Texture> WhiteTexture;
      std::unique_ptr<VertexArray> QuadVertexArray;
   };

   static std::unique_ptr<Renderer2DData> s_data;

   void Renderer2D::Init() {
      s_data = std::make_unique<Renderer2DData>();
      s_data->QuadVertexArray = VertexArray::Create();
      float quadVertices[5 * 4] = {
         -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
          0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
          0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
         -0.5f,  0.5f, 0.0f, 0.0f, 1.0f
      };
      std::unique_ptr<VertexBuffer> quadVertexBuffer = Hazel::VertexBuffer::Create(quadVertices, sizeof(quadVertices) / sizeof(float));

      quadVertexBuffer->SetLayout({
         {"a_position", ShaderDataType::Float3},
         { "a_texCoord", ShaderDataType::Float2}
      });

      s_data->QuadVertexArray->AddVertexBuffer(std::move(quadVertexBuffer));

      uint32_t indicesQuad[6] = {0, 1, 2, 2, 3, 0};
      std::unique_ptr<IndexBuffer> quadIndexBuffer = Hazel::IndexBuffer::Create(indicesQuad, sizeof(indicesQuad) / sizeof(uint32_t));

      s_data->QuadVertexArray->SetIndexBuffer(std::move(quadIndexBuffer));

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
   }


   void Renderer2D::EndScene() {}


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
      texture.Bind(0);
      s_data->TextureShader->SetVec4("u_color", color);
      s_data->TextureShader->SetMat4("u_transform", glm::translate(glm::identity<glm::mat4>(), position) * glm::scale(glm::identity<glm::mat4>(), {size.x, size.y, 1.0f}));
      s_data->QuadVertexArray->Bind();
      RenderCommand::DrawIndexed(*s_data->QuadVertexArray);
   }

}