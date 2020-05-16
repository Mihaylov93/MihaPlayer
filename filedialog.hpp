#ifndef FILEDIALOG_H
#define FILEDIALOG_H

#include <QWidget>
#include <QLineEdit>
#include <QDir>

#include <QFileSystemModel>
#include <QTreeView>
#include <QVBoxLayout>

#include <QMessageBox>

class FileDialog : public QWidget {
    Q_OBJECT

public:
    FileDialog(QWidget* parent = nullptr);
    ~FileDialog() override;
signals:
    void openVideo(QString path);
    void quitApplication();

protected:
    void keyReleaseEvent(QKeyEvent* event) override;
    // bool eventFilter(QObject*, QEvent*);

private:
    QLineEdit mPath;
    QFileSystemModel mFSModel;
    QTreeView mTreeView;
    QVBoxLayout* mLayout;

    QMessageBox* mMsgBox;
    bool ignoreConfirm = false;
    bool showPopup(const QString& msg, QMessageBox::StandardButton accept = QMessageBox::NoButton,
                   QMessageBox::StandardButton decline = QMessageBox::NoButton);
    void checkFilePath(const QString& path);
};

#endif    // FILEDIALOG_H
