#include "videowidget.hpp"
#include <QMessageBox>

#include <QtGui>
#include <QVBoxLayout>

using namespace QtAV;

VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0, 0, 320, 240);
    _player = new AVPlayer(this);
    QVBoxLayout *vl = new QVBoxLayout();

    setLayout(vl);
    _videoOutput = new VideoOutput(this);
    if (!_videoOutput->widget()) {
        QMessageBox::warning(nullptr, QString::fromLatin1("QtAV error"), tr("Can not create video renderer"));
        return;
    }
    vl->setMargin(0);
    _videoOutput->widget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    _videoOutput->widget()->setGeometry(0, 0, 320, 240);

    _player->setRenderer(_videoOutput);
    vl->addWidget(_videoOutput->widget());

    _videoOutput->widget()->show();
}

VideoWidget::~VideoWidget()
{
}

void VideoWidget::openFile(const QString &path)
{
    if (path.isEmpty()) return;
    _videoPath = path;
    _player->play(_videoPath);
}

void VideoWidget::playPause()
{
    if (!_player->isPlaying()) {
        _player->play();
        return;
    }
    _player->pause(!_player->isPaused());
}

void VideoWidget::closeEvent(QCloseEvent *event)
{
    // stop();
    event->accept();
}
