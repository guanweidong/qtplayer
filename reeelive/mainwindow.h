#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString.h>
#include "rsvideoasset.h"
#include "demux.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QString videoPath;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow  *   ui;
    RSVideoAsset    *   videoasset;
    Demux           *   demux;
private slots:
    void startPaseClick();
    void demuxClick();
};

#endif // MAINWINDOW_H
