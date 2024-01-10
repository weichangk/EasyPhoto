/*
 * @Author: weick
 * @Date: 2024-01-08 23:00:05
 * @Last Modified by: weick
 * @Last Modified time: 2024-01-09 00:13:49
 */

#pragma once
#include "agui_global.h"
#include "abasewidget.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>

class AGUI_EXPORT ARotatingPixmapItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)

public:
    explicit ARotatingPixmapItem(const QPixmap &pixmap, QGraphicsItem *parent = nullptr);
    void start();
    void stop();

private:
    QPropertyAnimation *m_RotationAnimation = 0;
};

class AGUI_EXPORT AWidgetWithRotatingItem : public ABaseWidget {
    Q_OBJECT
public:
    explicit AWidgetWithRotatingItem(QPixmap pixmap, QWidget *parent = nullptr);
    explicit AWidgetWithRotatingItem(QWidget *parent = nullptr);
    void start();
    void stop();

private:
    ARotatingPixmapItem *m_RotatingPixmapItem = 0;
};
