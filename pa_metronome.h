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

    int addBpm = 0;

    void setBar(std::vector<Beat> bar);
    void setBpm(int);
    void setBarLimit(int);
    void setBarCount(int);
    void setBeatCount(int);
    void speedTr();
    void HandleError(PaError &err);

    int getBpm();
    int getBarLimit();
    int getBarCount();
    int getBeatCount();

    bool open(PaDeviceIndex);
    bool pa_init();
    bool start();
    bool close();
    bool stop();
    bool isPlaying();

    ~Metronome(void);



private:
        static int paCallback(const void*  inputBuffer,
        void*                           outputBuffer,
        unsigned long                   framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags           statusFlags,
        void*                           userData);

    std::vector<Beat> bar;
    int barCount = 0;
    int barLimit = 0;
    int bpm = 120;
    bool playing = false;
    unsigned int counter = 0;
    int beatCount = 0;

    PaStream *stream;

signals:
    void barIsPlayed(int);
    void bpmIsChanged(int);
    void beatIsChanged(int);
};

#endif // METRONOME_H
