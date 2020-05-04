#include "movieexportdialog.h"
#include "ui_movieexportdialog.h"
#include "framemanager.h"
#include "qgifimage.h"
#include <QFileDialog>

MovieExportDialog::MovieExportDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MovieExportDialog)
{
    ui->setupUi(this);
    QObject::connect(ui->btn_exportGIF, &QPushButton::clicked,
                     this, &MovieExportDialog::showMovieFilePath);
}

MovieExportDialog::~MovieExportDialog()
{
    delete ui;
}

void MovieExportDialog::showMovieFilePath()
{
    QString filename = QFileDialog::getSaveFileName(this, "Save Animation", QCoreApplication::applicationDirPath(), "GIF Files(*.gif);;");
    if(!filename.isNull())
    {
        generateGif(filename);
    }
}

bool MovieExportDialog::generateMovie(QString ffmpegPath, QString strOutputFile, std::function<void (float)> progress)
{

}

//Generates GIF by reading each frame. Please note that solution is not written with optimisation in mind
void MovieExportDialog::generateGif(QString gif_path)
{
    QGifImage gif(QSize(800, 400));

    int totalFrames = FrameManager::getInstance()->getTotalFrames();
    for(int i=0; i<totalFrames; i++)
    {
        QPixmap pm = FrameManager::getInstance()->getFramePixmap(i);
        QImage animationFrame = pm.toImage();
        gif.addFrame(animationFrame, 10);
    }
    gif.save(gif_path);
}

bool MovieExportDialog::executeFFMpeg(QString strCmd, std::function<void (float)> progress)
{

}
bool MovieExportDialog::checkInputParameters(const ExportMovieDesc &movieDesc)
{

}
