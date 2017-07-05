//自定义模型 使用汇率，只读模型
#ifndef CURRENCYMODEL_H
#define CURRENCYMODEL_H
#include <QAbstractTableModel>
#include <QMap>
#include <QString>
#include <QVariant>

class CurrencyModel : public QAbstractTableModel
{
public:
    CurrencyModel(QObject *parent = 0);
    //对于只读表模型，必须实现如下三个函数
    void setCurrencyMap(const QMap<QString,double> &map);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index,int role) const;
    QVariant headerData(int section,Qt::Orientation orientation,int role)const;

private:
    QString currencyAt(int offset) const;
    QMap<QString ,double> currencyMap;
};

#endif // CURRENCYMODEL_H
