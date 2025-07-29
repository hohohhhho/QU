#include "profile.h"

#include <QLabel>
#include <QPainter>
#include <QPainterPath>

Profile::Profile(QWidget *parent)
    : MyHintPushButton{parent}
{
    this->setStyleSheet("QPushButton{"
                        "background-color:rgba(0,0,0,0);"
                        // "border:none;"
                        "}");
    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(this,&QPushButton::clicked,this,[=](){
        if(checkable){
            QLabel* label=new QLabel;
            label->setAlignment(Qt::AlignCenter);
            label->setAttribute(Qt::WA_DeleteOnClose);
            const static int size=512;
            label->setFixedSize(size,size);
            QPixmap pxp=this->icon().pixmap(size,size);
            label->setPixmap(pxp);
            label->show();
        }
    });
}

void Profile::paintEvent(QPaintEvent *ev)
{
    // MyHintPushButton::paintEvent(ev);

    // QBitmap mask(this->size());
    // QPainter p(&mask);
    // mask.fill(Qt::color0);
    // p.setRenderHint(QPainter::Antialiasing);
    // p.setBrush(Qt::color1);
    // p.setPen(Qt::color1);
    // int pad=4;
    // p.drawEllipse(pad,pad,this->width()-pad*2,this->height()-pad*2);
    // this->setMask(mask);

    Q_UNUSED(ev);

    QPainter painter(this);
    // painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(rect(), Qt::transparent);

    QPainterPath path;
    path.addEllipse(rect().adjusted(4, 4, -4, -4));

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setClipPath(path);

    if (icon().isNull()) {
        this->setIcon(QIcon(":/res/defualt_profile"));
        // painter.setPen(QPen(Qt::gray));
        // painter.drawEllipse(rect().adjusted(1,1,-1,-1));
    }
    icon().paint(&painter, rect());
}

void Profile::setCheckPicture(bool on)
{
    checkable = on;
}
