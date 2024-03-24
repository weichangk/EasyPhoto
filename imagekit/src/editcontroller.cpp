/*
 * @Author: weick
 * @Date: 2024-03-23 10:53:08
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 12:46:23
 */

#include "inc/editcontroller.h"

namespace imageedit {
EditController::EditController() {
    init();
    sigConnect();
}

EditController::~EditController() {
}

void EditController::showWindow() {
    window_->show();
}

void EditController::closeWindow() {
    window_->close();
}

void EditController::init() {
    window_ = new EditWindow;
}

void EditController::sigConnect() {

}
} // namespace imageedit