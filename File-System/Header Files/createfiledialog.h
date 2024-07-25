#ifndef CREATEFILEDIALOG_H
#define CREATEFILEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

class CreateFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateFileDialog(QWidget *parent = nullptr);

    QString getFilePath() const;
    QString getFileType() const;

private:
    QLineEdit *pathLineEdit;
    QComboBox *fileTypeComboBox;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // CREATEFILEDIALOG_H
