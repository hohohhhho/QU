#include "emotionwidget.h"
#include "ui_emotionwidget.h"
#include "emotionitem.h"

#include <QMap>

EmotionWidget::EmotionWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmotionWidget)
{
    ui->setupUi(this);
    this->setFocusPolicy(Qt::NoFocus);
    const QVector<QPair<QByteArray, QString>> emojis = {
        // 笑脸表情
        {"😀", "大笑"},        {"😃", "开心大笑"},    {"😄", "笑眼"},
        {"😁", "得意"},        {"😆", "笑到不行"},    {"😅", "流汗笑"},
        {"😂", "笑哭"},        {"🤣", "笑到打滚"},    {"😊", "微笑"},
        {"😇", "天使"},        {"🙂", "普通笑"},      {"🙃", "倒脸"},
        {"😉", "眨眼"},        {"😌", "轻松"},        {"😍", "爱心眼"},

        // 动物与自然
        {"🐶", "狗"},          {"🐱", "猫"},          {"🐭", "老鼠"},
        {"🐹", "仓鼠"},        {"🐰", "兔子"},        {"🦊", "狐狸"},
        {"🐻", "熊"},          {"🐼", "熊猫"},        {"🐨", "考拉"},
        {"🐯", "老虎"},        {"🦁", "狮子"},        {"🐮", "牛"},
        {"🐷", "猪"},          {"🐸", "青蛙"},        {"🐥", "小鸡"},

        // 食物饮料
        {"🍎", "苹果"},        {"🍐", "梨"},          {"🍊", "橘子"},
        {"🍋", "柠檬"},        {"🍌", "香蕉"},        {"🍉", "西瓜"},
        {"🍇", "葡萄"},        {"🍓", "草莓"},        {"🍈", "甜瓜"},
        {"🍒", "樱桃"},        {"🍑", "桃子"},        {"🍍", "菠萝"},
        {"🥭", "芒果"},        {"🥥", "椰子"},        {"🥝", "猕猴桃"},

        // 活动与运动
        {"⚽", "足球"},        {"🏀", "篮球"},        {"🏈", "橄榄球"},
        {"⚾", "棒球"},        {"🎾", "网球"},        {"🏐", "排球"},
        {"🎱", "台球"},        {"🏓", "乒乓球"},      {"🏸", "羽毛球"},
        {"🥅", "球门"},        {"⛳", "高尔夫"},      {"🎯", "靶心"},

        // 交通工具
        {"🚗", "轿车"},        {"🚕", "出租车"},      {"🚙", "SUV"},
        {"🚌", "巴士"},        {"🚎", "电车"},        {"🏎", "赛车"},
        {"🚓", "警车"},        {"🚑", "救护车"},      {"🚒", "消防车"},
        {"✈️", "飞机"},       {"🚀", "火箭"},        {"🛸", "飞碟"},

        // 特殊符号
        {"❤️", "红心"},        {"💔", "碎心"},       {"⭐", "星星"},
        {"🌟", "闪星"},        {"✨", "火花"},        {"💫", "眩晕"},
        {"💥", "爆炸"},        {"💦", "汗滴"},        {"💨", "疾风"}
    };

    const int emo_size=35;
    int i_column=0;
    int i_emo=0;
    while(i_emo < emojis.size()){
        QHBoxLayout *layout=new QHBoxLayout;
        for(; i_emo<(i_column+1)*10 && i_emo<emojis.size() ;i_emo++){
            auto emo=emojis[i_emo];
            EmotionItem* item=new EmotionItem(this);
            item->setFixedSize(emo_size,emo_size);
            item->setEmotion(emo.first,emo.second);
            layout->addWidget(item);
            connect(item,&EmotionItem::clicked,this,[=](){
                emit addEmoji(item->getEmotion());
            });
        }
        ui->vl_emotion->insertLayout(i_column,layout);
        i_column++;
    }
    // QHBoxLayout *layout=new QHBoxLayout;
    // for(int i=0; i<10 && i<emojis.size() ;i++){
    //     auto emo=emojis[i];
    //     EmotionItem* item=new EmotionItem(this);
    //     item->setFixedSize(emo_size,emo_size);
    //     item->setEmotion(emo.first,emo.second);
    //     layout->addWidget(item);
    // }
    // QHBoxLayout *layout2=new QHBoxLayout;
    // for(int i=10; i<20 && i<emojis.size() ;i++){
    //     auto emo=emojis[i];
    //     EmotionItem* item=new EmotionItem(this);
    //     item->setFixedSize(emo_size,emo_size);
    //     item->setEmotion(emo.first,emo.second);
    //     layout2->addWidget(item);
    // }

    // ui->vl_emotion->insertLayout(0,layout);
    // ui->vl_emotion->insertLayout(0,layout2);
}

EmotionWidget::~EmotionWidget()
{
    delete ui;
}
