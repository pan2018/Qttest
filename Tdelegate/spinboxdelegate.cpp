#include "spinboxdelegate.h"
#include <QDebug>
SpinBoxDelegate::SpinBoxDelegate(QObject *parent):QItemDelegate(parent)
{
    list = new QStringList();
    //connect(parent,SIGNAL(showlistdate()),this,SLOT(showDate()));//对应发送方是父窗口
    //connect(this,SIGNAL(showlistdate()),this,SLOT(showDate()));//对应的发方是 delegate
}
//返回一个编辑控件，用来编辑指定项的数据
QWidget *SpinBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                       const QModelIndex &index) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);
    return editor;
}
// 将Model中数据赋值到控件上
void SpinBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    int value = index.model()->data(index,Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}
//将控件数据赋值到model上
void SpinBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();
    QString value = spinBox->text();

    model->setData(index,value,Qt::EditRole);
    list->append(value);
    qDebug()<<list->count()<<value<<index.column()<<index.row()<<list->indexOf("55");

    //判断链表中是否已添加了该行数据，如果没有则根据行号,填入不重复项数据和修改数据，如果有则将修改项赋值到已有项(此处不会保存到数据库，
    //需要点击提交才会将整个链表更新到数据库中。)
      //QModelIndex transposedIndex = createIndex(index.column(),2);
}

void SpinBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

void SpinBoxDelegate::showDate()
{
    qDebug()<<"hello"<<QObject::sender()->objectName();
    for(int i = 0;i<list->count();i++){
        qDebug()<<list->at(i);
    }
}
