#include "ARcane/Renderer/Texture.hpp"

#include "stb/stb_image.h"

namespace ARcane {

Texture2D::Texture2D(uint32_t width, uint32_t height)
    : m_Width(width), m_Height(height), m_InternalFormat(GL_RGBA), m_DataFormat(GL_RGBA) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, GL_RGBA8, m_Width, m_Height);
    // Set texture parameters
    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Texture2D::Texture2D(const std::string& path) : m_Path(path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);

    // Load image
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    ARC_CORE_ASSERT(data, "Failed to load image!");
    m_Width = width;
    m_Height = height;

    // Determine image format
    GLenum internalFormat = 0, dataFormat = 0;
    if (channels == 4) {
        internalFormat = GL_RGBA8;  // 8 bits per channel rgba (OpenGL)
        dataFormat = GL_RGBA;       // 8 bits per channel rgba (image)
    } else if (channels == 3) {
        internalFormat = GL_RGB8;  // 8 bits per channel rgb (OpenGL)
        dataFormat = GL_RGB;       // 8 bits per channel rgb (image)
    }

    m_InternalFormat = internalFormat;
    m_DataFormat = dataFormat;

    ARC_CORE_ASSERT(internalFormat & dataFormat, "Image format not supported!");

    // Create and store texture
    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

    // Set texture parameters
    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Upload image data to GPU
    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE,
                        data);

    // Free image data from CPU
    stbi_image_free(data);
}

Texture2D::~Texture2D() { glDeleteTextures(1, &m_RendererID); }

void Texture2D::Bind(uint32_t slot) const { glBindTextureUnit(slot, m_RendererID); }

void Texture2D::SetData(void* data, uint32_t) {
    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE,
                        data);
}

}  // namespace ARcane
