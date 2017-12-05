#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "inputfile.h"
#include "rsvideoasset.h"
#include "demux.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->textCursor().insertText("/Users/guanweidong/reeelive/resource/2.mp4");
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(startPaseClick()));
    connect(ui->demuxButton,SIGNAL(clicked()),this,SLOT(demuxClick()));
}

void  MainWindow::startPaseClick()
{
    QString path =  ui->textEdit->toPlainText();
    InputFile inputfile(path.toStdString());
    this->videoPath = path;
    this->videoasset = new RSVideoAsset(this->videoPath.toStdString());
    ui->fpslable->setText(QString::number(videoasset->getFrameRate().num,10));
    ui->bitrateValue->setText(QString::number(videoasset->getBitRate(),10));
    ui->widthValue->setText(QString::number(videoasset->getVideoWidth(),10));
    ui->heightValue->setText(QString::number(videoasset->getVideoHeight(),10));
    ui->chanelCountValue->setText(QString::number(videoasset->getChannalCount(),10));
    ui->sampleValue->setText(QString::number(videoasset->getSampleRate(),10));
    ui->deepValue->setText(QString::number(videoasset->getAudioBitPreChannel(),10));
    ui->vDecodeName->setText(QString::fromStdString(videoasset->getVideoCodecName()));
    ui->aDecodeValue->setText(QString::fromStdString(videoasset->getAudioCodecName()));
}

void MainWindow::demuxClick()
{
    this->demux = new Demux(this->videoasset,true);
    this->demux->startDemux();
}

MainWindow::~MainWindow()
{
    delete ui;
}
