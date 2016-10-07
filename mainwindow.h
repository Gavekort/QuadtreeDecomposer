#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "videoprocessing.h"
#include "quantizer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    //Display video frame in player UI
    void updatePlayerUI(QImage img);
    void updateProgress(int value);
private:
    Ui::MainWindow *ui;
    VideoProcessing* vp;
    int quantization;
};

#endif // MAINWINDOW_H
