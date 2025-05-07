#ifndef EMOTIONWIDGET_H
#define EMOTIONWIDGET_H

#include <QWidget>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class EmotionWidget;
}
QT_END_NAMESPACE

class EmotionWidget : public QWidget
{
    Q_OBJECT

public:
    EmotionWidget(QWidget *parent = nullptr);
    ~EmotionWidget();

signals:
    void addEmoji(const QByteArray& emo);
private:
    Ui::EmotionWidget *ui;
    QVector<QHBoxLayout*> vt_layout;
};
#endif // EMOTIONWIDGET_H
