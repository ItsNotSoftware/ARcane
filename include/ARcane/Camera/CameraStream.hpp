#pragma once

#include "ARcane/Core/Core.hpp"
#include "ARcane/Camera/Camera.hpp"
#include <opencv2/opencv.hpp>
#include <zmq.hpp>
#include <thread>
#include <atomic>
#include <mutex>
#include <string>

namespace ARcane {

class CameraStream : public Camera {
   public:
    CameraStream(const glm::mat4& projection);
    virtual ~CameraStream();

    Camera& GetCamera() { return *this; }

    void StartSubscriberThread(const std::string& url);

    cv::Mat GetFrame() const;

   private:
    void SubscriberLoop();

    cv::Mat m_Frame;
    mutable std::mutex m_FrameMutex;

    std::atomic_bool m_Running;
    std::thread m_SubscriberThread;
    zmq::context_t m_Context;
    zmq::socket_t m_Subscriber;
};

}  // namespace ARcane
