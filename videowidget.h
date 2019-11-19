#pragma once

#include <QtGui>
#include <vlc/vlc.h>
#include <QPushButton>
#include <QSlider>
#include <QMainWindow>

#include <QWidget>
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

    libvlc_instance_t *_vlcInstance;
    libvlc_media_player_t *_vlcPlayer;

    void initUI();
};
