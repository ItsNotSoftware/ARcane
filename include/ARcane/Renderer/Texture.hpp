#pragma once

#include "ARcane/Core.hpp"
#include <glad/glad.h>

namespace ARcane {

class Texture {
   public:
    virtual ~Texture() = default;
    virtual uint32_t GetWidth() const = 0;
    virtual uint32_t GetHeight() const = 0;
    virtual void SetData(void* data, uint32_t size) = 0;
    virtual void Bind(uint32_t slot = 0) const = 0;
};

class Texture2D : public Texture {
   public:
    Texture2D(const std::string& path);
    Texture2D(uint32_t width, uint32_t height);
    ~Texture2D();

    inline uint32_t GetWidth() const override { return m_Width; }
    inline uint32_t GetHeight() const override { return m_Height; }
    inline uint32_t GetRendererID() const { return m_RendererID; }

    void SetData(void* data, uint32_t) override;

    void Bind(uint32_t slot = 0) const override;

    inline bool operator==(const Texture2D& other) const {
        return m_RendererID == other.m_RendererID;
    }

   private:
    std::string m_Path;
    uint32_t m_Width, m_Height;
    uint32_t m_RendererID;
    GLenum m_InternalFormat, m_DataFormat;
};

}  // namespace ARcane
