#ifndef CHANGEPICTUREDIALOG_H
#define CHANGEPICTUREDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QDir>
#include <QPushButton>
#include <QFileDialog>

class ChangePictureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePictureDialog(QWidget *parent = nullptr);
    QString getSelectedPicture() const;

private slots:
    void onItemDoubleClicked(QListWidgetItem *item);

private:
    QListWidget *pictureListWidget;
    QString selectedPicture;
};

#endif // CHANGEPICTUREDIALOG_H
