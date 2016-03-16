#include <QObject>
#include "pa_metronome.h"
#include <iostream>
#include <portaudio.h>
#include <math.h>
#include <vector>

#define SAMPLE_RATE (44100)

Metronome::Metronome(QObject *parent) : QObject(parent)
{
    pa_init();
    open(Pa_GetDefaultOutputDevice());
    std::vector<Beat> bar = { { b1, d1 },   { b2, d2 },   { b3, d3 },   { b4, d4 },
                              { b5, d5 },   { b6, d6 },   { b7, d7 },   { b8, d8 },
                              { b9, d9 },   { b10, d10 }, { b11, d11 }, { b12, d12 },
                              { b13, d13 }, { b14, d14 }, { b15, d15 }, { b16, d16 },
                              { b17, d17 }, { b18, d28 }, { b19, d19 }, { b20, d20 },
                              { b21, d21 }, { b22, d22 }, { b23, d23 }, { b24, d24 },
                              { b25, d25 }, { b26, d26 }, { b27, d27 }, { b28, d28 },
                              { b29, d29 }, { b30, d30 }, { b31, d31 }, { b32, d32 } };
    setBar(bar);
}

/*=================================================================================*/

void Metronome::speedTr()
{
     if(barIndex > barLimit)
     {
         barIndex = 1;
         bpm = bpm +addBpm;
     }
}

/*===============================================================================*/

bool Metronome::open(PaDeviceIndex index)
{
    PaError err;
    PaStreamParameters outputParameters;
    Metronome *metronome;
    outputParameters.device = index;
    if (outputParameters.device == paNoDevice)
    {
        return false;
    }

    outputParameters.channelCount = 2;
    outputParameters.sampleFormat = paFloat32;
    outputParameters.suggestedLatency = Pa_GetDeviceInfo(outputParameters.device)->defaultHighOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&stream,
        NULL,              /* No input. */
        &outputParameters, /* As above. */
        SAMPLE_RATE,
        256,               /* Frames per buffer. */
        paClipOff,         /* No out of range samples expected. */
        paCallback,
        this);

    return true;
}


bool Metronome::start()
{
    if (stream == 0)
        return false;

    beatIndex = 0;
    barIndex = 0;
    counter = 0;
    playing = true;
    PaError err = Pa_StartStream(stream);
    return (err == paNoError);
}

bool Metronome::pa_init()
{
    PaError err = Pa_Initialize();
    if (err != paNoError) Pa_Terminate();
    return err;
}

bool Metronome::close()
{
    if (stream == 0)
        return false;
    PaError err = Pa_CloseStream(stream);
    stream = 0;
    return (err == paNoError);
}

bool Metronome::stop()
{
    if (stream == 0)
        return false;
    playing = false;
    PaError err = Pa_StopStream(stream);
    return (err == paNoError);
}


void Metronome::HandleError(PaError &err)
{
    Pa_Terminate();
    std::cout << "Произошла ошибка во время использования потока Portaudio" << std::endl;
    std::cout << "Номер ошибки: " << err << std::endl;
    std::cout << "Сообщение об ошибке: " << Pa_GetErrorText(err) << std::endl;
    exit(err);
}

int Metronome::paCallback(const void * inputBuffer,
                          void * outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void * userData)

{
        Metronome *metronome = (Metronome*)userData;
        float sampleVal;
        const float pi = 3.14159265358;
        float *out = (float*)outputBuffer;
        float framesInMs = SAMPLE_RATE / 1000.0;			//количество кадров в одной мс. = 44.1
        double tick = framesInMs * 100;                     //длительность одного удара в кадрах
        double delayMs = (( 1000 * 60) / metronome->bpm )
                          / metronome->bar[metronome->beatIndex].Duration;      //интервал в мс
        double interval = (framesInMs * delayMs);           //интервал между ударами в кадрах.

        double dur = metronome->beatDuration;

        for (unsigned int i = 0; i < framesPerBuffer; i++)
        {
            if (metronome->counter < tick)
            {
                int freq = metronome->bar[metronome->beatIndex].frequencyTick;
                sampleVal = sinf(2.0 * pi * freq * metronome->counter / SAMPLE_RATE);
                sampleVal = sampleVal * metronome->volume;

                *out++ = sampleVal;
                *out++ = sampleVal;
                metronome->counter++;
            }
            else
                if (metronome->counter < interval)
                {
                    *out++ = 0;
                    *out++ = 0;
                    metronome->counter++;
                }
                else
                {

                    metronome->counter = 0;

                    metronome->beatIndex = (metronome->beatIndex + 1) % metronome->barSize;
                    emit metronome->beatChanged(metronome->beatIndex);


                    if(metronome->beatIndex == 1)
                    {
                        metronome->barIndex = metronome->barIndex + 1;
                        emit metronome->barPlayed(metronome->barIndex);
                        emit metronome->bpmChanged(metronome->bpm);
                    }

                }
        }

        return 0;
    }

Metronome::~Metronome(void)
{
    close();
    Pa_Terminate();
}
