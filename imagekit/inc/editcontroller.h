/*
 * @Author: weick
 * @Date: 2024-03-23 10:48:38
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-24 12:46:05
 */

#pragma once
#include "editwindow.h"
#include <QWidget>

namespace imageedit {
class EditController : public QObject {
    Q_OBJECT
public:
    explicit EditController();
    ~EditController();
    void showWindow();
    void closeWindow();

private:
    void init();
    void sigConnect();
    
private:
    EditWindow *window_;
};
} // namespace imageedit