#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    vp = new VideoProcessing();
    ui->setupUi(this);

    QObject::connect(vp, SIGNAL(processedImage(QImage)),
                              this, SLOT(updatePlayerUI(QImage)));
    QObject::connect(ui->quantizer, SIGNAL(valueChanged(int)),
                              this, SLOT(updateProgress(int)));
    vp->loadVideo(&quantization);
    vp->Play();
}

MainWindow::~MainWindow()
{
    delete vp;
    delete ui;
}

void MainWindow::updatePlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->label->setAlignment(Qt::AlignCenter);
        ui->label->setPixmap(QPixmap::fromImage(img).scaled(ui->label->size(),
                                           Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::updateProgress(int value){
    ui->sliderlabel->setText(QString::number(value));
    quantization = value;
}
