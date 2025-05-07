#ifndef AUTOHEIGHTTEXTEDIT_H
#define AUTOHEIGHTTEXTEDIT_H

#include <QTextEdit>

class AutoHeightTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit AutoHeightTextEdit(QWidget *parent = nullptr);
    void resizeEvent(QResizeEvent* ev)override;

    void adjustDocument();

signals:
    void updateSize();
};

#endif // AUTOHEIGHTTEXTEDIT_H
