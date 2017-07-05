#include "widget.h"
#include <QApplication>
#include <QAxObject>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QAxObject excel("Excel.Application");
    excel.setProperty("Visible", false);
    QAxObject *work_books = excel.querySubObject("WorkBooks");
    work_books->dynamicCall("Open (const QString&)", QString("D:/panjiafu/mydata/wish张凤莲38497Z2017-6.xls"));
    QVariant title_value = excel.property("Caption");  //获取标题
    qDebug()<<QString("excel title : ")<<title_value.toString();
    QAxObject *work_book = excel.querySubObject("ActiveWorkBook");
    QAxObject *work_sheets = work_book->querySubObject("Sheets");  //Sheets也可换用WorkSheets

    int sheet_count = work_sheets->property("Count").toInt();  //获取工作表数目
    qDebug()<<QString("sheet count : ")<<sheet_count;
    for(int i=1; i<=sheet_count; i++)
    {
        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", i);  //Sheets(int)也可换用Worksheets(int)
        QString work_sheet_name = work_sheet->property("Name").toString();  //获取工作表名称
        QString message = QString("sheet ")+QString::number(i, 10)+ QString(" name");
        qDebug()<<message<<work_sheet_name;
    }
    for(int i = 1;i<sheet_count;i++)
    {
        QAxObject *work_sheet = work_book->querySubObject("Sheets(int)", i);
        QAxObject *used_range = work_sheet->querySubObject("UsedRange");
        QAxObject *rows = used_range->querySubObject("Rows");
        QAxObject *columns = used_range->querySubObject("Columns");
        int row_start = used_range->property("Row").toInt();  //获取起始行
        int column_start = used_range->property("Column").toInt();  //获取起始列
        int row_count = rows->property("Count").toInt();  //获取行数
        int column_count = columns->property("Count").toInt();  //获取列数
        for(int i=row_start; i<row_count;i++)
        {
            for(int j=column_start; j<column_count;j++)
            {
                QAxObject *cell = work_sheet->querySubObject("Cells(int,int)", i, j);
                QVariant cell_value = cell->property("Value");  //获取单元格内容
                QString message = QString("row-")+QString::number(i, 10)+QString("-column-")+QString::number(j, 10)+QString(":");
                qDebug()<<message<<cell_value.toString();
            }
        }
    }

    //Widget w;
    //w.show();

    return a.exec();
}
