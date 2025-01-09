#pragma once

#include "mvp/message.h"

using namespace qtmaterialmvp;

class NavChangeMessage : public Message {
public:
    explicit NavChangeMessage(const MessageCode code);
    ~NavChangeMessage();
};