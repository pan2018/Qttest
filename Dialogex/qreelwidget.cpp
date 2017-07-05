#include "qreelwidget.h"
#include <QPainter>

QReelWidget::QReelWidget(QWidget *parent) : QWidget(parent)
{
    oriSize = QSize(0, 0);
    connect(&animaShow, SIGNAL(frameChanged(int)), SLOT(onShow()));
    connect(&animaExpan, SIGNAL(frameChanged(int)), SLOT(onExpansion()));
    animaShow.setFrameRange(0, 100);
    animaShow.setDuration(500); //平移过程持续时间
    animaShow.setCurveShape(QTimeLine::EaseInCurve); //先慢后快
    animaExpan.setFrameRange(0, 100);
    animaExpan.setDuration(1000); //展开过程持续时间
    animaExpan.setCurveShape(QTimeLine::LinearCurve); //匀速
}

void QReelWidget::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    QPen p(QColor(179,196,204)); //画边框用，颜色深一点边框更明显，效果会更好一些
    p.setWidth(2);
    painter.setPen(p);

    QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, rect().height()));
    linearGradient.setColorAt(0, QColor(236,240,244));
    linearGradient.setColorAt(1, QColor(203,215,221));
    linearGradient.setSpread(QGradient::PadSpread);

    painter.save();
    QPainterPath path;
    /* 窗体圆角设置
     * 底部留25高度画“卷轴”
     * 注意不能用 addRoundRect方法，否则圆角弧度会随窗体大小自动调整，这里要的是绝对弧度 */
    path.addRoundedRect(QRect(rect().topLeft(),QPoint(rect().right(),rect().bottom()-25)),8,8);
    painter.fillPath(path,QBrush(linearGradient));
    painter.drawPath(path);
    painter.restore();
    if(bFinally) { //定格，即最终呈现的时候
        painter.save();
        //因为窗体左下角有一个弧度，还要考虑曲线外留下的空白区域，先“填补”它
        QRect r(0,height()-33,15,16);
        painter.fillRect(r,QColor(203,215,221));
        painter.drawLine(r.topLeft(), r.bottomLeft());

        painter.restore();
        //用贝塞尔曲线填充
        QPoint startPos(20,height()-25);
        QPoint endPos(20,startPos.y()+25);
        QPainterPath path1(startPos);
        //贝塞尔曲线的两个控制点可能没那么精确，大家可以参考贝塞尔曲线算法做到更精确的控制，我这就不赘述了
        path1.cubicTo(QPoint(0,startPos.y()), QPoint(-15,startPos.y()+8), endPos);
        //闭合曲线区域
        path1.closeSubpath();
        painter.fillPath(path1, QColor(43,43,43));
        painter.drawPath(path1);
    }
    else { //动画的时候
        painter.save();
        //同上面一样，先“填补”窗体左下角的空白区域

        /* 注意这里的椭圆高度控制为15，底部给定格的时候留下一定区域
         * 因为定格的时候“卷筒”要展开 */
        QRect r(0,height()-33,20,15);
        painter.fillRect(r,QColor(203,215,221));
        //画三条边框线
        painter.drawLine(r.topLeft(), r.bottomLeft());
        painter.drawLine(QPoint(20,height()-25), r.bottomRight());
        painter.drawLine(QPoint(10,height()-25), QPoint(20,height()-25));

        painter.restore();
        //用椭圆填充
        QPainterPath path1;
        path1.addEllipse(0,height()-25,20,15);
        painter.fillPath(path1, QColor(43,43,43));
        painter.drawPath(path1);
    }
}

void QReelWidget::onShow()
{
    /* 显示Widget的时候首先按帧数逐渐平移到指定位置oriPos
     * 我这里x方向总共移动10，y方向移动60，大家可以根据需要自己控制
     * 若不需要平移的效果大可直接忽略 */
    int indexFrame = animaShow.currentFrame();
    move(oriPos.x()+10/100.0*(100-indexFrame), oriPos.y()+60/100.0*(100-indexFrame));
    if(indexFrame >= 99) //平移完后开始逐渐展开
        animaExpan.start();
}
void QReelWidget::onExpansion()
{
    /* 展开过程，oriSize为Widget的原始尺寸
     * 展开过程宽度至少为20，因为“卷轴”部分的宽度为20 */
    int indexFrame = animaExpan.currentFrame();
    resize(20+(oriSize.width()-20)/100.0*indexFrame, oriSize.height());
    if(indexFrame >= 99) { //最终定格
        bFinally = true;
    }
}
//展开显示
void QReelWidget::showExpan()
{
    bFinally = false;
    resize(20,height()); //最初保持“卷轴”部分的宽度
    move(oriPos.x()+10,oriPos.y()+60);
    show();
    animaShow.stop();
    animaExpan.stop();
    animaShow.start();
}
//设置原始左上角坐标
void QReelWidget::setOriPos(const QPoint& p)
{
    this->oriPos = p;
}
//设置原始尺寸
void QReelWidget::setOriSize(const QSize& s)
{
    this->oriSize = s;
}
