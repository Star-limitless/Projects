#include "createfiledialog.h"

CreateFileDialog::CreateFileDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle(tr("Create File"));

    QLabel *pathLabel = new QLabel(tr("File Path:"));
    pathLineEdit = new QLineEdit(this);

    QLabel *typeLabel = new QLabel(tr("File Type:"));
    fileTypeComboBox = new QComboBox(this);
    fileTypeComboBox->addItem("txt");
    fileTypeComboBox->addItem("pdf");

    okButton = new QPushButton(tr("OK"), this);
    cancelButton = new QPushButton(tr("Cancel"), this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QHBoxLayout *pathLayout = new QHBoxLayout();
    QHBoxLayout *typeLayout = new QHBoxLayout();
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    pathLayout->addWidget(pathLabel);
    pathLayout->addWidget(pathLineEdit);

    typeLayout->addWidget(typeLabel);
    typeLayout->addWidget(fileTypeComboBox);

    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    mainLayout->addLayout(pathLayout);
    mainLayout->addLayout(typeLayout);
    mainLayout->addLayout(buttonLayout);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
}

QString CreateFileDialog::getFilePath() const
{
    return pathLineEdit->text();
}

QString CreateFileDialog::getFileType() const
{
    return fileTypeComboBox->currentText();
}
