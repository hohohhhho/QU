#ifndef EMOTIONITEM_H
#define EMOTIONITEM_H

#include <QLabel>
#include <QWidget>

class EmotionItem : public QWidget
{
    Q_OBJECT
public:
    explicit EmotionItem(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
    void mousePressEvent(QMouseEvent* ev)override;
    void enterEvent(QEnterEvent* ev)override;
    void leaveEvent(QEvent* ev)override;

    QByteArray getEmotion(){return m_emotion;};
    void setEmotion(const QByteArray& emo,const QString& introduce="无介绍");
    QLabel* label_tooltip;
signals:
    void clicked();
private:

    QByteArray m_emotion;
    QString m_introduce="无介绍";
    float scaling=0.8f;
};

#endif // EMOTIONITEM_H
