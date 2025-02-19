//
// Created by onelei on 2024/3/8.
//

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <iostream>
#include <unordered_map>

namespace DivineBrush {
    class Shader {
    public:
        Shader();

        ~Shader();

        void Parse(const std::string &shaderName);

        void CreateProgram(const char *vertex_shader_text, const char *fragment_shader_text);

        void Use() const;

        unsigned int GetProgramHandle() const { return shaderProgramHandle; }

        static Shader *Find(const std::string &shaderName);

    public:
        std::string shader_name;

    private:
        unsigned int shaderProgramHandle = 0;
        static std::unordered_map<std::string, Shader *> shader_map;
    };
} // DivineBrush

#endif //ENGINE_SHADER_H
