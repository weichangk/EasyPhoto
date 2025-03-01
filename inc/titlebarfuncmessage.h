#pragma once

#include "mvp/message.h"

using namespace qtmaterialmvp;

class TitlebarFuncMessage : public Message {
public:
    explicit TitlebarFuncMessage(const MessageCode code);
    ~TitlebarFuncMessage();
};