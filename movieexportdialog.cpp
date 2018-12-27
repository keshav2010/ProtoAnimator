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

bool MovieExportDialog::generateMovie(QString ffmpegPath, QString strOutputFile, std::function<void (float)> progress)
{

}
bool MovieExportDialog::generateGif(QString ffmpeg, QString strOut, std::function<void (float)> progress)
{

}

bool MovieExportDialog::executeFFMpeg(QString strCmd, std::function<void (float)> progress)
{

}
bool MovieExportDialog::checkInputParameters(const ExportMovieDesc &movieDesc)
{

}
