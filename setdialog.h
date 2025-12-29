#ifndef SETDIALOG_H
#define SETDIALOG_H

#include <QCheckBox>
#include <QDialog>
#include <QLineEdit>
#include <QRadioButton>

class SetDialog : public QDialog
{
    Q_OBJECT
public:
    explicit SetDialog(QWidget *parent = nullptr);

    QLineEdit *edit_ip;
    QLineEdit *edit_port;
    QRadioButton *radio_linux;
    QRadioButton *radio_windows;
    QRadioButton *radio_cloud;
    QRadioButton *radio_custom;
    QCheckBox* box;
    QPushButton *btn_save;
    QPushButton *btn_cancel;
signals:
};

#endif // SETDIALOG_H
