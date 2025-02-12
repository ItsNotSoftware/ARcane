#pragma once

#include "ARcane/Core.hpp"

namespace ARcane {

class Shader {
   public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void Bind() const;
    void Unbind() const;

   private:
    uint32_t m_RendererID;
};

};  // namespace ARcane