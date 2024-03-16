//
// Created by onelei on 2024/3/5.
//

#ifndef ENGINE_GAME_WINDOW_H
#define ENGINE_GAME_WINDOW_H

#include <imgui.h>
#include "../editor_window.h"

namespace DivineBrush::Editor {
    class EditorWindow;
}

namespace DivineBrush::Editor {

    class GameWindow : public EditorWindow {
    public:
        GameWindow();

        ~GameWindow();

        void OnGUI() override;

    private:
        ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    };
} // DivineBrush

#endif //ENGINE_GAME_WINDOW_H