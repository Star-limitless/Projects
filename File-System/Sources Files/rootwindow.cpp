#include "rootwindow.h"
#include "ui_rootwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDir>
#include <fstream>
#include <sstream>

// 初始化函数
RootWindow::RootWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::RootWindow)
{
    ui->setupUi(this);
    initUI();
}

// 析构函数
RootWindow::~RootWindow()
{
    delete ui;
}

// 设置菜单的函数
void RootWindow::initUI()
{
    setWindowTitle("root");
    setWindowIcon(QIcon(":/app-icon1.png"));
    // 设置窗口的背景图片
    setStyleSheet("RootWindow {"
                  "background-image: url(:/login_background1.jpg);"
                  "background-repeat: no-repeat;"
                  "background-position: center;"
                  "}");

    menuFile = menuBar()->addMenu(tr("File"));

    actionFSTree = new QAction(tr("FStree"), this);
    menuFile->addAction(actionFSTree);
    connect(actionFSTree, &QAction::triggered, this, &RootWindow::showFSTree);

    actionExit = new QAction(tr("Exit"), this); // 创建退出操作
    menuFile->addAction(actionExit);
    connect(actionExit, &QAction::triggered, this, &RootWindow::exitApplication); // 连接退出操作

    // 初始化 QTextEdit
    textEditTreeView = new QTextEdit(this);
    setCentralWidget(textEditTreeView); // 设置 textEditTreeView 为中央小部件



}

// 显示文件树结构的槽函数
void RootWindow::showFSTree()
{
    QString usersFilePath = QDir::currentPath() + "/USERS/Info/root/users.txt";

    // 读取所有用户名
    std::ifstream usersFile(usersFilePath.toStdString());
    if (!usersFile.is_open()) {
        textEditTreeView->setPlainText("Failed to open users.txt");
        return;
    }

    std::string username;
    std::ostringstream oss; // 用于累计所有用户的文件树结构

    while (std::getline(usersFile, username)) {
        qDebug() << QString::fromStdString(username);

        // 为每个用户创建一个新的 Trie 对象
        Trie trie;

        QString filePath = QDir::currentPath() + "/USERS/Info/" + QString::fromStdString(username) + "/FileTree.txt";
        readAndInsertPaths(filePath.toStdString(), trie);

        // 将当前用户的 Trie 结构打印到字符串流中并追加到总的输出中
        oss << "User: " << username << "\n";
        std::ostringstream userOss;
        trie.printToStream(userOss);
        oss << userOss.str() << "\n\n";
    }
    usersFile.close();

    // 显示所有用户的文件树结构
    textEditTreeView->setPlainText(QString::fromStdString(oss.str()));
}

// 退出应用程序的槽函数
void RootWindow::exitApplication()
{
    this->close(); // 关闭窗口，退出应用程序
    //打开登录界面
    MainWindow *mainwindow = new MainWindow();
    mainwindow->show();


}
