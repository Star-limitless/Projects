#include "registerwindow.h"
#include "ui_registerwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

RegisterWindow::RegisterWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RegisterWindow)
    , usernameLabel(new QLabel("用户名", this))
    , passwordLabel(new QLabel("密码", this))
    , passwordLabel1(new QLabel("再次确认", this))
    , usernameLineEdit(new QLineEdit(this))
    , passwordLineEdit(new QLineEdit(this))
    , passwordLineEdit1(new QLineEdit(this))
    , RloginPushButton(new QPushButton("返回", this))
    , registerButton(new QPushButton("注册", this))
    , TermLabel(new QLabel("<a href=\"#\" style=\"color:blue;\">服务条款</a>", this)) // 创建带链接的标签
    , agreeCheckBox(new QCheckBox("", this)) // 创建复选框
{
    ui->setupUi(this);
    initUI(); //进行界面的初始化

    // 设置窗口标志，隐藏最大化和最小化按钮
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
}

RegisterWindow::~RegisterWindow()
{
    delete ui;
}

void RegisterWindow::initUI()
{
    //进行界面的初始化
    setWindowTitle("注册");

    // 设置背景图片
    setStyleSheet("RegisterWindow {"
                  "background-image: url(:/login_background1.jpg);"
                  "background-repeat: no-repeat;"
                  "background-position: center;"
                  "}");

    // 设置窗口的图标
    setWindowIcon(QIcon("://app-icon1.png"));

    usernameLineEdit->setFixedSize(100, 30);
    passwordLineEdit->setFixedSize(100, 30);
    passwordLineEdit1->setFixedSize(100, 30);
    usernameLabel->setFixedSize(80, 30);
    passwordLabel->setFixedSize(80, 30);
    passwordLabel1->setFixedSize(80, 30);
    registerButton->setFixedSize(80, 40);
    RloginPushButton->setFixedSize(80, 40);

    //设置为隐藏模式
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit1->setEchoMode(QLineEdit::Password);

    //设置输入框的四个角为弧形
    passwordLineEdit->setStyleSheet("border-radius: 10px; border: 1px solid #888;");
    passwordLineEdit1->setStyleSheet("border-radius: 10px; border: 1px solid #888;");
    usernameLineEdit->setStyleSheet("border-radius: 10px; border: 1px solid #888;");
    registerButton->setStyleSheet("border-radius: 10px;background-color:white;");
    RloginPushButton->setStyleSheet("border-radius: 10px;background-color:white");

    // 设置“服务条款”部分为超链接，允许点击
    TermLabel->setOpenExternalLinks(true);

    // 连接点击“服务条款”链接的信号到槽函数
    connect(TermLabel, &QLabel::linkActivated, this, &RegisterWindow::openTerm);

    // 创建一个 QVBoxLayout 用于将控件垂直排列
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->setContentsMargins(20, 20, 20, 20); // 设置中央布局的边距
    centralLayout->setSpacing(10); // 设置中央布局的控件间距

    // 创建一个 QGridLayout 用于布局用户名、密码等输入框和标签
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->setContentsMargins(10, 10, 10, 10); // 设置网格布局的边距
    gridLayout->setHorizontalSpacing(15); // 设置水平间距
    gridLayout->setVerticalSpacing(30); // 设置垂直间距

    // 设置标签字体
    QFont labelFont("Arial", 14, QFont::Bold);
    usernameLabel->setFont(labelFont);
    passwordLabel->setFont(labelFont);
    passwordLabel1->setFont(labelFont);

    QPalette palette;
    palette.setColor(QPalette::WindowText, Qt::white);
    usernameLabel->setPalette(palette);
    passwordLabel->setPalette(palette);
    passwordLabel1->setPalette(palette);

    // 调整标签和输入框的对齐方式，使它们居中对齐
    gridLayout->addWidget(usernameLabel, 0, 0, Qt::AlignRight | Qt::AlignVCenter);
    gridLayout->addWidget(usernameLineEdit, 0, 1, Qt::AlignLeft | Qt::AlignVCenter);
    gridLayout->addWidget(passwordLabel, 1, 0, Qt::AlignRight | Qt::AlignVCenter);
    gridLayout->addWidget(passwordLineEdit, 1, 1, Qt::AlignLeft | Qt::AlignVCenter);
    gridLayout->addWidget(passwordLabel1, 2, 0, Qt::AlignRight | Qt::AlignVCenter);
    gridLayout->addWidget(passwordLineEdit1, 2, 1, Qt::AlignLeft | Qt::AlignVCenter);


    // 创建水平布局来排列复选框和“我已阅读并同意服务条款”文本
    QHBoxLayout *termsLayout = new QHBoxLayout;
    termsLayout->setContentsMargins(10, 10, 10, 10); // 设置边距
    termsLayout->setSpacing(5); // 设置控件间距
    termsLayout->addWidget(agreeCheckBox); // 添加复选框
    termsLayout->addWidget(new QLabel("我已阅读并同意", this)); // 添加普通文本
    termsLayout->addWidget(TermLabel); // 添加服务条款链接

    // 创建一个 QHBoxLayout 用于管理登录和注册按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->setContentsMargins(10, 10, 10, 10); // 设置按钮布局的边距
    buttonLayout->setSpacing(20); // 设置按钮之间的间距
    buttonLayout->addWidget(registerButton);
    buttonLayout->addWidget(RloginPushButton);

    //创建表单布局来放置输入框和按钮等
    QWidget *formWidget = new QWidget(this);
    QVBoxLayout *formLayout = new QVBoxLayout(formWidget);
    formLayout->addLayout(gridLayout);
    formLayout->addLayout(termsLayout); // 添加服务条款布局
    formLayout->addLayout(buttonLayout); // 添加按钮布局
    formLayout->setContentsMargins(10, 10, 10, 10); // 设置表单布局的边距
    formLayout->setSpacing(15); // 设置表单布局的控件间距


    // 添加 QSpacerItem 以居中 formWidget
    centralLayout->addStretch();
    centralLayout->addWidget(formWidget, 0, Qt::AlignCenter);
    centralLayout->addStretch();


    // 创建一个中心窗口部件，并将布局设置为其布局
    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);

    // 设置窗口的最小大小
    setFixedSize(400, 500);

    connect(registerButton, &QPushButton::clicked, this, &RegisterWindow::registerTri);
    connect(RloginPushButton, &QPushButton::clicked, this, &RegisterWindow::RloginTri);
}

