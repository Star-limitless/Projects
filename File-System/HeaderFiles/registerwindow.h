#ifndef REGISTERWINDOW_H
#define REGISTERWINDOW_H

#include <QMainWindow>
#include <QString>
#include <string>
#include <ostream>
#include <fstream>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFile>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QDir>
#include <QPalette>
#include <QTextStream>
#include <QDesktopServices>
#include <QUrl>
#include <QIcon>

// 声明 Ui 命名空间
namespace Ui {
class RegisterWindow;
}

// RegisterWindow 类继承自 QMainWindow
class RegisterWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RegisterWindow(QWidget *parent = nullptr);
    ~RegisterWindow();
    void initUI();

private slots:
    void registerTri();
    void RloginTri();
    void openTerm();//打开同意书

private:
    Ui::RegisterWindow *ui; // Ui 对象指针
    QLabel *usernameLabel; // 用户名标签
    QLabel *passwordLabel; // 密码标签
    QLabel *passwordLabel1; // 再次输入密码标签
    QLineEdit *usernameLineEdit; // 用户名输入框
    QLineEdit *passwordLineEdit; // 密码输入框
    QLineEdit *passwordLineEdit1; // 再次输入密码输入框
    QPushButton *registerButton; // 注册按钮
    QPushButton *RloginPushButton; // 返回登录界面按钮
    QLabel *TermLabel;
    QCheckBox *agreeCheckBox; // 同意条款复选框
};

#endif // REGISTERWINDOW_H
