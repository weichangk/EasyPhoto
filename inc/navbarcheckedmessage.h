#pragma once

#include "mvp/message.h"

using namespace qtmaterialmvp;

class NavbarCheckedMessage : public Message {
public:
    explicit NavbarCheckedMessage(const MessageCode code);
    ~NavbarCheckedMessage();
};