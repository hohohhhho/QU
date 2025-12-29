#ifndef AUTOROTATEBUTTON_H
#define AUTOROTATEBUTTON_H

#include "myhintpushbutton.h"
#include <QVariantAnimation>

class AutoRotateButton : public MyHintPushButton
{
    Q_OBJECT
public:
    explicit AutoRotateButton(QWidget *parent = nullptr);

signals:
    void safeClicked();
private:
    QVariantAnimation* animation;
};

#endif // AUTOROTATEBUTTON_H
