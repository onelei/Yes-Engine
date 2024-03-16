//
// Created by onelei on 2024/3/14.
//

#include "material.h"
#include <rapidxml/rapidxml.hpp>
#include "rapidxml/rapidxml_utils.hpp"
#include "../application.h"
#include <string>

namespace DivineBrush {
    void Material::Parse(const std::string &materialPath) {
        //解析xml
        rapidxml::file<> xml_file((Application::GetDataPath() + materialPath).c_str());
        rapidxml::xml_document<> document;
        document.parse<0>(xml_file.data());
        //根节点
        rapidxml::xml_node<> *material_node = document.first_node("material");
        if (material_node == nullptr) {
            return;
        }
        rapidxml::xml_attribute<> *material_shader_attribute = material_node->first_attribute("shader");
        if (material_shader_attribute == nullptr) {
            return;
        }
        shader = Shader::Find(material_shader_attribute->value());
        //解析Texture
        rapidxml::xml_node<> *material_texture_node = material_node->first_node("texture");
        while (material_texture_node != nullptr) {
            rapidxml::xml_attribute<> *texture_name_attribute = material_texture_node->first_attribute("name");
            if (texture_name_attribute == nullptr) {
                return;
            }
            rapidxml::xml_attribute<> *texture_image_attribute = material_texture_node->first_attribute("image");
            if (texture_image_attribute == nullptr) {
                return;
            }
            std::string shader_property_name = texture_name_attribute->value();
            std::string image_path = texture_image_attribute->value();
            textures.emplace_back(texture_name_attribute->value(), Texture2d::LoadCompressFile(image_path));
            material_texture_node = material_texture_node->next_sibling("texture");
        }
    }

    void Material::SetUniformMatrix4fv(const std::string &shaderPropertyName, float *pointer) {
        uniform_matrix4fv_vec.emplace_back(shaderPropertyName, pointer);
    }

    void Material::SetUniform1i(const std::string &shaderPropertyName, int value) {
        uniform_1i_vec.emplace_back(shaderPropertyName, value);
    }
} // DivineBrush