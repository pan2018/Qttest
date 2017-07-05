//点击时动态弹出并可扩展窗口大小
#ifndef QREELWIDGET_H
#define QREELWIDGET_H

#include <QWidget>
#include <QPoint>
#include <QSize>
#include <QTimeLine>

class QReelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QReelWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void setOriPos(const QPoint&);
    void setOriSize(const QSize&);
    void showExpan();

private slots:
    void onShow();
    void onExpansion();
private:
    bool bFinally;
    QPoint oriPos;
    QSize oriSize;
    QTimeLine animaShow;
    QTimeLine animaExpan;
};

#endif // QREELWIDGET_H
