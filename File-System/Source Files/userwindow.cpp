#include "userwindow.h"
#include "ui_userwindow.h"
#include "mainwindow.h"
#include "createfiledialog.h"
#include <QFileDialog>
#include <QTextEdit>
#include <QFile>
#include <QTextStream>
#include <QInputDialog>

UserWindow::UserWindow(const QString &username, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UserWindow)
    , CurrentUser(username)
{
    ui->setupUi(this);
    setWindowTitle(username);
    setWindowIcon(QIcon(":/app-icon1.png"));

    // 初始化 QLabel 显示时间
    timeLabel = new QLabel(this);
    timeLabel->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    statusBar()->addWidget(timeLabel); // 将 QLabel 添加到状态栏

    // 初始化 QTimer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &UserWindow::updateTime);
    timer->start(1000); // 每秒更新时间


    // 创建菜单和动作
    fileMenu = menuBar()->addMenu(tr("File"));

    createMenu = new QMenu(tr("Create"), this);
    UserWindowhelp = new QMenu(tr("help"), this);
    Introduce = new QAction(tr("introduce"), this);
    UserWindowdeleteUser = new QAction(tr("Logout"), this);

    createTxtAction = new QAction(tr("txt"), this);
    createFolderAction = new QAction(tr("Folder"), this);
    createMenu->addAction(createTxtAction);
    createMenu->addAction(createFolderAction);

    deleteAction = new QAction(tr("Delete"), this);
    searchAction = new QAction(tr("Search"), this);
    saveAction = new QAction(tr("Save"), this);
    renameAction = new QAction(tr("Rename"), this);  // 创建 Rename 动作
    logoutAction = new QAction(tr("quit"), this);
    UserWindowLookTreeAction = new QAction(tr("FsTree"), this);


    // 添加动作到菜单
    fileMenu->addMenu(createMenu);
    fileMenu->addAction(deleteAction);
    fileMenu->addAction(searchAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(renameAction);  // 添加 Rename 动作到菜单
    menuBar()->addAction(logoutAction);
    fileMenu->addAction(UserWindowLookTreeAction);
    menuBar()->addMenu(UserWindowhelp);
    UserWindowhelp->addAction(Introduce);
    menuBar()->addAction(UserWindowdeleteUser);
    // 连接动作到槽函数
    connect(UserWindowLookTreeAction, &QAction::triggered, this, &UserWindow::UserWindowLookTree);
    connect(createTxtAction, &QAction::triggered, this, &UserWindow::createTxtFile);
    connect(createFolderAction, &QAction::triggered, this, &UserWindow::createFolder);
    connect(deleteAction, &QAction::triggered, this, &UserWindow::deleteFile);
    connect(searchAction, &QAction::triggered, this, &UserWindow::searchFile);
    connect(saveAction, &QAction::triggered, this, &UserWindow::saveFile);
    connect(renameAction, &QAction::triggered, this, &UserWindow::renameFile);  // 连接 Rename 动作
    connect(logoutAction, &QAction::triggered, this, &UserWindow::logout);
    connect(Introduce, &QAction::triggered, this, &UserWindow::introducebook);
    connect(UserWindowdeleteUser, &QAction::triggered, this, &UserWindow::deleteUserInformation);//删除用户信息

    // 创建工具栏和动作
    toolBar = addToolBar(tr("Toolbar"));
    homeAction = new QAction(QIcon(":/home.jpg"), tr("Home"), this);
    editAction = new QAction(QIcon(":/Editor.jpg"), tr("Edit"), this);
    toolBar->addAction(homeAction);
    toolBar->addAction(editAction);

    // 设置工具栏方向为垂直
    toolBar->setOrientation(Qt::Vertical);

    // 将工具栏停靠在左侧
    addToolBar(Qt::LeftToolBarArea, toolBar);

    // 连接工具栏动作到槽函数
    connect(homeAction, &QAction::triggered, this, &UserWindow::goHome);
    connect(editAction, &QAction::triggered, this, &UserWindow::editFile);

    goHome();
}

UserWindow::~UserWindow()
{
    delete ui;
}

void UserWindow::createTxtFile()
{
    // 弹出对话框获取文件名
    bool ok;
    QString fileName = QInputDialog::getText(this, tr("Create txt File"),
                                             tr("File Name:"), QLineEdit::Normal,
                                             "", &ok);

    if (ok && !fileName.isEmpty()) {
        // 检查文件名是否包含后缀
        if (!fileName.endsWith(".txt")) {
            fileName += ".txt";
        }

        // 构造文件路径
        QString dirPath = QDir::currentPath() + "/USERS/" + CurrentUser;
        QString filePath = QDir(dirPath).filePath(fileName);

        // 确保目录存在
        QDir dir;
        if (!dir.exists(dirPath)) {
            dir.mkpath(dirPath);
        }

        // 创建文件
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.close();
            QMessageBox::information(this, tr("创建成功"), tr("txt 文件创建成功！"));

            // 记录文件路径信息到 FileTree.txt
            QString infoFilePath = QDir::currentPath() + "/USERS/Info/" + CurrentUser + "/FileTree.txt";
            QFile infoFile(infoFilePath);
            if (infoFile.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&infoFile);
                out << CurrentUser + "/" + fileName << "\n";
                infoFile.close();
            } else {
                QMessageBox::warning(this, tr("记录失败"), tr("无法记录文件路径信息！"));
            }
        } else {
            QMessageBox::warning(this, tr("创建失败"), tr("无法创建 txt 文件！"));
        }
    }
}



