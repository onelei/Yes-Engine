//
// Created by onelei on 2024/2/29.
//

#include "GameObject.h"

namespace DivineBrush {
    std::string GameObject::kTagMainCamera = "MainCamera";

    GameObject::GameObject(const char *name) {
        this->SetName(name);
        // 添加Transform组件
        AddComponent<Transform>();
        transform = this->GetComponent<Transform>();
        // 添加到根节点
        GetRootNode()->AddChild(this);
    }

    GameObject::~GameObject() {
        //DEBUG_LOG_INFO("GameObject::~GameObject");
    }

    Component *GameObject::AddComponent(const std::string &componentName) {
        type t = type::get_by_name(componentName);
        variant var = t.create();
        Component *component = var.get_value<Component *>();
        component->SetGameObject(this);
        if (component_map.find(componentName) == component_map.end()) {
            std::vector<Component *> componentVec;
            componentVec.push_back(component);
            component_map[componentName] = componentVec;
        } else {
            component_map[componentName].push_back(component);
        }
        component->OnAwake();
        return component;
    }

    Component *GameObject::AddComponentByLua(std::string componentName, Component *component) {
        if (component == nullptr) {
            return nullptr;
        }
        component->SetGameObject(this);
        if (component_map.find(componentName) == component_map.end()) {
            std::vector<Component *> componentVec;
            componentVec.push_back(component);
            component_map[componentName] = componentVec;
        } else {
            component_map[componentName].push_back(component);
        }
        //component->OnAwake();
        return component;
    }

    Component *GameObject::GetComponent(const std::string &componentName) {
        if (component_map.find(componentName) != component_map.end()) {
            return component_map[componentName][0];
        }
        return nullptr;
    }

    void GameObject::RenderAll() {
        //剔除不需要渲染的物体
        ForeachGameObject([](GameObject *gameObject) {
            if (!gameObject->IsActive()) {
                return;
            }
            auto mesh_render = gameObject->GetComponent<MeshRenderer>();
            if (!mesh_render) {
                return;
            }
            mesh_render->Render();
        });
    }

    void GameObject::UpdateAll() {
        ForeachGameObject([](GameObject *gameObject) {
            if (!gameObject->IsActive()) {
                return;
            }
            gameObject->ForeachComponent([](Component *component) {
                component->OnUpdate();
            });
        });
    }

    void GameObject::FixUpdateAll() {
        ForeachGameObject([](GameObject *gameObject) {
            if (!gameObject->IsActive()) {
                return;
            }
            gameObject->ForeachComponent([](Component *component) {
                component->OnFixUpdate();
            });
        });
    }

    void GameObject::ForeachComponent(std::function<void(Component *)> func) {
        for (auto &v: component_map) {
            for (auto &component: v.second) {
                func(component);
            }
        }
    }

    void GameObject::ForeachGameObject(std::function<void(GameObject *)> func) {
        Foreach(GetRootNode(), [&func](Node *node) {
            auto gameObject = dynamic_cast<GameObject *>(node);
            func(gameObject);
        });
    }

    GameObject *GameObject::Find(std::string gameObject_name) {
        GameObject *result = nullptr;
        Node::Find(GetRootNode(), [&gameObject_name](Node *node) {
            auto gameObject = dynamic_cast<GameObject *>(node);
            return (gameObject->GetName() == gameObject_name);
        }, reinterpret_cast<Node **>(&result));
        return result;
    }


} // DivineBrush