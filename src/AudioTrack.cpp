#include "AudioTrack.h"
#include <iostream>
#include <cstring>
#include <random>

AudioTrack::AudioTrack(const std::string& title, const std::vector<std::string>& artists, 
                      int duration, int bpm, size_t waveform_samples)
    : title(title), artists(artists), duration_seconds(duration), bpm(bpm), 
      waveform_size(waveform_samples) {

    // Allocate memory for waveform analysis
    waveform_data = new double[waveform_size];

    // Generate some dummy waveform data for testing
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1.0, 1.0);

    for (size_t i = 0; i < waveform_size; ++i) {
        waveform_data[i] = dis(gen);
    }
    #ifdef DEBUG
    std::cout << "AudioTrack created: " << title << " by " << std::endl;
    for (const auto& artist : artists) {
        std::cout << artist << " ";
    }
    std::cout << std::endl;
    #endif
}

// ========== TODO: STUDENTS IMPLEMENT RULE OF 5 ==========

AudioTrack::~AudioTrack() {
    // TODO: Implement the destructor
    #ifdef DEBUG
    std::cout << "AudioTrack destructor called for: " << title << std::endl;
    #endif
    // Your code here...

    checkIfAllocatedAndDelete();
}

void AudioTrack::checkIfAllocatedAndDelete()
{
    //if the array is initialized then free the memory it.
    if(waveform_data)
    {
        delete[] waveform_data;
        waveform_data = nullptr;
    }
}

AudioTrack::AudioTrack(const AudioTrack& other)
: title(other.title), artists(other.artists), bpm(other.bpm), 
  waveform_size(other.waveform_size), waveform_data(nullptr)
{
    // TODO: Implement the copy constructor
    #ifdef DEBUG
    std::cout << "AudioTrack copy constructor called for: " << other.title << std::endl;
    #endif
    // Your code here...

    waveform_data = new double[waveform_size];

    for(int i=0; i< waveform_size; i++)
    {
        waveform_data[i] = other.waveform_data[i];
    }

}

AudioTrack& AudioTrack::operator=(const AudioTrack& other)
 {
    // TODO: Implement the copy assignment operator
    #ifdef DEBUG
    std::cout << "AudioTrack copy assignment called for: " << other.title << std::endl;
    #endif
    // Your code here...
    
    if(this != &other)
    {
        title = other.title;    // std::string 's rule of 5 should handle that.
        artists = other.artists; // std::vector<T>'s rule of 5 should handle that.
    
        //simple types
        duration_seconds = other.duration_seconds;
        bpm = other.bpm;
        waveform_size = other.waveform_size;

        checkIfAllocatedAndDelete();
        waveform_data = new double[waveform_size];

        for(int i=0; i< waveform_size; i++)
        {
            waveform_data[i] = other.waveform_data[i];
        }
    }

    return *this;
}

AudioTrack::AudioTrack(AudioTrack&& other) noexcept 
: title(other.title), artists(other.artists), bpm(other.bpm), 
  waveform_size(other.waveform_size), waveform_data(other.waveform_data)
{
    // TODO: Implement the move constructor
    #ifdef DEBUG
    std::cout << "AudioTrack move constructor called for: " << other.title << std::endl;
    #endif
    // Your code here...

    other.waveform_data = nullptr;
    other.artists.clear();
}

AudioTrack& AudioTrack::operator=(AudioTrack&& other) noexcept {
    // TODO: Implement the move assignment operator

    #ifdef DEBUG
    std::cout << "AudioTrack move assignment called for: " << other.title << std::endl;
    #endif
    // Your code here...

    if(this != &other)
    {
        title = other.title;    // std::string 's rule of 5 should handle that.
        artists = other.artists; // std::vector<T>'s rule of 5 should handle that.
        other.artists.clear();
        //simple types
        duration_seconds = other.duration_seconds;
        bpm = other.bpm;
        waveform_size = other.waveform_size;
        //array pointer
        waveform_data = other.waveform_data;
        other.waveform_data = nullptr;
    }

    return *this;
}

void AudioTrack::get_waveform_copy(double* buffer, size_t buffer_size) const {
    if (buffer && waveform_data && buffer_size <= waveform_size) {
        std::memcpy(buffer, waveform_data, buffer_size * sizeof(double));
    }
}