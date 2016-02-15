#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <portaudio.h>
#include "metronome.h"

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
    void StartClicked();
    void bpmChanged(int);
    void addBpmChanged(int);
    void barLimitChanged(int);
    void enableSpeedTraining();

signals:




};

#endif // MAINWINDOW_H
