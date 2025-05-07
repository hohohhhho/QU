#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QWidget>

class LoadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoadWidget(QString text="加载中...",QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;

    void changeText(const QString& text);
public slots:
    void changeProgress(qreal progress, const QString &text);
signals:
    void finished();
private:
    qreal progress=0.0f;
    QString text="加载中...";
};

#endif // LOADWIDGET_H