void UserWindow::createPdfFile()
{
    QMessageBox::information(this, tr("Create"), tr("Create pdf file: "));
    // 添加创建pdf文件的逻辑
}

void UserWindow::createFolder()
{
    // 弹出对话框获取文件夹名称
    bool ok;
    QString folderName = QInputDialog::getText(this, tr("Create Folder"),
                                               tr("Folder Name:"), QLineEdit::Normal,
                                               "", &ok);

    if (ok && !folderName.isEmpty()) {
        // 构造文件夹路径
        QString dirPath = QDir::currentPath() + "/USERS/" + CurrentUser;
        QString folderPath = QDir(dirPath).filePath(folderName);

        // 确保目录存在
        QDir dir;
        if (!dir.exists(dirPath)) {
            dir.mkpath(dirPath);
        }

        // 创建文件夹
        if (dir.mkpath(folderPath)) {
            QMessageBox::information(this, tr("创建成功"), tr("文件夹创建成功！"));

            // 记录文件夹路径信息到 FileTree.txt
            QString infoFilePath = QDir::currentPath() + "/USERS/Info/" + CurrentUser + "/FileTree.txt";
            QFile infoFile(infoFilePath);
            if (infoFile.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream out(&infoFile);
                out << CurrentUser + "/" + folderName << "\n";
                infoFile.close();
            } else {
                QMessageBox::warning(this, tr("记录失败"), tr("无法记录文件夹路径信息！"));
            }
        } else {
            QMessageBox::warning(this, tr("创建失败"), tr("无法创建文件夹！"));
        }
    }
}


void UserWindow::deleteFile()
{
    // 弹出对话框获取文件名
    bool ok;
    QString fileName = QInputDialog::getText(this, tr("Delete File"),
                                             tr("File Name (e.g., a.txt):"), QLineEdit::Normal,
                                             "", &ok);

    if (ok && !fileName.isEmpty()) {
        // 构造文件的绝对路径
        QString dirPath = QDir::currentPath() + "/USERS/" + CurrentUser;//文件的绝对路径
        QString fullFilePath;
        QString infoFilePath = QDir::currentPath() + "/USERS/Info/" + CurrentUser + "/FileTree.txt";

        QFile infoFile(infoFilePath);
        if (infoFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
            QStringList lines;
            QTextStream in(&infoFile);
            while (!in.atEnd()) {
                QString line = in.readLine();
                if (line.contains(CurrentUser + "/" + fileName)) {
                    fullFilePath = line.mid(CurrentUser.length() + 1);  // 获取相对路径
                } else {
                    lines.append(line);
                }
            }
            infoFile.close();

            // 重写 FileTree.txt 文件
            if (infoFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QTextStream out(&infoFile);
                for (const QString &line : lines) {
                    out << line << "\n";
                }
                infoFile.close();
            } else {
                QMessageBox::warning(this, tr("记录失败"), tr("无法重写 FileTree.txt 文件！"));
                return;
            }
        } else {
            QMessageBox::warning(this, tr("读取失败"), tr("无法读取 FileTree.txt 文件！"));
            return;
        }

        if (!fullFilePath.isEmpty()) {
            QString filePath = QDir(dirPath).filePath(fullFilePath);

            // 删除文件或文件夹
            QFileInfo fileInfo(filePath);
            bool removed = false;
            if (fileInfo.isFile()) {
                QFile file(filePath);
                removed = file.remove();
            } else if (fileInfo.isDir()) {
                QDir dir(filePath);
                removed = dir.removeRecursively();
            }

            if (removed) {
                QMessageBox::information(this, tr("删除成功"), tr("文件或文件夹删除成功！"));
            } else {
                QMessageBox::warning(this, tr("删除失败"), tr("无法删除文件或文件夹！"));
            }
        } else {
            QMessageBox::warning(this, tr("文件未找到"), tr("未找到指定的文件！"));
        }
    }
}



