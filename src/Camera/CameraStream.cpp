#include "ARcane/Camera/CameraStream.hpp"
#include <opencv2/imgcodecs.hpp>

namespace ARcane {

CameraStream::CameraStream(const glm::mat4& projection)
    : Camera(projection), m_Running(false), m_Context(1), m_Subscriber(m_Context, ZMQ_SUB) {}

CameraStream::~CameraStream() {
    // Signal the subscriber thread to stop and join it
    m_Running = false;
    if (m_SubscriberThread.joinable()) {
        m_SubscriberThread.join();
    }
    m_Subscriber.close();
    m_Context.close();
}

void CameraStream::StartSubscriberThread(const std::string& url) {
    // Connect to the publisher URL and subscribe to all messages
    m_Subscriber.connect(url);
    m_Subscriber.set(zmq::sockopt::subscribe, "");

    m_Running = true;
    m_SubscriberThread = std::thread(&CameraStream::SubscriberLoop, this);
}

void CameraStream::SubscriberLoop() {
    while (m_Running) {
        zmq::message_t message;
        try {
            // Blocking call to receive the next frame
            if (m_Subscriber.recv(message, zmq::recv_flags::none)) {
                // Convert the received data into a std::vector
                std::vector<uchar> buffer(static_cast<uchar*>(message.data()),
                                          static_cast<uchar*>(message.data()) + message.size());
                // Decode the JPEG buffer into an OpenCV Mat
                cv::Mat frame = cv::imdecode(buffer, cv::IMREAD_COLOR);
                if (!frame.empty()) {
                    // Lock and update the frame atomically
                    std::lock_guard<std::mutex> lock(m_FrameMutex);
                    m_Frame = frame;
                }
            }
        } catch (const zmq::error_t& e) {
            ARC_CORE_ERROR("ZMQ Error: {}", (const char*)e.what());
        }
    }
}

cv::Mat CameraStream::GetFrame() const {
    // Return a clone of the current frame to ensure thread safety
    std::lock_guard<std::mutex> lock(m_FrameMutex);
    return m_Frame.clone();
}

}  // namespace ARcane
