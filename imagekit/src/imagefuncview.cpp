#include "inc/imagefuncview.h"

ImageFuncView::ImageFuncView(QWidget *parent) : QListView(parent)
{
}

void ImageFuncView::changeModel(const QList<ImageFunc> &datas)
{
    m_Model->changeData(datas);
}

void ImageFuncView::changeModel(int row, const ImageFunc &data)
{
    m_Model->changeData(row, data);
}

void ImageFuncView::addModel(QList<ImageFunc> &datas)
{
    m_Model->addData(datas);
}

ImageFunc ImageFuncView::model(int row) const
{
    // return m_Model->data(m_Model., Qt::UserRole);
    return ImageFunc();
}

int ImageFuncView::rowCount() const
{
    return m_Model->rowCount();
}

void ImageFuncView::mouseMoveEvent(QMouseEvent *e)
{

}

void ImageFuncView::currentChanged(const QModelIndex &current, const QModelIndex &previous)
{

}
