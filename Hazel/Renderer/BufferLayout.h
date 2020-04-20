#pragma once

namespace Hazel {

   enum class ShaderDataType {
      None = 0,
      Float,
      Float2,
      Float3,
      Float4,
      Mat3,
      Mat4,
      UInt,
      UInt2,
      UInt3,
      UInt4,
      Int,
      Int2,
      Int3,
      Int4,
      Bool,
   };


   uint32_t ShaderDataTypeSize(ShaderDataType type);
   uint32_t ShaderDataTypeComponentCount(ShaderDataType type);


   struct BufferElement {
      std::string Name;
      ShaderDataType Type;
      uint32_t Size;
      uint32_t Offset;
      bool Normalized;

      BufferElement(const std::string& name, ShaderDataType type)
      : Name(name)
      , Type(type)
      , Size(ShaderDataTypeSize(type))
      , Offset(0)
      , Normalized(false)
      {}

      uint32_t GetComponentCount() const { return ShaderDataTypeComponentCount(Type); }

   };


   class BufferLayout {
   public:
      using BufferElementCollection = std::vector<BufferElement>;

      BufferLayout() = default;
      BufferLayout(const std::initializer_list<BufferElement>& elements);

      const BufferElementCollection& GetElements() const { return m_elements; }

      const uint32_t GetStride() const { return m_stride; }

      auto begin() { return m_elements.begin(); }
      auto end() { return m_elements.end(); }

      auto begin() const { return m_elements.begin(); }
      auto end() const { return m_elements.end(); }

      auto rbegin() { return m_elements.rbegin(); }
      auto rend() { return m_elements.rend(); }

      auto rbegin() const { return m_elements.rbegin(); }
      auto rend() const { return m_elements.rend(); }

   private:
      void CalculateOffsetsAndStride();

      BufferElementCollection m_elements;
      uint32_t m_stride = 0;
   };

}