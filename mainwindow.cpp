#include "mainwindow.h"
#include <portaudio.h>
#include "pa_metronome.h"
#include "ui_mainwindow.h"
#include <QFile>

MainWindow :: MainWindow(Metronome *metronome, QWidget *parent) : metronome(metronome), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->playButton, SIGNAL(clicked(bool)),      this, SLOT(startClicked()));
    connect(this,           SIGNAL(resetBpm(int)), ui->bpmSB, SLOT(setValue(int)));
    connect(ui->Volume,     SIGNAL(valueChanged(int)),  this, SLOT(volumeChange(int)));
    connect(ui->bpmSB,      SIGNAL(valueChanged(int)),  this, SLOT(bpmChange(int)));
    connect(ui->BarSizeSB,  SIGNAL(valueChanged(int)),  this, SLOT(barSizeChange(int)));
    connect(ui->en_sp_trRB, SIGNAL(toggled(bool)),      this, SLOT(enableSpeedTraining()));
    connect(ui->fourRB,     SIGNAL(toggled(bool)),      this, SLOT(barDuration()));
    connect(ui->eightRB,    SIGNAL(toggled(bool)),      this, SLOT(barDuration()));
    connect(ui->sixteenRB,  SIGNAL(toggled(bool)),      this, SLOT(barDuration()));
    connect(ui->thirtyTwoRB,SIGNAL(toggled(bool)),      this, SLOT(barDuration()));
    connect(ui->add_bpmSB,  SIGNAL(valueChanged(int)),  this, SLOT(addBpmChange(int)));
    connect(ui->barsLimitSB,SIGNAL(valueChanged(int)),  this, SLOT(barLimitChange(int)));
    connect(metronome,      SIGNAL(barPlayed(int)),     this, SLOT(enableSpeedTraining()));
    connect(metronome,      SIGNAL(bpmChanged(int)),    this, SLOT(bpmPrint()));
    connect(metronome,      SIGNAL(barPlayed(int)),     this, SLOT(barPrint()));
    connect(metronome,      SIGNAL(beatChanged(int)),   this, SLOT(beatPrint()));




}





/*===================================================================================================*/

void MainWindow::bpmPrint()     { ui->bpmOut->setText(QString::number(metronome->getBpm())); }

void MainWindow::barPrint()     { ui->barOut->setText(QString::number(metronome->getBarIndex())); }

void MainWindow::beatPrint()    { ui->beatOut->setText(QString::number(metronome->getBeatIndex())); }




void MainWindow::startClicked()
{
    if(!metronome->isPlaying())
        metronome->start();
    else
    {
        emit resetBpm(metronome->getBpm());
        metronome->stop();

    }
}

void MainWindow::barDuration()
{
    if (ui->fourRB->isChecked())
        metronome->setBpm(metronome->getBpm() * 1);
    else
        if (ui->eightRB->isChecked())
            metronome->setBpm(metronome->getBpm() * 2);
        else
            if (ui->sixteenRB->isChecked())
                metronome->setBpm(metronome->getBpm() * 4);
            else
                if (ui->thirtyTwoRB->isChecked())
                    metronome->setBpm(metronome->getBpm() * 8);

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
    }
}


/*==================================================================================================*/

MainWindow::~MainWindow()
{
    delete ui;
}


