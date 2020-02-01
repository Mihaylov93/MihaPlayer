#include "videowidget.h"
//#include <QMessageBox>

#include <QKeyEvent>
#include <QVBoxLayout>

VideoWidget::VideoWidget(QWidget *parent) : QVideoWidget(parent)
{
    _player = new QMediaPlayer(this);
    _player->setAudioRole(QAudio::VideoRole);

    qInfo() << "Supported audio roles:";
    for (QAudio::Role role : _player->supportedAudioRoles()) qInfo() << "    " << role;
    // owned by PlaylistModel
    _playlist = new QMediaPlaylist();
    _player->setPlaylist(_playlist);

    setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);

    QPalette p = palette();
    p.setColor(QPalette::Window, Qt::black);
    setPalette(p);

    setAttribute(Qt::WA_OpaquePaintEvent);

    _player->setVideoOutput(this);
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::openFile(const QString &path)
{

    _playlist->addMedia(QUrl(path));
    _player->play();
}

void VideoWidget::closeEvent(QCloseEvent *event)
{
    event->accept();
}
