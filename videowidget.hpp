#pragma once

#include <QtGui>
#include <QPushButton>
#include <QSlider>
#include <QMainWindow>

#include <QWidget>
#include <QPointer>
#include <QScopedPointer>
#include <QSharedPointer>

#include <QtAV>
#include <QtAVWidgets>

class VideoWidget : public QWidget {

    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget() override;

public slots:
    void openFile(const QString &path);

private slots:
    void playPause();

protected:
    void closeEvent(QCloseEvent *) override;

private:
    // QPushButton *playBut;
    // QSlider *_volumeSlider;
    // QSlider *_playbackSlider;
    QWidget *_videoWidget;
    QString _videoPath;

    QtAV::AVPlayer *_player;
    QtAV::VideoOutput *_videoOutput;
};
