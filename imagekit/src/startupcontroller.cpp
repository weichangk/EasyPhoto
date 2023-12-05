/*
 * @Author: weick
 * @Date: 2023-12-05 23:03:58
 * @Last Modified by:   weick
 * @Last Modified time: 2023-12-05 23:03:58
 */

#include "inc/startupcontroller.h"
#include "inc/startupwindow.h"
#include "inc/imagefunc.h"

StartupController::StartupController() {
    m_StartupWindow = new StartupWindow();
    initImageFunc();
}

StartupController::~StartupController() {
    delete m_StartupWindow;
}

void StartupController::show() {
    m_StartupWindow->show();
}

void StartupController::initImageFunc() {
    QList<ImageFunc *> imageFuncs;
    QString name = "图片转换";
    QString desc = "图片jpg、jpeg、png、gif等多种格式转换";
    QPixmap icon;
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图片裁剪";
    desc = "图片尺寸裁剪";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图片效果";
    desc = "图片亮度、对比度、饱和度修改";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图片擦除";
    desc = "图片擦除";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图片水印";
    desc = "图片添加水印";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图片抠像";
    desc = "图片抠像";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图像超分";
    desc = "图像超分";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图像增强";
    desc = "图像增强";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图像放大";
    desc = "图像放大";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "图像复原";
    desc = "图像复原";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    name = "AI生图";
    desc = "AI生图";
    icon = QPixmap(":/res/image/icon40_image_converter.png");
    imageFuncs.append(new ImageFunc(name, desc, icon));
    m_StartupWindow->imageFuncModelAppend(imageFuncs);
}
