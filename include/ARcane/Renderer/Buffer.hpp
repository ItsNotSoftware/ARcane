#pragma once

#include "ARcane/Core.hpp"

namespace ARcane {

/**
 * @enum ShaderDataType
 * @brief Represents different shader data types.
 */
enum class ShaderDataType {
    None = 0,
    Float,
    Float2,
    Float3,
    Float4,  // Floating point types.
    Mat3,
    Mat4,  // 3x3 and 4x4 matrix types.
    Int,
    Int2,
    Int3,
    Int4,  // Integer types.
    Bool   // Boolean type.
};

unsigned int ShaderDataTypeToOpenGLBaseType(ShaderDataType type);

/**
 * @class BufferElement
 * @brief Represents an element within a buffer.
 *
 * Each buffer element has a type, name, size, and offset.
 */
class BufferElement {
   public:
    /**
     * @brief Constructs a BufferElement.
     *
     * @param type The ShaderDataType of the buffer element.
     * @param name The name of the buffer element.
     */
    BufferElement(ShaderDataType type, const std::string& name, bool normalized = false);

    uint32_t GetComponentCount() const;

    ShaderDataType Type;  // Type of the buffer element.
    std::string Name;     // Name of the buffer element.
    uint32_t Size;        // Size in bytes.
    uint32_t Offset;      // Offset within the buffer.
    bool Normalized;      // Whether the data is normalized.
};

/**
 * @class BufferLayout
 * @brief Defines the layout of a buffer.
 *
 * This class stores a list of BufferElements and calculates their offsets.
 *
 * Example usage:
 * @code
 * BufferLayout layout = {
 *    {ShaderDataType::Float3, "a_Position"},
 *    {ShaderDataType::Float2, "a_TexCoord"},
 * };
 * @endcode
 */
class BufferLayout {
   public:
    /**
     * @brief Constructs a BufferLayout with a list of BufferElements.
     *
     * @param elements The list of BufferElements.
     */
    BufferLayout(const std::initializer_list<BufferElement>& elements);

    /**
     * @brief Gets the list of BufferElements in the layout.
     * @return A reference to the vector of BufferElements.
     */
    inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

    /**
     * @brief Gets the total stride of the layout.
     * @return The total stride in bytes.
     */
    inline uint32_t GetStride() const { return m_Stride; }

    // Iterators for BufferElements.
    std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
    std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
    std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

   private:
    void CalculateOffsetsAndStride();  // Computes offsets and total stride.

    std::vector<BufferElement> m_Elements;  // List of BufferElements.
    uint32_t m_Stride = 0;                  // Total stride in bytes.
};

/**
 * @class VertexBuffer
 * @brief Represents a GPU vertex buffer.
 *
 * Used to store vertex data in GPU memory.
 */
class VertexBuffer {
   public:
    /**
     * @brief Constructs a VertexBuffer and uploads data to GPU.
     *
     * @param vertices Pointer to vertex data.
     * @param size Size of the data in bytes.
     */
    VertexBuffer(float* vertices, uint32_t size);

    /**
     * @brief Destroys the VertexBuffer.
     */
    ~VertexBuffer();

    /**
     * @brief Binds the VertexBuffer.
     */
    void Bind() const;

    /**
     * @brief Unbinds the VertexBuffer.
     */
    void Unbind() const;

    /**
     * @brief Sets the layout of the VertexBuffer.
     *
     * @param layout The BufferLayout to set.
     */
    inline void SetLayout(const BufferLayout& layout) { m_Layout = layout; }

    /**
     * @brief Gets the layout of the VertexBuffer.
     * @return The BufferLayout of the VertexBuffer.
     */
    inline const BufferLayout& GetLayout() const { return m_Layout; }

   private:
    uint32_t m_RendererID = 0;   // Renderer-specific buffer ID.
    BufferLayout m_Layout = {};  // Layout of the buffer.
};

/**
 * @class IndexBuffer
 * @brief Represents an index buffer for rendering.
 *
 * Stores indices for indexed drawing.
 */
class IndexBuffer {
   public:
    /**
     * @brief Constructs an IndexBuffer and uploads data to GPU.
     *
     * @param indices Pointer to index data.
     * @param count Number of indices.
     */
    IndexBuffer(uint32_t* indices, uint32_t count);

    /**
     * @brief Destroys the IndexBuffer.
     */
    ~IndexBuffer();

    /**
     * @brief Binds the IndexBuffer.
     */
    void Bind() const;

    /**
     * @brief Unbinds the IndexBuffer.
     */
    void Unbind() const;

    /**
     * @brief Gets the count of indices.
     * @return The number of indices.
     */
    uint32_t GetCount() const { return m_Count; }

   private:
    uint32_t m_RendererID;  // Renderer-specific buffer ID.
    uint32_t m_Count;       // Number of indices.
};

}  // namespace ARcane
