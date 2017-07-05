#include "currencymodel.h"
#include <QtCore>
CurrencyModel::CurrencyModel(QObject *parent):QAbstractTableModel(parent)
{

}

int CurrencyModel::rowCount(const QModelIndex &parent) const{
    return currencyMap.count();
}

int CurrencyModel::columnCount(const QModelIndex &parent) const{
    return currencyMap.count();
}

QVariant CurrencyModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid()){
        return QVariant();
    }
    if(role == Qt::TextAlignmentRole){
        return int(Qt::AlignRight|Qt::AlignVCenter);
    }else if(role == Qt::DisplayRole){
        QString rowCurrency = currencyAt(index.row());
        QString columnCurrency = currencyAt(index.column());

        if(currencyMap.value(rowCurrency) == 0.0){
            return "####";
        }
        double amount = currencyMap.value(columnCurrency)/currencyMap.value(rowCurrency);
        return QString("%1").arg(amount,0,'f',4);
    }
    return QVariant();
}

QVariant CurrencyModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if(role!=Qt::DisplayRole)
        return QVariant();
    return currencyAt(section);
}
void CurrencyModel::setCurrencyMap(const QMap<QString, double> &map)
{
    beginResetModel();
    currencyMap = map;
    //reset();//该函数会提示任何使用这个模型的视图刷新显示项,但是在qt5中已经废弃，使用上面的的begin和end函数代替
    endResetModel();
}

QString CurrencyModel::currencyAt(int offset) const{
    return (currencyMap.begin() + offset).key();
}


