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
        double Duration;
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
    void setDuration(double value)      { this->beatDuration = value;  }


    void speedTr();
    void HandleError(PaError &err);

    int getBpm()        { return bpm; }
    int getOriginalBpm(){ return originalBpm; }
    int getBarLimit()   { return barLimit; }
    int getBarIndex()   { return barIndex; }
    int getBeatIndex()  { return beatIndex; }
    int getDuration()   { return beatDuration; }

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
    double beatDuration = 1;

    int b1  = 1000; double d1  = beatDuration;
    int b2  = 500;  double d2  = beatDuration;
    int b3  = 500;  double d3  = beatDuration;
    int b4  = 500;  double d4  = beatDuration;
    int b5  = 500;  double d5  = beatDuration;
    int b6  = 500;  double d6  = beatDuration;
    int b7  = 500;  double d7  = beatDuration;
    int b8  = 500;  double d8  = beatDuration;
    int b9  = 500;  double d9  = beatDuration;
    int b10 = 500;  double d10 = beatDuration;
    int b11 = 500;  double d11 = beatDuration;
    int b12 = 500;  double d12 = beatDuration;
    int b13 = 500;  double d13 = beatDuration;
    int b14 = 500;  double d14 = beatDuration;
    int b15 = 500;  double d15 = beatDuration;
    int b16 = 500;  double d16 = beatDuration;
    int b17 = 500;  double d17 = beatDuration;
    int b18 = 500;  double d18 = beatDuration;
    int b19 = 500;  double d19 = beatDuration;
    int b20 = 500;  double d20 = beatDuration;
    int b21 = 500;  double d21 = beatDuration;
    int b22 = 500;  double d22 = beatDuration;
    int b23 = 500;  double d23 = beatDuration;
    int b24 = 500;  double d24 = beatDuration;
    int b25 = 500;  double d25 = beatDuration;
    int b26 = 500;  double d26 = beatDuration;
    int b27 = 500;  double d27 = beatDuration;
    int b28 = 500;  double d28 = beatDuration;
    int b29 = 500;  double d29 = beatDuration;
    int b30 = 500;  double d30 = beatDuration;
    int b31 = 500;  double d31 = beatDuration;
    int b32 = 500;  double d32 = beatDuration;




signals:
    void barPlayed(int);
    void bpmChanged(int);
    void beatChanged(int);
};

#endif // METRONOME_H
