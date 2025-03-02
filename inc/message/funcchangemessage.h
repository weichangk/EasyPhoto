#pragma once

#include "mvp/message.h"

using namespace qtmaterialmvp;

class FuncChangeMessage : public Message {
public:
    explicit FuncChangeMessage(const MessageCode code);
    ~FuncChangeMessage();
};