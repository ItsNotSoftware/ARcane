#pragma once

#include "ARcane/Core.hpp"
#include "ARcane/Renderer/Buffer.hpp"

namespace ARcane {

class VertexArray {
   public:
    VertexArray();
    ~VertexArray();

    void Bind();
    void Unbind();

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

    inline const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const {
        return m_VertexBuffers;
    }

    inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

   private:
    uint32_t m_RendererID = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_VertexBuffers;
    std::shared_ptr<IndexBuffer> m_IndexBuffer;
};

}  // namespace ARcane