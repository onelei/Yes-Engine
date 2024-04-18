//
// Created by onelei on 2024/4/10.
//

#ifndef ENGINE_RENDERPIPELINE_H
#define ENGINE_RENDERPIPELINE_H

#include <thread>
#include "Handler/RenderCommandHandler.h"
//#include "../../depends/template/RingBuffer.h"
#include "RenderProgramGenerater.h"
#include "../../depends/template/Singleton.h"
#include <GLFW/glfw3.h>
#include "rigtorp/SPSCQueue.h"

namespace DivineBrush {

    class RenderPipeline : public Singleton<RenderPipeline> {
        /// 确保SingletonTemplate可以访问MyClass的构造函数
        friend class Singleton<RenderPipeline>;

    protected:
        ~RenderPipeline() override;

    public:
        void Init(GLFWwindow *window);

        void Dispose();

        GLuint GetColorTextureId() const {
            return color_texture_id;
        }

        GLuint GetDepthTextureId() const {
            return depth_texture_id;
        }

        RenderProgramGenerater *GetRenderProgramGenerater() {
            return renderProgramGenerater;
        }

        void AddRenderCommandHandler(RenderCommandHandler *handler) {
            ringBuffer.push(handler);
        }

        RenderPipeline();

    private:
        void Start();

        void Prepare();

        GLFWwindow *window = nullptr;
        bool isDispose = false;
        ///FBO 颜色纹理
        GLuint color_texture_id = 0;
        ///FBO 深度纹理
        GLuint depth_texture_id = 0;
        std::thread renderThread;
        rigtorp::SPSCQueue<RenderCommandHandler*> ringBuffer = rigtorp::SPSCQueue<RenderCommandHandler *>(1024);
        RenderProgramGenerater *renderProgramGenerater = nullptr;
    };

} // DivineBrush

#endif //ENGINE_RENDERPIPELINE_H