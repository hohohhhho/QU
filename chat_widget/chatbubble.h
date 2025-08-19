#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QLabel>
#include <QStackedWidget>
#include <QTextEdit>
#include "autoheighttextedit.h"
#include "chatpicturelabel.h"

class ChatBubble : public QWidget//整个气泡聊天框
{
    Q_OBJECT
public:
    explicit ChatBubble(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
    void resizeEvent(QResizeEvent* ev)override;

    void setText(const QString& text);
    void setPximap(const QPixmap& pxp);

    QStackedWidget* stack;
    AutoHeightTextEdit* edit;//聊天框中自适应文字大小的显示栏
    ChatPictureLabel* label_pxp;
    QWidget* w_file;
signals:
private:

};

#endif // CHATBUBBLE_H
