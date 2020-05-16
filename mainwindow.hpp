#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class VideoWidget;
class FileDialog;
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

public slots:
    void playVideo(const QString& path);

private:
    Ui::MainWindow* ui;
    VideoWidget* _videoWidget;
    FileDialog* _fileDialog;
};

#endif    // MAINWINDOW_H
