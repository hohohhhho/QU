#include "chatfilelabel.h"

#include <QDialog>
#include <QFileDialog>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QPainter>
#include <QVBoxLayout>
#include <QVideoWidget>

ChatFileLabel::ChatFileLabel(QWidget *parent)
    : QLabel{parent}
{

}

void ChatFileLabel::resizeEvent(QResizeEvent *ev)
{
    QLabel::resizeEvent(ev);
    // if(this->m_type == Message::MessageType::Picture){
    //     adjustSize();
    // }else{
    //    QLabel::resizeEvent(ev);
    // }
}

void ChatFileLabel::mousePressEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);

    if(this->m_type == Message::MessageType::Picture){
        QDialog* dlg = new QDialog(this);
        dlg->resize(600, 600);
        dlg->setAttribute(Qt::WA_DeleteOnClose);

        QVBoxLayout* layout = new QVBoxLayout(dlg);
        layout->setContentsMargins(0, 0, 0, 0);
        layout->setSpacing(0);

        QLabel* label_pxp = new QLabel(dlg);

        label_pxp->setPixmap(this->pixmap());
        // label_pxp->setScaledContents(true);

        label_pxp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        label_pxp->setAlignment(Qt::AlignCenter);

        layout->addWidget(label_pxp);
        dlg->show();
    }else if(this->m_type == Message::MessageType::Video){
        if(m_data.isEmpty()) return;

        QString tempPath = QDir::tempPath() + "/" + m_filename;
        QFile tempFile(tempPath);
        if(tempFile.open(QIODevice::WriteOnly)) {
            tempFile.write(m_data);
            tempFile.close();
        }

        QDialog* playerDlg = new QDialog(this);
        playerDlg->setWindowTitle("视频预览: " + m_filename);
        playerDlg->resize(800, 600);
        playerDlg->setAttribute(Qt::WA_DeleteOnClose);

        QVBoxLayout* layout = new QVBoxLayout(playerDlg);
        QVideoWidget* videoWidget = new QVideoWidget(playerDlg);
        QMediaPlayer* player = new QMediaPlayer(playerDlg);

        layout->addWidget(videoWidget);
        player->setVideoOutput(videoWidget);

        player->setSource(QUrl::fromLocalFile(tempPath));
        playerDlg->show();
        player->play();

        connect(playerDlg, &QDialog::finished, player, &QMediaPlayer::stop);
    }
}

void ChatFileLabel::mouseDoubleClickEvent(QMouseEvent *ev)
{
    Q_UNUSED(ev);

    if(m_data.isEmpty()) return;

    // 获取用户选择的保存路径
    QString savePath = QFileDialog::getSaveFileName(this, "文件下载", m_filename);

    if(!savePath.isEmpty()) {
        QFile file(savePath);
        if(file.open(QIODevice::WriteOnly)) {
            file.write(m_data);
            file.close();
            QMessageBox::information(this, "成功", "文件已保存至:\n" + savePath);
        } else {
            QMessageBox::critical(this, "失败", "无法写入文件");
        }
    }
}

void ChatFileLabel::paintEvent(QPaintEvent *ev)
{
    Q_UNUSED(ev);

    if(m_type == Message::MessageType::Video || m_type == Message::MessageType::File){
        QPainter painter(this);
        painter.fillRect(this->rect(),QColor(200,200,200));

        painter.drawPixmap(0,0,width()/3,height(),QPixmap(":/res/file.png"));

        painter.setPen(Qt::black);
        painter.setFont(QFont("微软雅黑",15));
        painter.drawText(width()/3,0,width()*2/3,height(),Qt::AlignCenter,QString("%1\n"
                                                                                  "-------\n"
                                                                                  "%2KB").arg(m_filename).arg(m_data.size()/1024));
    }else if(m_type == Message::MessageType::Picture){
        QLabel::paintEvent(ev);
    }
}

void ChatFileLabel::setPicture(const QString &filename, const QPixmap &pxp)
{
    this->m_filename = filename;
    this->setPixmap(pxp);
    this->m_type = Message::MessageType::Picture;
}

void ChatFileLabel::setVideo(const QString &filename, const QByteArray &data)
{
    this->m_filename = filename;
    this->m_data = data;
    this->m_type = Message::MessageType::Video;
}

void ChatFileLabel::setNormalFile(const QString &filename, const QByteArray &data)
{
    qDebug()<<"ChatFileLabel:setNormalFile"<<filename;
    this->m_filename = filename;
    this->m_data = data;
    this->m_type = Message::MessageType::File;
}

void ChatFileLabel::adjustSize()
{
    if(this->width() == 0 || m_type != Message::MessageType::Picture || this->pixmap().isNull()){
        return;
    }

    if(this->pixmap().width() != this->width()){
        // qreal ratio = qApp->devicePixelRatio();
        qreal rate = static_cast<qreal>(this->width()/**ratio*/)/this->pixmap().width();

        this->pixmap() = this->pixmap().scaled(this->pixmap().size() * rate,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    }

    this->setFixedSize(this->pixmap().size());
    this->setPixmap(this->pixmap());

    QWidget* parent = this->parentWidget();
    if(parent){
        parent->setFixedSize(this->size());
    }else{
        qDebug()<<"ChatPictureLabel::parent = nullptr";
    }
}
