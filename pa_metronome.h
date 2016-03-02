#ifndef _METRONOME_H_
#define _METRONOME_H_

#include <QObject>
#include <portaudio.h>
#include <vector>

class Metronome : public QObject
{
    Q_OBJECT

public:
    Metronome(QObject *parent=0);

    struct Beat
    {
        int frequencyTick;
    };

    void setBar(std::vector<Beat> bar);
    void setBpm(int);
    void setVolume(int);
    void setAddBpm(int);
    void setBarLimit(int);
    void setBarIndex(int);
    void setBeatIndex(int);
    void setBarSize(int);

    void speedTr();
    void HandleError(PaError &err);

    int getBpm();
    int getBarLimit();
    int getBarIndex();
    int getBeatIndex();

    bool open(PaDeviceIndex);
    bool pa_init();
    bool start();
    bool close();
    bool stop();
    bool isPlaying();

    ~Metronome(void);

private:
    static int paCallback(const void*   inputBuffer,
        void*                           outputBuffer,
        unsigned long                   framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags           statusFlags,
        void*                           userData);

    std::vector<Beat> bar;
    PaStream *stream;

    int addBpm      = 0;
    int barIndex    = 0;
    int barLimit    = 0;
    int bpm         = 120;
    float volume    = 0.75;
    int counter     = 0;
    int beatIndex   = 0;
    bool playing    = false;
    int barSize     = 4;

    int b1 = 1000;
    int b2 = 500;
    int b3 = 500;
    int b4 = 500;
    int b5 = 500;
    int b6 = 500;
    int b7 = 500;
    int b8 = 500;

signals:
    void barPlayed(int);
    void bpmChanged(int);
    void beatChanged(int);
};

#endif // METRONOME_H
