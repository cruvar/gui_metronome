#include "mainwindow.h"
#include <portaudio.h>
#include "pa_metronome.h"
#include "ui_mainwindow.h"



MainWindow :: MainWindow(Metronome *metronome, QWidget *parent) : metronome(metronome), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->playButton->setShortcut( QKeySequence(Qt::Key_Space) );

    connect(ui->playButton, SIGNAL(clicked(bool)),      this, SLOT(startClicked()));
    connect(this,           SIGNAL(resetBpm(int)), ui->bpmSB, SLOT(setValue(int)));
    connect(ui->Volume,     SIGNAL(valueChanged(int)),  this, SLOT(volumeChange(int)));
    connect(ui->bpmSB,      SIGNAL(valueChanged(int)),  this, SLOT(bpmChange(int)));
    connect(ui->BarSizeSB,  SIGNAL(valueChanged(int)),  this, SLOT(barSizeChange(int)));
    connect(ui->en_sp_trRB, SIGNAL(toggled(bool)),      this, SLOT(enableSpeedTraining()));
    connect(ui->fourRB,     SIGNAL(toggled(bool)),      this, SLOT(barDuration4()));
    connect(ui->eightRB,    SIGNAL(toggled(bool)),      this, SLOT(barDuration8()));
    connect(ui->sixteenRB,  SIGNAL(toggled(bool)),      this, SLOT(barDuration16()));
    connect(ui->thirtyTwoRB,SIGNAL(toggled(bool)),      this, SLOT(barDuration32()));
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
    {
        ui->playButton->setText("Stop");
        metronome->setOriginalBpm(ui->bpmSB->value());
        metronome->setBpm(metronome->getOriginalBpm());
        metronome->start();
    }
    else
    {
        ui->playButton->setText("Start");
        ui->playButton->setShortcut( QKeySequence(Qt::Key_Space) );
        emit resetBpm(metronome->getOriginalBpm());
        metronome->stop();

    }
}

void MainWindow::barDuration4()
{
    metronome->setBpm(metronome->getOriginalBpm() * 1);
}

void MainWindow::barDuration8()
{
    metronome->setBpm(metronome->getOriginalBpm() * 2);
}

void MainWindow::barDuration16()
{
    metronome->setBpm(metronome->getOriginalBpm() * 4);
}

void MainWindow::barDuration32()
{
    metronome->setBpm(metronome->getOriginalBpm() * 8);
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


