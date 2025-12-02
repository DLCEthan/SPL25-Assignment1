#include "MixingEngineService.h"
#include <iostream>
#include <memory>


/**
 * TODO: Implement MixingEngineService constructor
 */
MixingEngineService::MixingEngineService()
    : decks(), active_deck(1), auto_sync(false), bpm_tolerance(0)
{
    // Your implementation here
    decks[0] = nullptr;
    decks[1] = nullptr;

    std::cout << "[MixingEngineService] Initialized with 2 empty decks." << std::endl;
}

/**
 * TODO: Implement MixingEngineService destructor
 */
MixingEngineService::~MixingEngineService() {
    // Your implementation here

    std::cout << "MixingEngineService] Cleaning up decks...." << std::endl;

    for(size_t i = 0; i < 2; i++)
    {
        if(decks[i])
        {
            delete decks[i];
            decks[i] = nullptr;
        }
    }
}


/**
 * TODO: Implement loadTrackToDeck method
 * @param track: Reference to the track to be loaded
 * @return: Index of the deck where track was loaded, or -1 on failure
 */
int MixingEngineService::loadTrackToDeck(const AudioTrack& track) {
    // Your implementation here
    std::cout << "\n=== Loading Track to Deck ===" << std::endl;
    PointerWrapper<AudioTrack> clonedTrack = track.clone();
    
    if(!clonedTrack)
    {
        std::cout << "[ERROR] Track: " << track.get_title() << " failed to clone" << std::endl;

        return -1;
    }
    
    clonedTrack->load();
    clonedTrack->analyze_beatgrid();
    
    if(!decks[0] && !decks[1])
    {
        decks[0] = clonedTrack.release();
        std::cout << "[Load Complete] " << decks[0]->get_title() << " is now loaded on deck 0" << std::endl;
        active_deck = 0;
        displayDeckStatus();
        return 0; // returning the deck the track was loaded to
    }

    size_t target_index = 1 - active_deck;

    std::cout << "[Deck Switch] Target deck: " << target_index << std::endl;

    if(!decks[target_index])
    {
        delete decks[target_index];
        decks[target_index] = nullptr;
    }

    if(auto_sync && !can_mix_tracks(clonedTrack))
    {
        sync_bpm(clonedTrack);
    }

    AudioTrack* cloned = clonedTrack.release();
    decks[target_index] = cloned;
    std::cout << "[Load Complete] " << cloned->get_title() << " is now loaded on deck " << target_index << std::endl;

    std::cout << "[Unload] Unloading previous deck " << active_deck << " (" << decks[active_deck]->get_title() << ")" << std::endl;
    
    delete decks[active_deck];
    decks[active_deck] = nullptr;

    active_deck = target_index;
    std::cout << "[Active Deck] Switched to deck " << target_index << std::endl;
    displayDeckStatus();
    return active_deck; // Placeholder
}

/**
 * @brief Display current deck status
 */
void MixingEngineService::displayDeckStatus() const {
    std::cout << "\n=== Deck Status ===\n";
    for (size_t i = 0; i < 2; ++i) {
        if (decks[i])
            std::cout << "Deck " << i << ": " << decks[i]->get_title() << "\n";
        else
            std::cout << "Deck " << i << ": [EMPTY]\n";
    }
    std::cout << "Active Deck: " << active_deck << "\n";
    std::cout << "===================\n";
}

/**
 * TODO: Implement can_mix_tracks method
 * 
 * Check if two tracks can be mixed based on BPM difference.
 * 
 * @param track: Track to check for mixing compatibility
 * @return: true if BPM difference <= tolerance, false otherwise
 */
bool MixingEngineService::can_mix_tracks(const PointerWrapper<AudioTrack>& track) const {
    // Your implementation here
    if(!decks[active_deck] || !track)
    {
        return false;
    }
    
    int bpm1 = decks[active_deck]->get_bpm();
    int bpm2 = track->get_bpm();

    return std::abs(bpm1 - bpm2) <= bpm_tolerance ; 
}

/**
 * TODO: Implement sync_bpm method
 * @param track: Track to synchronize with active deck
 */
void MixingEngineService::sync_bpm(const PointerWrapper<AudioTrack>& track) const {
    int bpm1 = decks[active_deck]->get_bpm();
    int bpm2 = track->get_bpm();
    int new_bpm = (bpm1 + bpm2) / 2;

    std::cout << "[Sync BPM] Syncing BPM from  " << track->get_bpm() << " to " << new_bpm << std::endl;
    track->set_bpm(new_bpm);
    
    // Your implementation here
}
