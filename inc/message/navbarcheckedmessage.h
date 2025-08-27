#pragma once

#include "mvp/message.h"

using namespace QtmMvp;

class NavbarCheckedMessage : public Message {
public:
    explicit NavbarCheckedMessage(const MessageCode code);
    ~NavbarCheckedMessage();
};