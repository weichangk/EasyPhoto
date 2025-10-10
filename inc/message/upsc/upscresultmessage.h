#pragma once

#include "mvp/message.h"
#include "upsc/types.h"

class UpscResultMessage : public QtmMvp::Message {
public:
    explicit UpscResultMessage(const std::vector<EasyPhotoCore::Upsc::SResult> results,
                               const QtmMvp::MessageCode code = 0);
    ~UpscResultMessage();

    std::vector<EasyPhotoCore::Upsc::SResult> Results() const;

private:
    std::vector<EasyPhotoCore::Upsc::SResult> m_Results;
};