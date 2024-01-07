/*
 * @Author: weick
 * @Date: 2024-01-07 23:46:03
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-07 23:46:51
 */

/*
 * @Author: weick
 * @Date: 2023-12-21 23:57:42
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-21 23:59:21
 */

#include "inc/compressioncontroller.h"

CompressionController::CompressionController() {
    m_CompressionWindow = new CompressionWindow;
    sigConnect();
}

CompressionController::~CompressionController() {
}

void CompressionController::showWindow() {
    m_CompressionWindow->show();
}

void CompressionController::closeWindow() {
    m_CompressionWindow->close();
}

void CompressionController::sigConnect() {
}
