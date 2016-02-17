#include "mainwindow.h"
#include <portaudio.h>
#include "pa_metronome.h"
#include "ui_mainwindow.h"

MainWindow :: MainWindow(Metronome *metronome, QWidget *parent) : metronome(metronome), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked(bool)), this, SLOT(startClicked()));
    connect(ui->bpmSB, SIGNAL(valueChanged(int)), this, SLOT(bpmChange(int)));
    connect(ui->en_sp_trRB, SIGNAL(toggled(bool)), this, SLOT(enableSpeedTraining()));
    connect(ui->add_bpmSB, SIGNAL(valueChanged(int)), this, SLOT(addBpmChange(int)));
    connect(ui->bars_per_stepSB, SIGNAL(valueChanged(int)), this, SLOT(barLimitChange(int)));
    connect(metronome, SIGNAL(barIsPlayed(int)), this, SLOT(enableSpeedTraining()));
    connect(metronome, SIGNAL(bpmIsChanged(int)), this, SLOT(bpmOut()));
    connect(metronome, SIGNAL(barIsPlayed(int)), this, SLOT(barOut()));
    connect(metronome, SIGNAL(beatIsChanged(int)), this, SLOT(beatOut()));


}

/*===================================================================================================*/

void MainWindow::bpmOut()
{
    ui->bpmOut->setText(QString::number(metronome->getBpm()));
}

void MainWindow::barOut()
{
    ui->barOut->setText(QString::number(metronome->getBarCount()));
}

void MainWindow::beatOut()
{
    ui->beatOut->setText(QString::number(metronome->getBeatCount()));
}


void MainWindow::startClicked()
{
    if(!metronome->isPlaying())
        metronome->start();
    else
        metronome->stop();
}


void MainWindow::bpmChange(int bpm)
{
    metronome->setBpm(bpm);
}


void MainWindow::addBpmChange(int add_bpm)
{
    metronome->addBpm = add_bpm;
}


void MainWindow::barLimitChange(int bar_lim)
{
    metronome->setBarLimit(bar_lim);
}

void MainWindow::enableSpeedTraining()
{
    if(ui->en_sp_trRB->isChecked())
    {

        metronome->speedTr();

    }
    else
    {
        metronome->setBpm(ui->bpmSB->value());
        ui->bars_per_stepSB->setValue(0);
        ui->add_bpmSB->setValue(0);
    }
}


/*==================================================================================================*/

MainWindow::~MainWindow()
{
    delete ui;
}
