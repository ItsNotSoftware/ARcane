#include "ARcane/Renderer/Texture.hpp"

#include <glad/glad.h>
#include "ARcane/stb/stb_image.h"

namespace ARcane {

Texture2D::Texture2D(const std::string& path) : m_Path(path) {
    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);

    // Load image
    stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
    ARC_CORE_ASSERT(data, "Failed to load image!");
    m_Width = width;
    m_Height = height;

    // Create and store texture
    glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
    glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

    // Set texture parameters
    glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Upload image data to GPU
    glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, GL_RGB, GL_UNSIGNED_BYTE, data);

    // Free image data from CPU
    stbi_image_free(data);
}

Texture2D::~Texture2D() { glDeleteTextures(1, &m_RendererID); }

void Texture2D::Bind(uint32_t slot) const { glBindTextureUnit(slot, m_RendererID); }

}  // namespace ARcane
