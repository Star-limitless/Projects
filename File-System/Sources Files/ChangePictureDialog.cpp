#include "changepicturedialog.h"

ChangePictureDialog::ChangePictureDialog(QWidget *parent)
    : QDialog(parent), selectedPicture("")
{
    setWindowTitle(tr("选择头像"));
    setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(this);
    pictureListWidget = new QListWidget(this);
    layout->addWidget(pictureListWidget);

    QDir dir(":/");  // 这里的路径需要更改为实际存储图片的路径
    QStringList filters;
    filters << "*.png" << "*.jpg" << "*.jpeg";
    dir.setNameFilters(filters);
    QFileInfoList fileList = dir.entryInfoList();

    foreach (QFileInfo fileInfo, fileList) {
        QListWidgetItem *item = new QListWidgetItem(fileInfo.fileName(), pictureListWidget);
        item->setData(Qt::UserRole, fileInfo.absoluteFilePath());
    }

    connect(pictureListWidget, &QListWidget::itemDoubleClicked, this, &ChangePictureDialog::onItemDoubleClicked);
}

QString ChangePictureDialog::getSelectedPicture() const
{
    return selectedPicture;
}

void ChangePictureDialog::onItemDoubleClicked(QListWidgetItem *item)
{
    selectedPicture = item->data(Qt::UserRole).toString();
    accept();
}
