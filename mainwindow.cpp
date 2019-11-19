#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "filedialog.h"
#include "videowidget.h"

#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    this->setFixedSize(320, 240);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    ui->setupUi(this);
    _fileDialog = new FileDialog(this);
    ui->stackedWidget->addWidget(_fileDialog);
    _fileDialog->show();

    connect(_fileDialog, &FileDialog::openVideo, this, &MainWindow::playVideo);
    QObject::connect(_fileDialog, SIGNAL(quitApplication()), QApplication::instance(), SLOT(quit()));

    _videoWidget = new VideoWidget(this);
    ui->stackedWidget->addWidget(_videoWidget);
    ui->stackedWidget->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::playVideo(const QString &iPath)
{
    _videoWidget->openFile(iPath);
    // ui->stackedWidget->currentWidget()->clearFocus();
    // ui->stackedWidget->currentWidget()->hide();
    ui->stackedWidget->setCurrentWidget(_videoWidget);
}
