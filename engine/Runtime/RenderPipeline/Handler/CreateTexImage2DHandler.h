//
// Created by onelei on 2024/4/11.
//

#ifndef ENGINE_CREATETEXIMAGE2DHANDLER_H
#define ENGINE_CREATETEXIMAGE2DHANDLER_H

#include "RenderCommandHandler.h"
#include "cstdlib"

namespace DivineBrush {

    class CreateTexImage2DHandler : public RenderCommandHandler {
    public:
        CreateTexImage2DHandler();

        ~CreateTexImage2DHandler();

        unsigned int textureHandle = 0;
        int width = 0;
        int height = 0;
        unsigned int internalformat = 0;
        unsigned int format = 0;
        unsigned int dataType = 0;
        unsigned char *data = nullptr;

        void Run() override;

        void Clear() override;
    };

} // DivineBrush

#endif //ENGINE_CREATETEXIMAGE2DHANDLER_H
