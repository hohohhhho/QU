#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPropertyAnimation>
#include <QList>
#include <QParallelAnimationGroup>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyButton;
}
QT_END_NAMESPACE

class MyButton : public QWidget
{
    Q_OBJECT
    //Q_PROPERTY(QList<int> circle_radius_list READ getCircleRadiusList WRITE setName NOTIFY nameChanged FINAL)
public:
    int w=80;
    int h=40;
    MyButton(QWidget *parent = nullptr);
    ~MyButton();
    void paintEvent(QPaintEvent* ev);
    //void mouseMoveEvent(QMouseEvent* ev);
    void resizeEvent(QResizeEvent* ev);
    void leaveEvent(QEvent* ev);
    void enterEvent(QEnterEvent* ev);
    void mousePressEvent(QMouseEvent* ev);
    void mouseReleaseEvent(QMouseEvent* ev);
    void setText(QString qstr){text=qstr;};
    QString getText(){return this->text;};
    //void setText(QString text);
    //QList<int> getCircleRadiusList(){return  circle_radius_list;}

signals:
    void clicked();

private:
    //Ui::MyButton *ui;
    QLabel* label;
    QString text="我是一个按钮";
    int radius=h/10;
    int circle_x=0;
    int circle_y=0;
    int circle_radius1=0;
    QPropertyAnimation* animation1;

    // QList<int> circle_x_list;
    // QList<int> circle_y_list;
    // QList<int> circle_radius_list;
    // QList<QPropertyAnimation*> animation_list;
    // QParallelAnimationGroup* group;

    //int pointer=0;
    //QTimer* timer;

    QColor TextColor=qRgb(9,100,225);

    QColor BkColor=qRgb(20, 211, 195);
    QColor TempColor=qRgb(18, 234, 217);

};
#endif // MYBUTTON_H
