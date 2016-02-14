#include "mainwindow.h"
#include <portaudio.h>
#include "metronome.h"
#include "ui_mainwindow.h"

MainWindow :: MainWindow(Metronome *metronome, QWidget *parent) : metronome(metronome), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(StartClicked()));
    connect(ui->bpmSB, SIGNAL(valueChanged(int)), this, SLOT(bpmChanged(int)));



}

void MainWindow::StartClicked()
{
    if(!metronome->isPlaying())
        metronome->start();
    else
        metronome->stop();
}

void MainWindow::StopClicked()
{
    if(metronome->isPlaying())
        metronome->stop();
}


void MainWindow::bpmChanged(int bpm)
{
    metronome->setBpm(bpm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
