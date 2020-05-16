#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "filedialog.hpp"
#include "videowidget.hpp"

#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QVBoxLayout>
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setFixedSize(320, 240);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    ui->setupUi(this);
    ui->verticalLayout->setMargin(2);
    new QVBoxLayout(ui->sw1);
    new QVBoxLayout(ui->sw2);
    _fileDialog = new FileDialog(ui->sw1);
    _videoWidget = new VideoWidget(ui->sw2);

    connect(_fileDialog, &FileDialog::openVideo, this, &MainWindow::playVideo);
    QObject::connect(_fileDialog, SIGNAL(quitApplication()), QApplication::instance(), SLOT(quit()));

    ui->stackedWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playVideo(const QString &iPath)
{
    _videoWidget->openFile(iPath);
    _fileDialog->hide();
    ui->stackedWidget->setCurrentWidget(ui->sw2);
    _videoWidget->show();
    _videoWidget->setFocus();
}
