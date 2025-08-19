#include "autoheighttextedit.h"

#include <QResizeEvent>
#include <QTextDocument>
#include <QAbstractTextDocumentLayout>

AutoHeightTextEdit::AutoHeightTextEdit(QWidget *parent)
    : QTextEdit{parent}
{
    this->setStyleSheet("QTextEdit{"
                        "border:none;"
                        "background-color:transparent;"
                        "}");
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    // this->setMaximumSize(QWIDGETSIZE_MAX,QWIDGETSIZE_MAX);
    connect(this,&QTextEdit::textChanged,this,[=](){
        adjustDocument();
    });
}

void AutoHeightTextEdit::resizeEvent(QResizeEvent *ev)
{
    QTextEdit::resizeEvent(ev);
    if(ev->size()!=ev->oldSize()){
        this->adjustDocument();
    }
}

void AutoHeightTextEdit::adjustDocument()
{
    const int validWidth = viewport()->width() - 2*frameWidth();
    document()->setPageSize(QSizeF(validWidth, -1));

    qreal h_document=this->document()->size().height();
    QMargins margins=this->contentsMargins();
    int h_margins=margins.top()+margins.bottom();
    int pad=frameWidth()*2;

    int new_height=h_document+h_margins+pad;
    // qDebug()<<"adjustdocument,new_height:"<<QString("%1+%2+%3").arg(h_document).arg(h_margins).arg(pad);

    if(new_height!=height()){
        this->setFixedHeight(new_height);
        emit updateSize();
    }
}
