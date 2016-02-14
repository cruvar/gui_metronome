#include "mainwindow.h"
#include <portaudio.h>
#include "metronome.h"
#include "ui_mainwindow.h"

MainWindow :: MainWindow(Metronome *metronome, QWidget *parent) : metronome(metronome), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(StartClicked()));
    //connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(StopClicked()));
    connect(ui->bpmSB, SIGNAL(valueChanged(int)), this, SLOT(bpmChanged(int)));



}

void MainWindow::StartClicked()
{
    if (!metronome->isPlaying())
    {
        metronome->start();
        metronome->setPlaying(true);
    }
    else
    {
        metronome->stop();
        metronome->setPlaying(false);

    }

}

void MainWindow::StopClicked()
{
    if(metronome->isPlaying())
    {
        metronome->stop();
        metronome->setPlaying(false);

    }
}


void MainWindow::bpmChanged(int bpm)
{
    metronome->setBpm(bpm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
