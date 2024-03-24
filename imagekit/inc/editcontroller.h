/*
 * @Author: weick
 * @Date: 2024-03-23 10:48:38
 * @Last Modified by: weick
 * @Last Modified time: 2024-03-23 10:59:31
 */

#pragma once
#include <QWidget>

namespace imageedit {
class EditController : public QObject {
    Q_OBJECT
public:
    explicit EditController();
    ~EditController();
};
} // namespace imageedit