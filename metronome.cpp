#include "metronome.h"
#include <iostream>
#include <portaudio.h>
#include <math.h>
#include <vector>

#define SAMPLE_RATE (44100)

Metronome::Metronome()
{
    pa_init();
    open(Pa_GetDefaultOutputDevice());
    std::vector<Beat> bar = { { 1000 },{ 500 },{ 500 },{ 500 } };
    setBar(bar);
}

void Metronome::setBar(std::vector<Beat> bar)
{
    this->bar = bar;
}


void Metronome::speedTr()
{
    if(barCount > barLimit)
        bpm = bpm +addBpm;
}

bool Metronome::isPlaying()
{
    return playing;
}

void Metronome::setBpm(int b)
{
    bpm = b;
}

int Metronome::getBpm()
{
    return bpm;
}

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



int Metronome::paCallback	(const		void*						inputBuffer,
                                        void*                       outputBuffer,
                            unsigned	long						framesPerBuffer,
                            const		PaStreamCallbackTimeInfo*	timeInfo,
                                        PaStreamCallbackFlags       statusFlags,
                                        void*                       userData)

{
        Metronome *metronome = (Metronome*)userData;
        float sampleVal;
        const float pi = 3.14159265358;
        float *out = (float*)outputBuffer;
        float framesInMs = SAMPLE_RATE / 1000.0;			//количество кадров в одной мс. = 44.1
        float msCount = metronome->counter / framesInMs;	//счетчик мс
        double tick = framesInMs * 100;                     //длительность одного удара в кадрах
        double delayMs = (1000 * 60) / metronome->bpm;      //интервал в мс
        double interval = (framesInMs * delayMs);           //интервал между ударами в кадрах.

        for (unsigned int i = 0; i < framesPerBuffer; i++)
        {
            if (metronome->counter < tick)
            {
                int freq = metronome->bar[metronome->beatIndex].frequencyTick;
                sampleVal = sinf(2.0 * pi * freq * metronome->counter / SAMPLE_RATE);

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
                    metronome->beatIndex = (metronome->beatIndex + 1) % metronome->bar.size();
                    if(metronome->beatIndex == 0)
                    {
                        metronome->barCount = metronome->barCount + 1;

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
