#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pa_metronome.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     MainWindow(Metronome *metronome, QWidget *parent=0);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Metronome   *metronome;

private slots:
    void bpmPrint();
    void barPrint();
    void beatPrint();
    void bpmChange(int bpm)         { metronome->setBpm(bpm); }
    void addBpmChange(int add_bpm)  { metronome->setAddBpm(add_bpm); }
    void barLimitChange(int bar_lim){ metronome->setBarLimit(bar_lim); }
    void volumeChange(int vol)      { metronome->setVolume(vol);}
    void barSizeChange(int value)   { metronome->setBarSize(value); }

    void barDuration();

    void startClicked();
    void enableSpeedTraining();

signals:
    void resetBpm(int);
    void resetBar(int);
    void resetBeat(int);


};

#endif // MAINWINDOW_H
