#include "autorotatebutton.h"

#include <QPainter>

AutoRotateButton::AutoRotateButton(QWidget *parent)
    : MyHintPushButton{parent}
{
    this->animation=new QVariantAnimation(this);
    animation->setStartValue(0);
    animation->setEndValue(180);
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::OutQuad);

    connect(this, &QPushButton::clicked, this, [=](){
        if(animation->state() != QVariantAnimation::Running){
            emit safeClicked();
            animation->start();
        }
    });

    connect(animation,&QVariantAnimation::valueChanged,this,[=](const QVariant& value){
        // QPixmap pxp = QPixmap(":/res/refresh.png");
        // QTransform transform;
        // QPoint center = QPoint(pxp.width()/2 , pxp.height()/2);
        // transform = transform.translate(center.x() , center.y());
        // transform= transform.rotate(value.toInt());
        // transform = transform.translate(-center.x() , -center.y());
        // pxp = pxp.transformed(transform);
        // ui->btn_refresh->setIcon(QIcon(pxp));
        QPixmap origin = QPixmap(":/res/refresh.png");
        QPixmap canvas(origin.size());
        QTransform transform = QTransform().rotate(value.toInt());
        QPixmap pxp = origin.transformed(transform);
        canvas.fill(Qt::transparent);
        QPainter painter(&canvas);
        painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
        QPoint dp( origin.width()-pxp.width(),origin.height()-pxp.height() );
        painter.drawPixmap(dp.x()/2 , dp.y()/2 , pxp/*.scaled(canvas.size(),Qt::KeepAspectRatio,Qt::SmoothTransformation)*/);
        this->setIcon(QIcon(canvas));
    });
}
