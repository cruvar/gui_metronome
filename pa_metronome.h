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

    void setBar(std::vector<Beat> bar)  { this->bar = bar; }
    void setBpm(int bpm)                { this->bpm = bpm; }
    void setOriginalBpm(int value)      { this->originalBpm = value; }
    void setVolume(int volume)          { this->volume = (float)volume / 100; }
    void setAddBpm(int addBpm)          { this->addBpm = addBpm; }
    void setBarLimit(int barLimit)      { this->barLimit = barLimit; }
    void setBarIndex(int barIndex)      { this->barIndex = barIndex; }
    void setBeatIndex(int beatIndex)    { this->beatIndex = beatIndex; }
    void setBarSize(int barSize)        { this->barSize = barSize; }
    void setDuration(double value)      { this->duration = value; }

    void speedTr();
    void forceBeat()    { bar[0] = {1046}; }
    void normalBeat()   { bar[0] = {523}; };
    void HandleError(PaError &err);

    int getBpm()        { return bpm; }
    int getOriginalBpm(){ return originalBpm; }
    int getBarLimit()   { return barLimit; }
    int getBarIndex()   { return barIndex; }
    int getBeatIndex()  { return beatIndex; }
    int getDuration()   { return duration; }

    bool open(PaDeviceIndex);
    bool pa_init();
    bool start();
    bool close();
    bool stop();
    bool isPlaying() { return playing; }

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
    int originalBpm = 120;
    float volume    = 0.75;
    int counter     = 0;
    int beatIndex   = 0;
    bool playing    = false;
    int barSize     = 4;
    double duration = 1;

signals:
    void barPlayed(int);
    void bpmChanged(int);
    void beatChanged(int);
};

#endif // METRONOME_H
