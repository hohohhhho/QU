#ifndef ROUNDLABEL_H
#define ROUNDLABEL_H

#include <QLabel>

class RoundLabel : public QLabel
{
    Q_OBJECT
public:
    explicit RoundLabel(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
signals:
};

#endif // ROUNDLABEL_H
