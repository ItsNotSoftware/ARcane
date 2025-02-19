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

    void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer);
    void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer);

    inline const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const {
        return m_VertexBuffers;
    }

    inline const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }

   private:
    uint32_t m_RendererID = 0;
    std::vector<Ref<VertexBuffer>> m_VertexBuffers;
    Ref<IndexBuffer> m_IndexBuffer;
};

}  // namespace ARcane