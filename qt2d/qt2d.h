#ifndef QT2D_H
#define QT2D_H
//坐标系类
#include <QWidget>
#include <QImage>
#include <QPainter>
namespace Ui {
class qt2d;
}

class qt2d : public QWidget
{
    Q_OBJECT

public:
    explicit qt2d(QWidget *parent = 0);
    /*功能:用户输入数据链表，传入画布，如果画布不存在就新建，如果画布存在就在原有画布上绘制。
     * 根据传入的数据确定坐标轴的比例，实时更新其他绘制图形。
     * 绘图画布:
     * 绘图数据链表:
     */
    ~qt2d();
    void Paint();//绘制坐标系
    void Paint_zx();//绘制折线

protected:
    void paintEvent(QPaintEvent * event);
public slots:
private:
    Ui::qt2d *ui;
    QImage image;
    QPainter *painter;
};

#endif // QT2D_H
