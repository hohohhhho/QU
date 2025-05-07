#include "setdialog.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QRadioButton>
#include <QPushButton>
#include <QCheckBox>

SetDialog::SetDialog(QWidget *parent)
    : QDialog{parent}
{
    setObjectName("SetDialog");
    this->setStyleSheet("QLineEdit{"
                        "font-size:15px;"
                        "}");
    resize(400, 300);

    // 主垂直布局
    QVBoxLayout *verticalLayout = new QVBoxLayout(this);
    verticalLayout->setObjectName("verticalLayout");

    /* 第一部分：表单布局 + 单选按钮组 */
    QVBoxLayout *verticalLayout_12 = new QVBoxLayout();
    verticalLayout_12->setObjectName("verticalLayout_12");

    // 表单布局
    QFormLayout *formLayout = new QFormLayout();
    formLayout->setObjectName("formLayout");

    // 服务器IP输入
    QLabel *label = new QLabel("服务器ip：", this);
    label->setObjectName("label");
    edit_ip = new QLineEdit(this);
    edit_ip->setObjectName("edit_ip");
    formLayout->setWidget(0, QFormLayout::LabelRole, label);
    formLayout->setWidget(0, QFormLayout::FieldRole, edit_ip);

    // 端口输入
    QLabel *label_2 = new QLabel("端口：", this);
    label_2->setObjectName("label_2");
    edit_port = new QLineEdit(this);
    edit_port->setObjectName("edit_port");
    formLayout->setWidget(1, QFormLayout::LabelRole, label_2);
    formLayout->setWidget(1, QFormLayout::FieldRole, edit_port);

    verticalLayout_12->addLayout(formLayout);

    // 单选按钮组
    QGroupBox *groupBox = new QGroupBox("选择服务器连接类型：", this);
    groupBox->setObjectName("groupBox");
    QVBoxLayout *verticalLayout_11 = new QVBoxLayout(groupBox);
    verticalLayout_11->setObjectName("verticalLayout_11");

    radio_linux = new QRadioButton("本地Linux(Ubuntu)", groupBox);
    radio_linux->setObjectName("radio_linux");
    radio_linux->setChecked(true);

    radio_windows = new QRadioButton("本地Windows", groupBox);
    radio_windows->setObjectName("radio_windows");

    radio_cloud = new QRadioButton("阿里云服务器", groupBox);
    radio_cloud->setObjectName("radio_cloud");

    radio_custom = new QRadioButton("自定义(仅测试用）", groupBox);
    radio_custom->setObjectName("radio_custom");

    verticalLayout_11->addWidget(radio_linux);
    verticalLayout_11->addWidget(radio_windows);
    verticalLayout_11->addWidget(radio_cloud);
    verticalLayout_11->addWidget(radio_custom);

    verticalLayout_12->addWidget(groupBox);
    verticalLayout->addLayout(verticalLayout_12);

    box=new QCheckBox("自动查询重复账号",this);
    box->setChecked(true);
    verticalLayout->addWidget(box);
    /* 第二部分：按钮布局 */
    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    horizontalLayout->setObjectName("horizontalLayout");

    // 左侧弹簧
    QSpacerItem *horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer);

    // 保存按钮
    btn_save = new QPushButton("保存", this);
    btn_save->setObjectName("btn_save");
    btn_save->setAutoDefault(false);
    horizontalLayout->addWidget(btn_save);

    // 取消按钮
    btn_cancel = new QPushButton("取消", this);
    btn_cancel->setObjectName("btn_cancel");
    btn_cancel->setAutoDefault(false);
    horizontalLayout->addWidget(btn_cancel);

    // 右侧弹簧
    QSpacerItem *horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    horizontalLayout->addItem(horizontalSpacer_2);

    verticalLayout->addLayout(horizontalLayout);

    /* 第三部分：底部弹簧 */
    QSpacerItem *verticalSpacer = new QSpacerItem(20, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);
    verticalLayout->addItem(verticalSpacer);

    connect(edit_ip,&QLineEdit::returnPressed,this,[=](){
        edit_port->setFocus();
    });
    connect(edit_port,&QLineEdit::returnPressed,this,[=](){
        emit btn_save->clicked();
    });
}
