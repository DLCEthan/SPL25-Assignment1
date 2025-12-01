#include "DJLibraryService.h"
#include "SessionFileParser.h"
#include "MP3Track.h"
#include "WAVTrack.h"
#include <iostream>
#include <memory>
#include <filesystem>


DJLibraryService::DJLibraryService(const Playlist& playlist) 
    : playlist(playlist), library() {}
<<<<<<< HEAD

DJLibraryService::~DJLibraryService()
{
    for(size_t i = 0; i < library.size(); i++)
    {
        delete library[i];
        library[i] = nullptr;
    }
}

=======
>>>>>>> upstream/main
/**
 * @brief Load a playlist from track indices referencing the library
 * @param library_tracks Vector of track info from config
 */
void DJLibraryService::buildLibrary(const std::vector<SessionConfig::TrackInfo>& library_tracks) {
    //Todo: Implement buildLibrary method
    std::cout << "TODO: Implement DJLibraryService::buildLibrary method\n"<< library_tracks.size() << " tracks to be loaded into library.\n";
    
    for(size_t i = 0; i < library_tracks.size(); i++)
    {
        AudioTrack* newTrack = nullptr;
        if(library_tracks[i].type == "MP3")
        {
            newTrack = new MP3Track(library_tracks[i].title, library_tracks[i].artists, library_tracks[i].duration_seconds, 
                                library_tracks[i].bpm, library_tracks[i].extra_param1, library_tracks[i].extra_param2);
            std::cout << "MP3Track created: "<< library_tracks[i].extra_param1 << " kbps" << std::endl;
        }
        else
        {
            newTrack = new WAVTrack(library_tracks[i].title, library_tracks[i].artists, library_tracks[i].duration_seconds, 
                                library_tracks[i].bpm, library_tracks[i].extra_param1, library_tracks[i].extra_param2);
            std::cout << "WAVTrack created: "<< library_tracks[i].extra_param1 << "Hz/" << library_tracks[i].extra_param2 << "bit" << std::endl;
        }

        library.push_back(newTrack);
    }

    std::cout << "[INFO] Track library built: "<<library_tracks.size() << "tracks loaded" << std::endl;
}

/**
 * @brief Display the current state of the DJ library playlist
 * 
 */
void DJLibraryService::displayLibrary() const {
    std::cout << "=== DJ Library Playlist: " 
              << playlist.get_name() << " ===" << std::endl;

    if (playlist.is_empty()) {
        std::cout << "[INFO] Playlist is empty.\n";
        return;
    }

    // Let Playlist handle printing all track info
    playlist.display();

    std::cout << "Total duration: " << playlist.get_total_duration() << " seconds" << std::endl;
}

/**
 * @brief Get a reference to the current playlist
 * 
 * @return Playlist& 
 */
Playlist& DJLibraryService::getPlaylist() {
    // Your implementation here
    return playlist;
}

/**
 * TODO: Implement findTrack method
 * 
 * HINT: Leverage Playlist's find_track method
 */
AudioTrack* DJLibraryService::findTrack(const std::string& track_title) {
    // Your implementation here
    return playlist.find_track(track_title);
}

void DJLibraryService::loadPlaylistFromIndices(const std::string& playlist_name, 
                                               const std::vector<int>& track_indices) {
    // Your implementation here
    std::cout << "[INFO] Loading playlist: " << playlist_name << std::endl;
    //remove existing track to make sure no memory leaks
    std::vector<std::string> titles = getTrackTitles();
    int count = 0;
    for( std::string title : titles)
    {
        playlist.remove_track(title);
    }

    playlist = Playlist(playlist_name);
    for(int index : track_indices)
    {
        if(index <= 0 || index > library.size())
        {
            std::cout << " [WARNING] Invalid track index: " << index << std::endl;
            continue;
        }

        AudioTrack* track = (library[index - 1]->clone()).release();
        if(!track)
        {
            std::cout << "[ERROR] failed to clone track " << library[index - 1]->get_title() << std::endl;
            continue;
        }

        track->load();
        track->analyze_beatgrid();

        playlist.add_track(track);
        count++;
        std::cout << "Added "<< track->get_title() << " to playlist " <<playlist_name << std::endl;
    }

    std::cout << "[INFO] Playlist loaded: "<< playlist_name << "(" << count << " tracks)" << std::endl;

}
/**
 * TODO: Implement getTrackTitles method
 * @return Vector of track titles in the playlist
 */
std::vector<std::string> DJLibraryService::getTrackTitles() const {
    // Your implementation here
    std::vector<AudioTrack*> tracks = playlist.getTracks();
    std::vector<std::string> titles(tracks.size());

    for(size_t i = 0; i < tracks.size(); i++)
    {
        titles[i] = tracks[i]->get_title();
    }

    return titles; // Placeholder
}
