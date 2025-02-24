#include "ARcane/Renderer/Shader.hpp"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace ARcane {

static GLenum ShaderTypeFromString(const std::string &type) {
    if (type == "vertex") return GL_VERTEX_SHADER;
    if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

    ARC_CORE_ASSERT(false, "Unknown shader type!");
    return 0;
}

Shader::Shader(const std::string &filepath) {
    std::string source = ReadFile(filepath);
    auto shaderSources = PreProcess(source);
    Compile(shaderSources);
}

Shader::Shader(const std::string &vertexSrc, const std::string &fragmentSrc) {
    std::unordered_map<GLenum, std::string> sources;
    sources[GL_VERTEX_SHADER] = vertexSrc;
    sources[GL_FRAGMENT_SHADER] = fragmentSrc;
    Compile(sources);
}

Shader::~Shader() { glDeleteProgram(m_RendererID); }
std::string Shader::ReadFile(const std::string &filepath) {
    std::string result;
    std::ifstream in(filepath, std::ios::in | std::ios::binary);

    if (in) {
        in.seekg(0, std::ios::end);          // Seek to the end of the file
        result.resize(in.tellg());           // Get the length of the file
        in.seekg(0, std::ios::beg);          // Seek back to the beginning
        in.read(&result[0], result.size());  // Read the file into the string
        in.close();
    } else {
        ARC_CORE_ERROR("Could not open file '{0}'", filepath);
    }

    return result;
}

std::unordered_map<GLenum, std::string> Shader::PreProcess(const std::string &source) {
    std::unordered_map<GLenum, std::string> shaderSources;

    const char *typeToken = "#type";
    size_t typeTokenLength = strlen(typeToken);
    size_t pos = source.find(typeToken, 0);

    while (pos != std::string::npos) {
        // Find the end of the line where "#type" is found
        size_t eol = source.find_first_of("\r\n", pos);
        ARC_CORE_ASSERT(eol != std::string::npos, "Syntax error");  // Ensure valid syntax

        // Extract the shader type keyword from the line
        size_t begin = pos + typeTokenLength + 1;
        std::string type = source.substr(begin, eol - begin);

        // Ensure the shader type is valid
        ARC_CORE_ASSERT(type == "vertex" || type == "fragment" || type == "pixel",
                        "Invalid shader type specified");

        // Find the start of the next line after the type declaration
        size_t nextLinePos = source.find_first_not_of("\r\n", eol);

        // Find the next occurrence of "#type" to determine the bounds of the shader source
        pos = source.find(typeToken, nextLinePos);

        // Store the extracted shader source in the map, associating it with GLenum
        shaderSources[ShaderTypeFromString(type)] = source.substr(
            nextLinePos,
            pos - (nextLinePos == std::string::npos ? source.size() - 1 : nextLinePos));
    }

    return shaderSources;
}

void Shader::Compile(const std::unordered_map<GLenum, std::string> &shaderSources) {
    GLuint program = glCreateProgram();
    std::vector<GLuint> glShaderIDs(shaderSources.size());

    for (auto &&kv : shaderSources) {
        GLenum type = kv.first;
        const std::string &source = kv.second;

        GLuint shader = glCreateShader(type);

        const GLchar *sourceCStr = source.c_str();
        glShaderSource(shader, 1, &sourceCStr, 0);

        glCompileShader(shader);

        GLint isCompiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE) {
            GLint maxLength = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

            glDeleteShader(shader);

            ARC_CORE_ERROR("{0}", infoLog.data());
            ARC_CORE_ASSERT(false, "Shader compilation failure!");
            break;
        }

        glAttachShader(program, shader);
        glShaderIDs.push_back(shader);
    }

    // Link our program
    glLinkProgram(program);

    GLint isLinked = 0;
    glGetProgramiv(program, GL_LINK_STATUS, (int *)&isLinked);
    if (isLinked == GL_FALSE) {
        GLint maxLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

        std::vector<GLchar> infoLog(maxLength);
        glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

        glDeleteProgram(program);

        for (auto id : glShaderIDs) {
            glDeleteShader(id);
        }

        ARC_CORE_ERROR("{0}", infoLog.data());
        ARC_CORE_ASSERT(false, "Shader link failure!");
        return;
    }

    for (auto id : glShaderIDs) {
        glDetachShader(program, id);
        glDeleteShader(id);
    }

    m_RendererID = program;
}

void Shader::Bind() const { glUseProgram(m_RendererID); }

void Shader::Unbind() const { glUseProgram(0); }

void Shader::SetInt(const std::string &name, int value) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1i(location, value);
}

void Shader::SetIntArray(const std::string &name, int *values, uint32_t count) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1iv(location, count, values);
}

void Shader::SetFloat(const std::string &name, float value) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform1f(location, value);
}

void Shader::SetFloat2(const std::string &name, const glm::vec2 &vector) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform2f(location, vector.x, vector.y);
}

void Shader::SetFloat3(const std::string &name, const glm::vec3 &vector) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform3f(location, vector.x, vector.y, vector.z);
}

void Shader::SetFloat4(const std::string &name, const glm::vec4 &vector) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniform4f(location, vector.r, vector.g, vector.b, vector.a);
}

void Shader::SetMat3(const std::string &name, const glm::mat3 &matrix) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::SetMat4(const std::string &name, const glm::mat4 &matrix) {
    GLint location = glGetUniformLocation(m_RendererID, name.c_str());
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
}

};  // namespace ARcane