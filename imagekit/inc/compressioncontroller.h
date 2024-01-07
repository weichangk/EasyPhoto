/*
 * @Author: weick
 * @Date: 2024-01-07 23:43:32
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-07 23:48:44
 */

#pragma once

#pragma once
#include "compressionwindow.h"
#include "compressionwindow.h"
#include <QWidget>

class CompressionController : public QObject {
    Q_OBJECT
public:
    explicit CompressionController();
    ~CompressionController();
    void showWindow();
    void closeWindow();

private:
    void sigConnect();

private:
    CompressionWindow *m_CompressionWindow = 0;
};
