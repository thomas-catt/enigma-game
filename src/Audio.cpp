sf::Music currentMusic;

void initMusic(const std::string& path) {
    if (!currentMusic.openFromFile(path)) {
        std::cout << "Error: Could not load music from file: " << path << std::endl;
    }
}


void playMusic(const std::string& path) {
    std::cout << "Switching music to: " << path << std::endl;

    currentMusic.stop();

    // Initialize and play the new music
    initMusic(path);
    currentMusic.setLoop(true);
    currentMusic.setVolume(MUSIC_MAX_VOL);
    currentMusic.play();
}
