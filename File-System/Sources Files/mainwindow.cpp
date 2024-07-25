#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "userwindow.h"
#include "./ui_userwindow.h"
#include "registerwindow.h"
#include "./ui_registerwindow.h"
#include "rootwindow.h"
#include "./ui_rootwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , usernameLabel(new QLabel("用户名", this)) // 创建用户名标签
    , passwordLabel(new QLabel("密 码", this)) // 创建密码标签
    , usernameLineEdit(new QLineEdit(this)) // 创建用户名输入框
    , passwordLineEdit(new QLineEdit(this)) // 创建密码输入框
    , logining(new QPushButton("登录", this)) // 创建登录按钮
    , registering(new QPushButton("注册", this)) // 创建注册按钮
    , avatarLabel(new QLabel(this)) // 创建头像标签
    , termsCheckBox(new QCheckBox("", this)) // 创建复选框
    , termsLabel(new QLabel("<a href=\"#\" style=\"color:blue;\">服务条款</a>", this)) // 创建带链接的标签
{
    ui->setupUi(this); // 设置 UI
    initUI(); // 初始化用户界面

    // 设置窗口标志，隐藏最大化和最小化按钮
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

MainWindow::~MainWindow()
{
    delete ui; // 删除 UI 对象
}

void MainWindow::initUI()
{
    setWindowTitle("登录"); // 设置窗口标题为“登录”

    // 设置窗口的背景图片
    setStyleSheet("MainWindow {"
                  "background-image: url(:/login_background1.jpg);"
                  "background-repeat: no-repeat;"
                  "background-position: center;"
                  "}");

    // 设置窗口的图标
    setWindowIcon(QIcon("://app-icon1.png"));

    // 设置控件的固定大小
    usernameLineEdit->setFixedSize(100, 30);
    passwordLineEdit->setFixedSize(100, 30);
    usernameLabel->setFixedSize(60, 30);
    passwordLabel->setFixedSize(60, 30);
    logining->setFixedSize(80, 40);
    registering->setFixedSize(80, 40);
    avatarLabel->setFixedSize(150, 150);

    // 设置密码输入框为密码模式
    passwordLineEdit->setEchoMode(QLineEdit::Password);

    // 加载头像图片，并设置为圆形
    QPixmap pixmap("://T1.jpg");
    QBitmap mask(pixmap.size());
    mask.fill(Qt::color0);
    QPainter painter(&mask);
    painter.setBrush(Qt::color1);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(0, 0, pixmap.width(), pixmap.height());
    pixmap.setMask(mask);
    QPixmap scaledPixmap = pixmap.scaled(150, 150, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    avatarLabel->setPixmap(scaledPixmap);

    // 设置输入框的圆角
    usernameLineEdit->setStyleSheet("border-radius: 10px; border: 1px solid #888;");
    passwordLineEdit->setStyleSheet("border-radius: 10px; border: 1px solid #888;");

    // 设置“服务条款”部分为超链接，允许点击
    termsLabel->setOpenExternalLinks(true);

    // 连接点击“服务条款”链接的信号到槽函数
    connect(termsLabel, &QLabel::linkActivated, this, &MainWindow::openTerms);

    // 创建垂直布局来排列控件
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->setContentsMargins(20, 20, 20, 20); // 设置边距
    centralLayout->setSpacing(10); // 设置控件间距

    // 创建网格布局来安排标签和输入框
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setContentsMargins(10, 10, 10, 10); // 设置边距
    gridLayout->setHorizontalSpacing(15); // 设置水平间距
    gridLayout->setVerticalSpacing(30); // 设置垂直间距

    // 设置标签字体
    QFont labelFont("Arial", 14, QFont::Bold);
    usernameLabel->setFont(labelFont);
    passwordLabel->setFont(labelFont);

    // 设置标签的字体颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    usernameLabel->setPalette(palette);
    passwordLabel->setPalette(palette);

    // 将控件添加到网格布局中
    gridLayout->addWidget(usernameLabel, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
    gridLayout->addWidget(usernameLineEdit, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);
    gridLayout->addWidget(passwordLabel, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
    gridLayout->addWidget(passwordLineEdit, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);

    // 创建水平布局来排列复选框和“我已阅读并同意服务条款”文本
    QHBoxLayout *termsLayout = new QHBoxLayout;
    termsLayout->setContentsMargins(10, 10, 10, 10); // 设置边距
    termsLayout->setSpacing(5); // 设置控件间距
    termsLayout->addWidget(termsCheckBox); // 添加复选框
    termsLayout->addWidget(new QLabel("我已阅读并同意", this)); // 添加普通文本
    termsLayout->addWidget(termsLabel); // 添加服务条款链接

    // 创建水平布局来排列登录和注册按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setContentsMargins(10, 10, 10, 10); // 设置边距
    buttonLayout->setSpacing(20); // 设置按钮间距
    buttonLayout->addWidget(logining); // 添加登录按钮
    buttonLayout->addWidget(registering); // 添加注册按钮

    // 创建表单布局来包含头像、输入框和按钮
    QWidget *formWidget = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    formLayout->setContentsMargins(10, 10, 10, 10); // 设置边距
    formLayout->setSpacing(15); // 设置控件间距
    formLayout->addWidget(avatarLabel, 0, Qt::AlignCenter); // 添加头像到布局中
    formLayout->addLayout(gridLayout); // 添加网格布局
    formLayout->addLayout(termsLayout); // 添加服务条款布局
    formLayout->addLayout(buttonLayout); // 添加按钮布局

    // 使用 QSpacerItem 来使 formWidget 居中
    centralLayout->addStretch();
    centralLayout->addWidget(formWidget, 0, Qt::AlignCenter);
    centralLayout->addStretch();

    // 创建中心窗口部件，并设置布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    // 设置窗口的最小尺寸
    setMinimumSize(400, 500);
    setFixedSize(400, 500);

    // 连接按钮的点击信号到对应的槽函数
    connect(logining, &QPushButton::clicked, this, &MainWindow::loginPushButton);
    connect(registering, &QPushButton::clicked, this, &MainWindow::registerPushButton);
}

void MainWindow::loginPushButton()
{
    // 获取用户名和密码
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();

    // 检查用户名和密码是否为空
    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "登录错误", "用户名或密码不能为空");
        return;
    }

    // 检查用户是否同意服务条款
    if (!termsCheckBox->isChecked()) {
        QMessageBox::warning(this, "登录错误", "请先同意服务条款");
        return;
    }

    // 读取用户信息文件的路径
    QString userDirPath = QDir::currentPath() + "/USERS/Info";
    QString userInfoFilePath = userDirPath + "/user.txt";

    // 打开用户信息文件
    QFile userFile(userInfoFilePath);
    if (!userFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "登录错误", "无法打开用户信息文件！");
        return;
    }

    bool loggedIn = false; // 登录状态
    QTextStream in(&userFile);
    // 逐行读取用户信息
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList userDetails = line.split(" ");
        // 验证用户名和密码是否匹配
        if (userDetails.size() >= 2 && userDetails[0] == username && userDetails[1] == password) {
            loggedIn = true; // 登录成功
            break;
        }
    }
    userFile.close();

    // 根据登录状态显示提示信息或打开用户界面
    if (loggedIn) {
        this->close(); // 关闭当前登录窗口

        if(username == "root"){
            RootWindow *rootwindow = new RootWindow();
            rootwindow->show();//打开管理员窗口
        }
        else{
            UserWindow *userwindow = new UserWindow(username); // 创建用户窗口
            userwindow->show(); // 显示用户窗口
        }

    } else {
        QMessageBox::warning(this, "登录错误", "用户名或密码错误"); // 登录失败提示
    }
}

void MainWindow::registerPushButton()
{
    this->close(); // 关闭当前登录窗口
    RegisterWindow *registerwindow = new RegisterWindow; // 创建注册窗口
    registerwindow->show(); // 显示注册窗口
}

void MainWindow::openTerms()
{
    QString filePath = QDir::currentPath() + "/path/to/terms.html"; // 替换为实际路径
    QUrl url = QUrl::fromLocalFile(filePath); // 创建本地文件的 URL
    QDesktopServices::openUrl(url); // 打开服务条款文件
    termsCheckBox->setChecked(true); // 自动勾选复选框
}
