#ifndef CHATBUBBLE_H
#define CHATBUBBLE_H

#include <QLabel>
#include <QStackedWidget>
#include <QTextEdit>
#include "autoheighttextedit.h"
#include "chatfilelabel.h"
#include "macro.h"

class ChatBubble : public QWidget//整个气泡聊天框
{
    Q_OBJECT
public:
    explicit ChatBubble(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* ev)override;
    void resizeEvent(QResizeEvent* ev)override;

    void setText(const QString& text);
    void setPicture(const QString& filename, const QPixmap& pxp);
    void setVideo(const QString& filename, const QByteArray& data);
    void setNormalFile(const QString& filename, const QByteArray& data);

    QStackedWidget* stack;
    AutoHeightTextEdit* edit;//聊天框中自适应文字大小的显示栏
    ChatFileLabel* label_file;
    QWidget* w_file;
    Message::MessageType m_type = Message::MessageType::Text;
signals:
private:

};

#endif // CHATBUBBLE_H
