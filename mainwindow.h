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
    void startClicked();
    void bpmChange(int);
    void addBpmChange(int);
    void barLimitChange(int);
    void enableSpeedTraining();
    void volumeChange(int);


signals:
    void resetBpm(int);
    void resetBar(int);
    void resetBeat(int);


};

#endif // MAINWINDOW_H
