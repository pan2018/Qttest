/*坐标系类型绘图类。
 *传入绘图设备和数据链表后即可绘制图形。
 */

#ifndef PCOORDINATE_H
#define PCOORDINATE_H

#include <QWidget>

class PCoordinate : public QWidget
{
    Q_OBJECT
public:
    explicit PCoordinate(QWidget *parent = 0);

signals:

public slots:
};

#endif // PCOORDINATE_H
