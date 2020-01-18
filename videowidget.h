#pragma once

#include <QtGui>
#include <QPushButton>
#include <QSlider>
#include <QMainWindow>

#include <QWidget>
#include <QPointer>
#include <vlc/vlc.h>
#include <vlc/libvlc.h>
#include <QScopedPointer>
#include <QSharedPointer>

#define qtu(i) ((i).toUtf8().constData())
class VideoWidget : public QWidget {

    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget() override;

public slots:
    void openFile(const QString &path);

private slots:
    void play();
    void stop();
    void mute();
    void fullscreen();

    int changeVolume(int);
    void changePosition(int);
    void updateInterface();

protected:
    void closeEvent(QCloseEvent *) override;

private:
    // QPushButton *playBut;
    QSlider *_volumeSlider;
    QSlider *_playbackSlider;
    QWidget *_videoWidget;

    QSharedPointer<libvlc_instance_t> _vlcInstance;
    QSharedPointer<libvlc_media_player_t> _vlcPlayer;

    void initUI();
};
