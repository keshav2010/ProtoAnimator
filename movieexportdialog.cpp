#include "movieexportdialog.h"
#include "ui_movieexportdialog.h"

MovieExportDialog::MovieExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieExportDialog)
{
    ui->setupUi(this);
}

MovieExportDialog::~MovieExportDialog()
{
    delete ui;
}
