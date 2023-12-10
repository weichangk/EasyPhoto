/*
 * @Author: weick
 * @Date: 2023-12-10 22:25:46
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-10 23:35:27
 */

#pragma once
#include <QObject>
#include <QString>

class ConversionData : public QObject {
    Q_OBJECT
public:
    enum ConversionType {
        None = 0,
        Run,
        Success,
        Fail
    };
    Q_ENUM(ConversionType)

    explicit ConversionData();

private:
    QString m_Name;
    QString m_Infmt;
    QString m_Outfmt;
    ConversionType m_ConversionType = ConversionType::None;
};

ConversionData::ConversionData(){

}
