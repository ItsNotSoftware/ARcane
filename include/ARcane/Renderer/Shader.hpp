#pragma once

#include "ARcane/Core/Core.hpp"

#include <glad/glad.h>
#include <glm/glm.hpp>

namespace ARcane {

class Shader {
   public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    Shader(const std::string& filepath);
    ~Shader();

    void Bind() const;
    void Unbind() const;

    void SetInt(const std::string& name, int value);
    void SetIntArray(const std::string& name, int* values, uint32_t count);
    void SetFloat(const std::string& name, float value);

    void SetFloat2(const std::string& name, const glm::vec2& vector);
    void SetFloat3(const std::string& name, const glm::vec3& vector);
    void SetFloat4(const std::string& name, const glm::vec4& vector);

    void SetMat3(const std::string& name, const glm::mat3& matrix);
    void SetMat4(const std::string& name, const glm::mat4& matrix);

   private:
    std::string ReadFile(const std::string& filepath);
    std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
    void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

    uint32_t m_RendererID;
};

};  // namespace ARcane