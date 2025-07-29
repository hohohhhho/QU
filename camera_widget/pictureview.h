#ifndef PICTUREVIEW_H
#define PICTUREVIEW_H

#include <QWidget>

class PictureView : public QWidget
{
    Q_OBJECT
public:
    explicit PictureView(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
    void mousePressEvent(QMouseEvent* ev)override;
    void mouseMoveEvent(QMouseEvent* ev)override;

    void setImage(const QImage& image);
    void setRangeLimit(QRect range);
signals:
    void clicked();
private:
    QPixmap pxp;

    QPointF pos_pressed;
    QPoint pos_origin;
    QRect move_range;
};

#endif // PICTUREVIEW_H
