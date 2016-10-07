#ifndef VIEWWIDGET_H
#define VIEWWIDGET_H

#include <QWidget>
#include "videoprocessing.h"

namespace Ui {
class ViewWidget;
}

class ViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ViewWidget(QWidget *parent = 0);
    ~ViewWidget();
    void SetImage(QImage &img);
private slots:
    void updatePlayerUI(QImage img);

private:
    Ui::ViewWidget *ui;
    VideoProcessing* vp;
};

#endif // VIEWWIDGET_H
