#ifndef CLOCKLABEL_H
#define CLOCKLABEL_H

#include <QLabel>
#include <QTime>

class ClockLabel : public QLabel
{
    Q_OBJECT
public:
    explicit ClockLabel(QWidget *parent = nullptr);
    // void paintEvent(QPaintEvent* ev)override;

    void setTime(uint _h,uint _m,uint _s);
    void addTime(uint _s,uint _m=0,uint _h=0);
    QTime getTime();
signals:
private:
    uint h,m,s;

    void updateTime();
};

#endif // CLOCKLABEL_H
