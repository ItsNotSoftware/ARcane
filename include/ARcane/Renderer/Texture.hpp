#pragma once

#include "ARcane/Core.hpp"

namespace ARcane {

class Texture {
   public:
    virtual ~Texture() = default;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual void Bind() const = 0;
};

class Texture2D : public Texture {
   public:
    Texture2D(const std::string& path);
    ~Texture2D();

    uint32_t GetWidth() const override { return m_Width; }
    uint32_t GetHeight() const override { return m_Height; }

    void Bind() const override;

   private:
    std::string m_Path;
    uint32_t m_Width, m_Height;
    uint32_t m_RendererID;
};

}  // namespace ARcane
