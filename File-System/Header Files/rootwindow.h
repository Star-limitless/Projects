#ifndef ROOTWINDOW_H
#define ROOTWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "fsstructure.h"
#include <QDebug>
#include "mainwindow.h"
#include <QIcon>

namespace Ui {
class RootWindow;
}

class RootWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit RootWindow(QWidget *parent = nullptr);
    ~RootWindow();

private slots:
    void showFSTree();
    void exitApplication(); // 新的槽函数用于退出应用程序

private:
    void initUI();

    Ui::RootWindow *ui;
    QMenu *menuFile;
    QAction *actionFSTree;
    QAction *actionExit; // 新的 QAction 用于退出
    QTextEdit *textEditTreeView;
};

#endif // ROOTWINDOW_H
