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

    void setCheckPicture(bool on);
signals:
private:
    bool checkable = false;
};

#endif // PROFILE_H