void UserWindow::searchFile()
{
    // 弹出对话框获取文件名
    bool ok;
    QString searchText = QInputDialog::getText(this, tr("Search File"),
                                               tr("File Name (part of name):"), QLineEdit::Normal,
                                               "", &ok);

    if (ok && !searchText.isEmpty()) {
        // 构造 FileTree.txt 的路径
        QString filePath = QDir::currentPath() + "/USERS/Info/" + CurrentUser + "/FileTree.txt";

        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QMessageBox::warning(this, tr("Read Error"), tr("Unable to open FileTree.txt!"));
            return;
        }

        // 存储匹配的文件路径
        QStringList matchingFiles;
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (line.contains(searchText, Qt::CaseInsensitive)) {
                matchingFiles.append(line);
            }
        }
        file.close();

        // 如果找到了匹配的文件，显示在文本编辑器中
        if (!matchingFiles.isEmpty()) {
            QTextEdit* resultTextEdit = new QTextEdit(this);
            resultTextEdit->setReadOnly(true); // 设置为只读模式
            resultTextEdit->setText(matchingFiles.join("\n"));
            setCentralWidget(resultTextEdit);
        } else {
            QMessageBox::information(this, tr("No Results"), tr("No files found with the given name."));
        }
    }
}


void UserWindow::saveFile()
{
    if (currentFilePath.isEmpty()) {
        QMessageBox::warning(this, tr("No File Open"), tr("No file is currently open."));
        return;
    }

    QFile file(currentFilePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
        QMessageBox::information(this, tr("Save"), tr("File saved successfully."));
    } else {
        QMessageBox::warning(this, tr("Save Error"), tr("Unable to save the file."));
    }
}

void UserWindow::renameFile()
{
    if (currentFilePath.isEmpty()) {
        QMessageBox::warning(this, tr("No File Open"), tr("No file is currently open."));
        return;
    }

    bool ok;
    QString newFileName = QInputDialog::getText(this, tr("Rename File"),
                                                tr("New file name:"), QLineEdit::Normal,
                                                QFileInfo(currentFilePath).fileName(), &ok);
    if (ok && !newFileName.isEmpty()) {
        QString newFilePath = QFileInfo(currentFilePath).absolutePath() + '/' + newFileName;
        if (QFile::rename(currentFilePath, newFilePath)) {
            currentFilePath = newFilePath;
            QMessageBox::information(this, tr("Rename"), tr("File renamed successfully."));
        } else {
            QMessageBox::warning(this, tr("Rename Error"), tr("Unable to rename the file."));
        }
    }
}

void UserWindow::logout()
{
    QMessageBox::information(this, tr("Logout"), tr("Logout action"));
    // 添加退出登录的逻辑
    this->close();
    // 可以在这里打开登录窗口
    MainWindow *RMainWindow = new MainWindow;
    RMainWindow->show();
}

void UserWindow::goHome()
{
    // 创建一个新的中心窗口小部件
    homeWidget = new QWidget(this);

    setStyleSheet("UserWindow {"
                  "background-image: url(://login_background1.jpg);"
                  "background-repeat: no-repeat;"
                  "background-position: center;"
                  "background-size: cover;"
                  "}");

    // 设置背景颜色
    // homeWidget->setStyleSheet("background-color: lightblue;");

    QHBoxLayout *layout = new QHBoxLayout(homeWidget);

    // 创建按钮
    createFileButton = new QPushButton(tr("Create File"), homeWidget);
    openFileButton = new QPushButton(tr("Open File"), homeWidget);

    createFileButton->setFixedSize(100, 30);
    openFileButton->setFixedSize(100, 30);

    // 添加按钮到布局
    layout->addWidget(createFileButton);
    layout->addWidget(openFileButton);

    // 连接按钮到槽函数
    connect(createFileButton, &QPushButton::clicked, this, &UserWindow::showCreateFileDialog);
    connect(openFileButton, &QPushButton::clicked, this, &UserWindow::openFile);

    // 设置新的中心窗口小部件
    setCentralWidget(homeWidget);
}


