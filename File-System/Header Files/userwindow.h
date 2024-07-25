#ifndef USERWINDOW_H
#define USERWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QToolBar>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QInputDialog>
#include <QTextEdit>
#include <QString>
#include "createfiledialog.h"
#include "fsstructure.h"
#include <QTimer>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class UserWindow; }
QT_END_NAMESPACE

class UserWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UserWindow(const QString &username, QWidget *parent = nullptr);
    ~UserWindow();


private slots:
    void createTxtFile();
    void createPdfFile();
    void createFolder();
    void deleteFile();
    void searchFile();
    void logout();
    void goHome();
    void editFile();
    void showCreateFileDialog();
    void openFile();
    void saveFile();
    void renameFile();  // 新增槽函数
    void UserWindowLookTree();
    void introducebook();//说明书
    void updateTime();
    void deleteUserInformation(); // 声明

private:
    Ui::UserWindow *ui;

    QMenu *fileMenu;
    QMenu *createMenu;
    QMenu *UserWindowhelp;
    QAction *Introduce;//说明书
    QAction *createTxtAction;
    QAction *createFolderAction;
    QAction *deleteAction;
    QAction *searchAction;
    QAction *saveAction;
    QAction *logoutAction;
    QAction *renameAction;  // Rename 动作
    QAction *UserWindowLookTreeAction;


    QToolBar *toolBar;
    QAction *homeAction;
    QAction *editAction;
    QAction *UserWindowdeleteUser;

    QWidget *homeWidget;//主页
    QPushButton *createFileButton;//创建文件
    QPushButton *openFileButton;//打开文件
    QTextEdit *textEdit;//文本框
    QString currentFilePath;//当前文件路径
    QString CurrentUser;//当前用户名称

    QLabel *timeLabel; // 用于显示时间的 QLabel
    QTimer *timer; // 用于定时更新时间的 QTimer

};

#endif // USERWINDOW_H
