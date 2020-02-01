#pragma once

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
class VideoWidget : public QVideoWidget {

    Q_OBJECT

public:
    explicit VideoWidget(QWidget *parent = nullptr);
    ~VideoWidget() override;

public slots:
    void openFile(const QString &path);

protected:
    // void keyPressEvent(QKeyEvent *event) override;
    // void mouseDoubleClickEvent(QMouseEvent *event) override;
    // void mousePressEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *) override;    //

private:
    QMediaPlayer *_player = nullptr;
    QMediaPlaylist *_playlist = nullptr;
};