void RegisterWindow::registerTri()
{
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();
    QString passwordConfirm = passwordLineEdit1->text();

    // 用户名和密码格式验证
    QRegularExpression usernameRegex("^[a-zA-Z0-9]{3,15}$"); // 用户名应为3-15个字符，包含字母、数字和下划线
    QRegularExpression passwordRegex("^(?=.*[A-Za-z])(?=.*\\d)[A-Za-z\\d]{8,}$"); // 密码至少8个字符，包含至少一个字母和一个数字

    bool validUsername = usernameRegex.match(username).hasMatch();
    bool validPassword = passwordRegex.match(password).hasMatch();

    if (!validUsername || !validPassword) {
        QString errorMessage = "错误:\n";
        if (!validUsername) {
            errorMessage += "用户名应为5-15个字符，包含字母、数字\n";
        }
        if (!validPassword) {
            errorMessage += "密码应至少8个字符，包含至少一个字母和一个数字\n";
        }
        QMessageBox::warning(this, "注册错误", errorMessage);
        return;
    }

    if (password != passwordConfirm) {
        QMessageBox::warning(this, "注册错误", "两次输入的密码不一致！");
        return;
    }

    // 创建目录路径
    QString userDirPath = QDir::currentPath() + "/USERS";//用户目录
    QString userInfoFilePath = userDirPath + "/Info/user.txt";//用户信息文件
    QString userFolderPath = userDirPath + "/" + username;//用户的专属目录
    QString userInfoFolderPath = userDirPath + "/Info/" + username;//用户文件信息的存放地点
    QString userInfoPath = userDirPath + "/Info/root/users.txt";//存放用户名称的文件

    qDebug() << "Current Path: " << QDir::currentPath();

    QDir dir;
    if (!dir.exists(userDirPath + "/Info")) {
        dir.mkpath(userDirPath + "/Info");
    }

    // 检查 user.txt 文件是否存在，如果不存在则创建它
    QFile userFile(userInfoFilePath);
    if (!userFile.exists()) {
        if (!userFile.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "注册错误", "无法创建用户信息文件！");
            return;
        }
        userFile.close();
    }


    //检查 users.txt中的文件是否存在，如果不存在创建
    QFile usersFile(userInfoPath);
    if(!usersFile.exists()){
        if(!usersFile.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this, "错误", "文件不存在");
            return;
        }
        usersFile.close();
    }


    // 检查用户名是否已经存在
    if (userFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&userFile);
        QString line;
        while (in.readLineInto(&line)) {
            QStringList userDetails = line.split(" ");
            if (userDetails.size() >= 2 && userDetails[0] == username) {
                QMessageBox::warning(this, "注册错误", "用户名已存在，请选择其他用户名！");
                userFile.close();
                return;
            }
        }
        userFile.close();
    } else {
        QMessageBox::warning(this, "注册错误", "无法读取用户信息文件！");
        return;
    }

    // 将用户名和密码写入 user.txt 文件
    if (userFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&userFile);
        out << username << " " << password << "\n";
        userFile.close();
    } else {
        QMessageBox::warning(this, "注册错误", "无法写入用户信息文件！");
        return;
    }

    //蒋用户名写入 users.txt文件中
    if(usersFile.open(QIODevice::Append | QIODevice::Text)){
        QTextStream output(&usersFile);
        output << username << "\n";
        usersFile.close();
    }
    else{
        QMessageBox::warning(this, "注册错误", "无法写入用户信息文件！");
        return;
    }

    // 创建用户文件夹
    if (!dir.exists(userFolderPath)) {
        if (!dir.mkpath(userFolderPath)) {
            QMessageBox::warning(this, "注册错误", "无法创建用户文件夹！");
            return;
        }
    }

    // 在 USERS/Info 目录下创建以用户名为名称的文件夹，并创建 FileTree.txt 和 FileDetail.txt 文件
    if (!dir.exists(userInfoFolderPath)) {
        if (!dir.mkpath(userInfoFolderPath)) {
            QMessageBox::warning(this, "注册错误", "无法创建用户信息文件夹！");
            return;
        }

        QFile filePathFile(userInfoFolderPath + "/FileDetail.txt");
        if (!filePathFile.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "注册错误", "无法创建 FileDetail.txt 文件！");
            return;
        }
        filePathFile.close();

        QFile detailFile(userInfoFolderPath + "/FileTree.txt");
        if (!detailFile.open(QIODevice::WriteOnly)) {
            QMessageBox::warning(this, "注册错误", "无法创建 FileTree.txt 文件！");
            return;
        }
        detailFile.close();
    }

    QMessageBox::information(this, "注册成功", "注册成功！");

    // 返回登录窗口
    this->close();
    MainWindow *mainwindow1 = new MainWindow;
    mainwindow1->show();


}

void RegisterWindow::RloginTri(){
    // QMessageBox::information(this, tr("RloginTri"), tr("Rlogin action"));
    // 返回到登录界面的逻辑
    this->close();
    MainWindow *mainWindow = new MainWindow;
    mainWindow->show();
}

void RegisterWindow::openTerm(){
    QString filePath = QDir::currentPath() + "/path/to/terms.html"; // 替换为实际路径
    QUrl url = QUrl::fromLocalFile(filePath); // 创建本地文件的 URL
    QDesktopServices::openUrl(url); // 打开服务条款文件
    agreeCheckBox->setChecked(true); // 自动勾选复选框
}
