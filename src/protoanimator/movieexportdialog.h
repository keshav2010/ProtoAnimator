#ifndef MOVIEEXPORTDIALOG_H
#define MOVIEEXPORTDIALOG_H

#include <QDialog>
#include<QSize>
#include<QString>
#include<QTemporaryDir>
#include<QProcess>

namespace Ui {
class MovieExportDialog;
}

struct ExportMovieDesc
{
    QString strFileName;
    int     startFrame = 0;
    int     endFrame = 0;
    int     fps = 12;
    QSize   exportSize{ 0, 0 };
};


class MovieExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MovieExportDialog(QWidget *parent = 0);
    ~MovieExportDialog();

private slots:
    void showMovieFilePath();

private:
    Ui::MovieExportDialog *ui;

    ExportMovieDesc mDesc;

    bool generateMovie(QString ffmpegPath, QString strOutputFile, std::function<void(float)> progress);
    void generateGif(QString);

    bool executeFFMpeg(QString strCmd, std::function<void(float)> progress);
    bool executeFFMpegPipe(QString strCmd, std::function<void(float)> progress, std::function<bool(QProcess&, int)> writeFrame);
    bool checkInputParameters(const ExportMovieDesc&);
};

#endif // MOVIEEXPORTDIALOG_H

