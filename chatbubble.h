#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QLabel>
#include <QStackedWidget>
#include <QTextEdit>
#include "autoheighttextedit.h"

class ChatBubble : public QWidget
{
    Q_OBJECT
public:
    explicit ChatBubble(QWidget *parent = nullptr);
    // void paintEvent(QPaintEvent* ev)override;

    void setText(const QString& text);
    void setPximap(const QPixmap& pxp);

    AutoHeightTextEdit* edit;
    QStackedWidget* stack;
    QLabel* label_pxp;
    QWidget* w_file;
signals:
private:

};

#endif // CHATBUBBLE_H
