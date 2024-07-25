#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPalette>
#include <QBitmap>
#include <QPainter>
#include <QCheckBox>
#include <QTextBrowser>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QDesktopServices>
#include <QUrl>
#include <QIcon>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // 构造函数
    MainWindow(QWidget *parent = nullptr);

    // 析构函数
    ~MainWindow();

    // 界面初始化函数
    void initUI();

private slots:
    // 注册按钮的槽函数，用于处理注册操作
    void registerPushButton();

    // 登录按钮的槽函数，用于处理登录操作
    void loginPushButton();

    // 打开服务条款的槽函数
    void openTerms();

private:
    Ui::MainWindow *ui;  // UI指针，用于访问UI设计器生成的UI组件

    QPushButton *logining;  // 登录按钮，用于触发登录操作
    QPushButton *registering;  // 注册按钮，用于触发注册操作

    QLabel *usernameLabel;  // 用户名标签，用于显示“用户名”文本
    QLabel *passwordLabel;  // 密码标签，用于显示“密码”文本

    QLineEdit *usernameLineEdit;  // 用户名输入框，用于用户输入用户名
    QLineEdit *passwordLineEdit;  // 密码输入框，用于用户输入密码，并以隐藏方式显示

    QLabel *avatarLabel;  // 用户头像标签，用于显示用户头像

    QLabel *termsLabel;  // 标签，用于显示服务条款的链接
    QCheckBox *termsCheckBox;  // 复选框，用于用户同意条款
};

#endif // MAINWINDOW_H
