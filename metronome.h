#include <portaudio.h>
#include <vector>

#ifndef _METRONOME_H_
#define _METRONOME_H_

class Metronome
{
public:
    Metronome();

    struct Beat
    {
        int frequencyTick;
    };


    void setBar(std::vector<Beat> bar);
    void setBpm(int);
    bool open(PaDeviceIndex);
    bool pa_init();
    bool start();
    bool close();
    bool stop();
    bool isPlaying();
    void setPlaying(bool);
    void speedTr();
    void HandleError(PaError &err);
    ~Metronome(void);



private:
        static int paCallback(const void*  inputBuffer,
        void*                           outputBuffer,
        unsigned long                   framesPerBuffer,
        const PaStreamCallbackTimeInfo* timeInfo,
        PaStreamCallbackFlags           statusFlags,
        void*                           userData);

    std::vector<Beat> bar;
    int barCount = 1;
    int barLimit;
    int bpm = 120;
    int addBpm;

    bool playing = false;
    unsigned int counter = 0;
    int beatIndex = 0;



    PaStream *stream;
};

#endif // METRONOME_H
