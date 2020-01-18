#include "videowidget.h"
#include <QMessageBox>
#include <vlc/vlc.h>

#define qtu(i) ((i).toUtf8().constData())

#include <QtGui>
#include <QVBoxLayout>
VideoWidget::VideoWidget(QWidget *parent) : QWidget(parent)
{
    _vlcPlayer = nullptr;

    /* Initialize libVLC */
    _vlcInstance = libvlc_new(0, nullptr);

    /* Complain in case of broken installation */
    if (_vlcInstance == nullptr) {
        QMessageBox::critical(this, "Qt libVLC player", "Could not init libVLC");
        exit(1);
    }

    /* Interface initialization */
    initUI();
    this->setGeometry(0, 0, 320, 240);
}

VideoWidget::~VideoWidget()
{
    /* Release libVLC instance on quit */
    if (_vlcInstance) libvlc_release(_vlcInstance);
}

void VideoWidget::initUI()
{

    /* Buttons for the UI */
    /*playBut = new QPushButton("Play");
    QObject::connect(playBut, SIGNAL(clicked()), this, SLOT(play()));*/

    QPushButton *stopBut = new QPushButton("Stop");
    QObject::connect(stopBut, SIGNAL(clicked()), this, SLOT(stop()));

    QPushButton *muteBut = new QPushButton("Mute");
    QObject::connect(muteBut, SIGNAL(clicked()), this, SLOT(mute()));

    QPushButton *fsBut = new QPushButton("Fullscreen");
    QObject::connect(fsBut, SIGNAL(clicked()), this, SLOT(fullscreen()));

    _volumeSlider = new QSlider(Qt::Horizontal);
    QObject::connect(_volumeSlider, SIGNAL(sliderMoved(int)), this, SLOT(changeVolume(int)));
    _volumeSlider->setValue(80);

    _playbackSlider = new QSlider(Qt::Horizontal);
    _playbackSlider->setMaximum(1000);
    QObject::connect(_playbackSlider, SIGNAL(sliderMoved(int)), this, SLOT(changePosition(int)));

    /* A timer to update the sliders */
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateInterface()));
    timer->start(100);

    /* Central Widgets */
    _videoWidget = new QWidget(this);

    _videoWidget->setAutoFillBackground(true);
    QPalette plt = palette();
    plt.setColor(QPalette::Window, Qt::black);
    _videoWidget->setPalette(plt);

    QVBoxLayout *layout2 = new QVBoxLayout;
    layout2->setMargin(0);
    layout2->addWidget(_videoWidget);
    layout2->addWidget(_playbackSlider);
    // layout2->addLayout(layout);

    this->setLayout(layout2);
    resize(320, 240);
    this->setAutoFillBackground(true);
}

void VideoWidget::openFile(const QString &path)
{
    /* Stop if something is playing */
    if (_vlcPlayer && libvlc_media_player_is_playing(_vlcPlayer)) stop();

    /* Create a new Media */
    libvlc_media_t *vlcMedia = libvlc_media_new_path(_vlcInstance, qtu(path));
    if (!vlcMedia) return;

    /* Create a new libvlc player */
    _vlcPlayer = libvlc_media_player_new_from_media(vlcMedia);

    /* Release the media */
    libvlc_media_release(vlcMedia);

    /* Integrate the video in the interface */
#if defined(Q_OS_UNIX)
    libvlc_media_player_set_xwindow(_vlcPlayer, _videoWidget->winId());
#elif defined(Q_OS_WIN)
    // libvlc_media_player_set_hwnd(_vlcPlayer, _videoWidget->winId());
#endif

    /* And start playback */
    libvlc_media_player_play(_vlcPlayer);

    /* Update playback button */
    // playBut->setText("Pause");
}

void VideoWidget::play()
{
    if (!_vlcPlayer) return;

    if (libvlc_media_player_is_playing(_vlcPlayer)) {
        /* Pause */
        libvlc_media_player_pause(_vlcPlayer);
        // playBut->setText("Play");
    } else {
        /* Play again */
        libvlc_media_player_play(_vlcPlayer);
        // playBut->setText("Pause");
    }
}

int VideoWidget::changeVolume(int vol)
{ /* Called on volume slider change */

    if (_vlcPlayer) return libvlc_audio_set_volume(_vlcPlayer, vol);

    return 0;
}

void VideoWidget::changePosition(int pos)
{ /* Called on position slider change */

    if (_vlcPlayer) libvlc_media_player_set_position(_vlcPlayer, static_cast<float>(pos) / 1000.0f);
}

void VideoWidget::updateInterface()
{    // Update interface and check if song is finished

    if (!_vlcPlayer) return;

    /* update the timeline */
    float pos = libvlc_media_player_get_position(_vlcPlayer);
    _playbackSlider->setValue(static_cast<int>(pos * 1000.0f));

    /* Stop the media */
    if (libvlc_media_player_get_state(_vlcPlayer) == libvlc_Ended) this->stop();
}

void VideoWidget::stop()
{
    if (_vlcPlayer) {
        /* stop the media player */
        libvlc_media_player_stop(_vlcPlayer);

        /* release the media player */
        libvlc_media_player_release(_vlcPlayer);

        /* Reset application values */
        _vlcPlayer = nullptr;
        _playbackSlider->setValue(0);
        // playBut->setText("Play");
    }
}

void VideoWidget::mute()
{
    if (_vlcPlayer) {
        if (_volumeSlider->value() == 0) {    // if already muted...

            this->changeVolume(80);
            _volumeSlider->setValue(80);

        } else {    // else mute volume

            this->changeVolume(0);
            _volumeSlider->setValue(0);
        }
    }
}

void VideoWidget::fullscreen()
{
    if (isFullScreen()) {
        showNormal();

    } else {
        showFullScreen();
    }
}

void VideoWidget::closeEvent(QCloseEvent *event)
{
    stop();
    event->accept();
}
