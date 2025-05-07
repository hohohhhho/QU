#ifndef REDPOINTBUTTON_H
#define REDPOINTBUTTON_H

#include <QPushButton>
#include "myhintpushbutton.h"

class RedPointButton : public MyHintPushButton
{
    Q_OBJECT
public:
    explicit RedPointButton(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;

    void setNum(int num);
    int getNum(){return m_num;};
    void setNotSquare();
    void resizeEvent(QResizeEvent *ev)override;
    QSize sizeHint()const override;

signals:
private:
    int m_num=0;
    bool square=true;
};

#endif // REDPOINTBUTTON_H
