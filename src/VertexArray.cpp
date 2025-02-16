#include "ARcane/Renderer/VertexArray.hpp"
#include <glad/glad.h>

namespace ARcane {

VertexArray::VertexArray() { glCreateVertexArrays(1, &m_RendererID); }

VertexArray::~VertexArray() { glDeleteVertexArrays(1, &m_RendererID); }

void VertexArray::Bind() { glBindVertexArray(m_RendererID); }

void VertexArray::Unbind() { glBindVertexArray(0); }

void VertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
    // Check if the vertex buffer has a layout (size > 0)
    ARC_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

    // Bind the vertex array and the vertex buffer
    glBindVertexArray(m_RendererID);
    vertexBuffer->Bind();

    uint32_t index = 0;
    const auto& layout = vertexBuffer->GetLayout();
    // Iterate through the layout elements
    for (const auto& element : layout) {
        // Enable the vertex attribute array and set the vertex attribute pointer
        glEnableVertexAttribArray(index);

        // Enable the vertex attribute array at the current index
        glVertexAttribPointer(index, element.GetComponentCount(),
                              ShaderDataTypeToOpenGLBaseType(element.Type),
                              element.Normalized ? GL_TRUE : GL_FALSE, layout.GetStride(),
                              (const void*)(uintptr_t)element.Offset);

        index++;
    }
    // Store the vertex buffer in the list of vertex buffers
    m_VertexBuffers.push_back(vertexBuffer);
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
    ARC_CORE_ASSERT(indexBuffer->GetCount(), "Index Buffer has no indices!");

    // Bind the vertex array and the index buffer
    glBindVertexArray(m_RendererID);
    indexBuffer->Bind();
    m_IndexBuffer = indexBuffer;
}

}  // namespace ARcane