#ifndef PROFILE_H
#define PROFILE_H

#include <QPushButton>
#include "myhintpushbutton.h"

class Profile : public MyHintPushButton
{
    Q_OBJECT
public:
    explicit Profile(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
signals:
};

#endif // PROFILE_H
