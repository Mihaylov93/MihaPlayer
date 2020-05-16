#include "filedialog.hpp"

#include <QFileIconProvider>
#include <QSizePolicy>

#include <QEvent>
#include <QKeyEvent>
#include <QMessageBox>
#include <QPushButton>
#include <QMimeDatabase>

FileDialog::FileDialog(QWidget *parent) : QWidget(parent)
{
    // this->setFixedSize(320/*298*/, 220);
    this->setGeometry(0, 0, 320, 240);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mPath.setText(QDir::homePath());
    mPath.setFocusPolicy(Qt::NoFocus);
    mFSModel.setRootPath(QDir::homePath());
    mFSModel.iconProvider()->setOptions(QFileIconProvider::DontUseCustomDirectoryIcons);

    mTreeView.setModel(&mFSModel);
    mTreeView.setFocus();
    const QModelIndex rootIndex = mFSModel.index(QDir::cleanPath(QDir::homePath()));
    if (rootIndex.isValid()) mTreeView.setRootIndex(rootIndex);
    mLayout = new QVBoxLayout(this);
    mLayout->setMargin(1);
    //->setContentsMargins(0, 0, 0, 0);
    mLayout->addWidget(&mPath);
    mLayout->addWidget(&mTreeView);

    this->setLayout(mLayout);

    mTreeView.hideColumn(1);
    mTreeView.hideColumn(2);
    mTreeView.hideColumn(3);

    connect(&mTreeView, &QTreeView::expanded,
            [=](const QModelIndex &index) { this->mPath.setText(mFSModel.filePath(index)); });

    connect(&mTreeView, &QTreeView::collapsed,
            [=](const QModelIndex &index) { this->mPath.setText(mFSModel.filePath(index)); });

    /* connect(&mTreeView, &QTreeView::keyPressEvent,
             [=]() { this->mPath.setText(mFSModel.filePath(mTreeView.currentIndex())); });*/

    mMsgBox = new QMessageBox(this);
}

FileDialog::~FileDialog()
{
}

void FileDialog::keyReleaseEvent(QKeyEvent *event)
{
    // handle custom buttons
    switch (event->key()) {
        case Qt::Key_J: {
            // mMsgBox->information(this, tr("Application Name"), tr("An information message."));

            if (!ignoreConfirm) {
                checkFilePath(mFSModel.filePath(mTreeView.currentIndex()));
            } else
                ignoreConfirm = false;

            break;
        }
        case Qt::Key_Enter:
            if (showPopup("Do you want to exit?", QMessageBox::Yes, QMessageBox::No)) emit quitApplication();
            break;
        default:
            // Pass others to base class
            QWidget::keyReleaseEvent(event);
            break;
    }
}

bool FileDialog::showPopup(const QString &msg, QMessageBox::StandardButton accept, QMessageBox::StandardButton decline)
{
    bool result(false);

    mMsgBox->setText(msg);
    if (accept != QMessageBox::NoButton) {
        if (decline == QMessageBox::NoButton) {

            mMsgBox->setStandardButtons(accept);
            mMsgBox->setDefaultButton(accept);
            QAbstractButton *btnAccept = mMsgBox->button(accept);
            Q_ASSERT(btnAccept);
            btnAccept->setShortcut(QKeySequence(Qt::Key_J));
            ignoreConfirm = true;
            mMsgBox->exec();
            // if (mMsgBox->exec() == accept) ignoreConfirm = false;
        } else {

            mMsgBox->setStandardButtons(accept | decline);
            mMsgBox->setDefaultButton(decline);
            QAbstractButton *btnAccept = mMsgBox->button(accept);
            Q_ASSERT(btnAccept);
            btnAccept->setShortcut(QKeySequence(Qt::Key_J));
            QAbstractButton *btnDecline = mMsgBox->button(decline);
            Q_ASSERT(btnDecline);
            btnDecline->setShortcut(QKeySequence(Qt::Key_B));

            if (mMsgBox->exec() == accept) {
                // do something
                result = true;
            } else {
                mMsgBox->close();
                result = false;
            }
        }
    }
    return result;
}

void FileDialog::checkFilePath(const QString &path)
{
    QFileInfo file(path);
    if (file.isDir() && file.exists()) {
        showPopup(mFSModel.filePath(mTreeView.currentIndex()).append(" is a Dir."), QMessageBox::Ok);
    } else if (file.isFile() && file.exists()) {
        QString mimeType = QMimeDatabase().mimeTypeForFile(file).name();
        if (mimeType.contains("video")) {
            emit openVideo(path);
        } else {
            showPopup(mFSModel.filePath(mTreeView.currentIndex()).append(" File is not a video."), QMessageBox::Ok);
        }
    }
}
