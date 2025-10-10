#include "message/upsc/upscresultmessage.h"

UpscResultMessage::UpscResultMessage(const std::vector<EasyPhotoCore::Upsc::SResult> results,
                                     const QtmMvp::MessageCode code) :
    Message(code), m_Results(results) {
}

UpscResultMessage::~UpscResultMessage() {
}

std::vector<EasyPhotoCore::Upsc::SResult> UpscResultMessage::Results() const {
    return m_Results;
}