void UserWindow::editFile()
{
    if (currentFilePath.isEmpty()) {
        QMessageBox::warning(this, tr("No File Open"), tr("No file is currently open."));
        return;
    }

    QFile file(currentFilePath);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        textEdit = new QTextEdit(this);
        textEdit->setText(in.readAll());
        file.close();

        setCentralWidget(textEdit);
    } else {
        QMessageBox::warning(this, tr("Open Error"), tr("Unable to open the file."));
    }
}

void UserWindow::showCreateFileDialog()
{
    CreateFileDialog dialog(this);
    dialog.setFixedSize(300, 200);
    if (dialog.exec() == QDialog::Accepted) {
        QString filePath = dialog.getFilePath();
        QString fileType = dialog.getFileType();

        if (filePath.isEmpty()) {
            QMessageBox::warning(this, tr("Invalid Path"), tr("File path cannot be empty."));
            return;
        }

        if (fileType == "txt") {
            createTxtFile();
        } else if (fileType == "pdf") {
            createPdfFile();
        }
    }
}

void UserWindow::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"));
    if (!filePath.isEmpty()) {
        currentFilePath = filePath;
        QMessageBox::information(this, tr("Open File"), tr("File opened: ") + filePath);
        editFile();  // 自动打开文件进行编辑
    }
}


void UserWindow::UserWindowLookTree()
{
    // 创建 Trie 对象
    Trie trie;

    // 读取 FileTree.txt 文件并插入到 Trie 中
    QString filePath = QDir::currentPath() + "/USERS/Info/" + CurrentUser + "/FileTree.txt";
    readAndInsertPaths(filePath.toStdString(), trie);

    // 打印树结构
    std::ostringstream oss;
    trie.printToStream(oss);  // 使用输出流打印树结构
    QString treeStructure = QString::fromStdString(oss.str());

    // 创建一个文本编辑器来展示树结构
    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setText(treeStructure);
    textEdit->setReadOnly(true);
    setCentralWidget(textEdit);
}

void UserWindow::introducebook()
{
    // 构造 Introduce.txt 文件的路径
    QString introduceFilePath = QDir::currentPath() + "/USERS/Info/Introduce.txt";

    // 读取文件内容
    QFile file(introduceFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("读取失败"), tr("无法打开 Introduce.txt 文件！"));
        return;
    }

    QTextStream in(&file);
    QString introduceText = in.readAll();
    file.close();

    // 创建一个文本编辑器来展示说明书内容
    QTextEdit* textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true); // 设置为只读模式
    textEdit->setText(introduceText);

    // 创建一个新的窗口来显示说明书内容
    QMainWindow* introduceWindow = new QMainWindow(this);
    introduceWindow->setWindowTitle(tr("说明书"));
    introduceWindow->setCentralWidget(textEdit);
    introduceWindow->resize(600, 400); // 设置窗口大小
    introduceWindow->show();
}

void UserWindow::updateTime()
{
    QTime currentTime = QTime::currentTime();
    timeLabel->setText(currentTime.toString("hh:mm:ss")); // 设置时间格式
}

void UserWindow::deleteUserInformation()
{
    // 删除用户目录中的所有文件和文件夹
    QString userDirPath = QDir::currentPath() + "/USERS/" + CurrentUser;
    QDir userDir(userDirPath);
    if (userDir.exists()) {
        userDir.removeRecursively();
    }


    QString userfilePath = QDir::currentPath() + "/USERS/Info/" + CurrentUser;
    QDir UsersFile(userfilePath);
    if(UsersFile.exists()){
        UsersFile.removeRecursively();
    }

    // 从 user.txt 文件中删除当前用户的信息
    QString userInfoFilePath = QDir::currentPath() + "/USERS/Info/user.txt";
    QFile userInfoFile(userInfoFilePath);
    if (userInfoFile.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QStringList lines;
        QTextStream in(&userInfoFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            if (!line.contains(CurrentUser)) {
                lines.append(line);
            }
        }
        userInfoFile.resize(0); // 清空文件
        QTextStream out(&userInfoFile);
        for (const QString &line : lines) {
            out << line << "\n";
        }
        userInfoFile.close();
        logout();
    } else {
        QMessageBox::warning(this, tr("删除失败"), tr("无法打开 user.txt 文件！"));
    }
}
