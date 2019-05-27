#ifndef MYTRACER_H
#define MYTRACER_H

#include <QObject>
#include "qcustomplot.h"
class myTracer : public QObject
{
    Q_OBJECT
public:

    enum TracerType
    {
        XAxisTracer,
        YAxisTracer,
        DataTracer
    };

public:

    explicit myTracer(QCustomPlot *_plot, TracerType _type, QObject *parent = nullptr);
    ~myTracer();

    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);
    void setText(const QString &text);
    void setLabelPen(const QPen &pen);
    void updatePosition(double xValue, double yValue);

protected:
    void setVisible(bool visible);
protected:
    QCustomPlot *plot = nullptr;
    QCPItemTracer *tracer = nullptr;// 跟踪的点
    QCPItemText *label = nullptr;   // 显示的数值
    QCPItemLine *arrow = nullptr;   // 箭头

    TracerType type = DataTracer;
    bool visible = false;
};


#endif // MYTRACER_H
