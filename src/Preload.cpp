/* Preload.cpp
 * This file preloads assets: all the fonts and sprites are loaded here before
 * the game starts.
 * */

void loadAssets() {

    UI_FONT_HEAD.loadFromFile(UI_FONT_HEAD_LOCATION);
    UI_FONT_BODY.loadFromFile(UI_FONT_BODY_LOCATION);

    if (!uiSpriteTexture.loadFromFile(UI_SPRITE_PATH))
        std::cout << "Failed to load from file: " << UI_SPRITE_PATH << std::endl;

    if (!menuBgTexture.loadFromFile(BACKGROUND_MENU_PATH))
        std::cout << "Failed to load from file: " << BACKGROUND_MENU_PATH << std::endl;

    if (!keysSpriteTexture.loadFromFile(KEYS_SPRITE_PATH))
        std::cout << "Failed to load from file: " << KEYS_SPRITE_PATH << std::endl;

    if (!rockTexture.loadFromFile(ROCK_TEXTURE_PATH)) {
        std::cout << "Failed to load Rock." << std::endl;
    }

    if (!redRockTexture.loadFromFile(ROCK_RED_TEXTURE_PATH)) {
        std::cout << "Failed to load Rock." << std::endl;
    }

    if (!puzzleCipherTexture.loadFromFile(PUZZLE_CIPHER_PATH)) {
        std::cout << "Failed to load from file: " << PUZZLE_CIPHER_PATH << std::endl;
    }

    if (!platformerPlatformTexture.loadFromFile(PLATFORMER_PLATFORM_PATH)) {
        std::cout << "Failed to load from file: " << PLATFORMER_PLATFORM_PATH << std::endl;
    }

    if (!platformerObstacleTexture.loadFromFile(PLATFORMER_OBSTACLE_PATH)) {
        std::cout << "Failed to load from file: " << PLATFORMER_OBSTACLE_PATH << std::endl;
    }

    initGuideCharSprite();
    initRockCharSprite();
    initCipherCharSprite();
    initHorseCharSprite();
    initPlatformerCharSprite();
    initEmptyCharSprite();
    initPlayerCharSprite();
    initPuzzleCipherSprite();
    initStonePillarSprite();
}