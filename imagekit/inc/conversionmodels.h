/*
 * @Author: weick
 * @Date: 2023-12-10 22:25:46
 * @Last Modified by: weick
 * @Last Modified time: 2023-12-14 00:02:40
 */

#pragma once
#include <QObject>
#include <QString>

class ConversionModels : public QObject {
    Q_OBJECT
public:
    enum ConversionType {
        None = 0,
        Run,
        Success,
        Fail
    };
    Q_ENUM(ConversionType)
};

struct ConversionData {
    QString m_Name;
    QString m_Infmt;
    QString m_Outfmt;
    ConversionModels::ConversionType m_ConversionType = ConversionModels::ConversionType::None;
};
Q_DECLARE_METATYPE(ConversionData)
