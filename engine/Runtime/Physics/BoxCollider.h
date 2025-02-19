﻿//
// Created by onelei on 2024/4/28.
//

#ifndef ENGINE_BOXCOLLIDER_H
#define ENGINE_BOXCOLLIDER_H

#include <glm/glm.hpp>
#include "Collider.h"

namespace DivineBrush {

    class BoxCollider : public Collider {
    public:
        BoxCollider();

        ~BoxCollider();

        void SetSize(glm::vec3 size);

        glm::vec3 GetSize();

    protected:
        void CreatePxShape() override;

    private:
        glm::vec3 size = glm::vec3(1, 1, 1);
    RTTR_ENABLE(Collider);
    };

} // DivineBrush

#endif //ENGINE_BOXCOLLIDER_H
