#include "widget.h"
#include "spinboxdelegate.h"
#include "ui_widget.h"
#include <QItemSelectionModel>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QTableView>
#include <QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    //构建一个4行，2列的项模型
    QStandardItemModel *model = new QStandardItemModel(ui->tableView);
    //声明一个TableView
    //QTableView tableView(this);
    //绑定模型

    //声明一个委托
    SpinBoxDelegate *delegate = new SpinBoxDelegate(this);
    delegate->setObjectName("panj");
    //设定视图的委托
    ui->tableView->setItemDelegate(delegate);
    //ensuring that the view does not waste any of the space assigned to it for its header
    //最后一列全部填充View
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    //初始化Model
    model->setHorizontalHeaderLabels(QStringList()<<"sku"<<"数量"<<"名称");
    for (int row = 0; row < 4; ++row) {
        QStandardItem* itemProject = new QStandardItem("22");
        model->appendRow(itemProject);
        model->setItem(model->indexFromItem(itemProject).row(),1,new QStandardItem("55"));
        model->setItem(model->indexFromItem(itemProject).row(),2,new QStandardItem("44"));
    }
    ui->tableView->setModel(model);
    this->setWindowTitle(QObject::tr("Spin Box Delegate"));
    //QCoreApplication::processEvents(QEventLoop::AllEvents, 100);//不使用此函数就不会刷新

    // connect(ui->pushButton,SIGNAL(clicked()),delegate,SIGNAL(showlistdate()));//接收方应该是this，如果直接写delegate是接收不到的。
    connect(ui->pushButton,SIGNAL(clicked()),delegate,SLOT(showDate()));//直接调用接受者槽函数，不用父窗口转发
    //connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(showhello()));

}

Widget::~Widget()
{
    delete ui;
}

void Widget::showhello()
{
    qDebug()<<"send";
    //emit showlistdate();
}
