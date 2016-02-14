#include "mainwindow.h"
#include <portaudio.h>
#include "metronome.h"
#include "ui_mainwindow.h"

MainWindow :: MainWindow(Metronome *metronome, QWidget *parent) : metronome(metronome), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->bpmSB->setValue(metronome->setBpm());

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(StartClicked()));
    connect(ui->bpmSB, SIGNAL(valueChanged(int)), this, SLOT(bpmChanged(int)));



}

void MainWindow::StartClicked()
{
    metronome->start();
}

void MainWindow::StopClicked()
{

    metronome->stop();
}

void MainWindow::CloseClicked()
{
    metronome->close();
    Pa_Terminate();
    this->close();

}

void MainWindow::bpmChanged(int bpm)
{
    metronome->setBpm(bpm);
}

MainWindow::~MainWindow()
{
    delete ui;
}
