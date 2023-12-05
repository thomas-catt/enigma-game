/* ../../Assets.h *
 * Sprites, fonts, sounds and all about the ../../assets and resources. All the asset
 * related constant values stuff of the entire project are in this file.
 *
 * */

/* Player constants */

#define PLAYER_SPRITE_PATH "assets/sprites/player-sprite.png"
#define PLAYER_SPRITE_WIDTH 64
#define PLAYER_SPRITE_HEIGHT 64

#define PLAYER_ANIM_FRAMES 8

#define PLAYER_ANIM_SPEED 100

enum PLAYER_SPRITE_DIR
{
    PLAYER_SPRITE_UP,
    PLAYER_SPRITE_LEFT,
    PLAYER_SPRITE_DOWN,
    PLAYER_SPRITE_RIGHT
};

/* Rock texture */

#define ROCK_TEXTURE_PATH "assets/sprites/DawayneJohnsun.png"

/* Guide character constants */

sf::Texture guideCharTexture;
NPC guideChar;
void initGuideCharSprite()
{
    guideChar.path = "assets/sprites/character_guide.png";
    guideChar.name = "Guide";
    guideChar.width = 32;
    guideChar.height = 32;

    guideChar.animFrames = 4;
    guideChar.animSpeed = 500;

    if (!guideChar.texture.loadFromFile(guideChar.path))
        std::cout << "Failed to load from file: " << guideChar.path << std::endl;
}


/* Rock game character constants */

NPC rockChar;
void initRockCharSprite()
{
    rockChar.path = "assets/sprites/golem.png";
    rockChar.name = "Rock Guy";
    rockChar.width = 80;
    rockChar.height = 108;

    rockChar.animFrames = 9;
    rockChar.animSpeed = 83; // 12 FPS

    if (!rockChar.texture.loadFromFile(rockChar.path))
        std::cout << "Failed to load from file: " << rockChar.path << std::endl;
}

/* Cipher game character constants */

NPC cipherChar;
void initCipherCharSprite()
{
    cipherChar.path = "assets/sprites/character_cipher.png";
    cipherChar.name = "Cipher Guy";
    cipherChar.width = 68;
    cipherChar.height = 96;

    cipherChar.animFrames = 9;
    cipherChar.animSpeed = 83; // 12 FPS

    if (!cipherChar.texture.loadFromFile(cipherChar.path))
        std::cout << "Failed to load from file: " << cipherChar.path << std::endl;
}

/* Platformer horse running game character constants */

NPC horseChar;
void initHorseCharSprite()
{
    horseChar.path = "assets/sprites/character_platformer_new.png";
    horseChar.name = "Horse";
    horseChar.width = 120;
    horseChar.height = 80;

    horseChar.animFrames = 4;
    horseChar.animSpeed = 100; // 10 FPS

    if (!horseChar.texture.loadFromFile(horseChar.path))
        std::cout << "Failed to load from file: " << horseChar.path << std::endl;
}
/* Platformer idle horse character constants */

NPC platformerChar;
void initPlatformerCharSprite()
{
    platformerChar.path = "assets/sprites/demon-idle.png";
    platformerChar.name = "Horse";
    platformerChar.width = 160;
    platformerChar.height = 144;

    platformerChar.animFrames = 6;
    platformerChar.animSpeed = 83; // 12 FPS

    if (!platformerChar.texture.loadFromFile(platformerChar.path))
        std::cout << "Failed to load from file: " << platformerChar.path << std::endl;
}

/* This NPC would basically act as the narrator or the speaker, won't have
 * any image, and so.
 *
 * */

NPC emptyChar;
void initEmptyCharSprite()
{
    emptyChar.path = "assets/sprites/character_rock.png";
    emptyChar.name = "Message";
    emptyChar.width = 1;
    emptyChar.height = 1;

    emptyChar.animFrames = 2;
    emptyChar.animSpeed = 1000;

    if (!emptyChar.texture.loadFromFile(emptyChar.path))
        std::cout << "Failed to load from file: " << emptyChar.path << std::endl;
}



/* The player himself. (Yes we are declaring him as an NPC) */

NPC playerChar;
void initPlayerCharSprite()
{
    playerChar.path = "assets/sprites/player-sprite.png";
    playerChar.name = "You";
    playerChar.width = PLAYER_SPRITE_WIDTH;
    playerChar.height = PLAYER_SPRITE_HEIGHT;

    playerChar.verticalOffset = PLAYER_SPRITE_DOWN;
    playerChar.animFrames = 1;
    playerChar.animSpeed = 1000;

    if (!playerChar.texture.loadFromFile(playerChar.path))
        std::cout << "Failed to load from file: " << playerChar.path << std::endl;
}

/* The puzzle cipher */

#define PUZZLE_CIPHER_PATH "assets/imgs/KeyMAIN_TWO.png"

NPC puzzleCipherChar;
void initPuzzleCipherSprite()
{
    puzzleCipherChar.path = "assets/sprites/key_puzzle.png";
    puzzleCipherChar.name = "Puzzle";
    puzzleCipherChar.width = 25;
    puzzleCipherChar.height = 25;

    puzzleCipherChar.animFrames = 1;
    puzzleCipherChar.animSpeed = 1000;

    if (!puzzleCipherChar.texture.loadFromFile(puzzleCipherChar.path))
        std::cout << "Failed to load from file: " << puzzleCipherChar.path << std::endl;
}



/* Background constants */

#define BACKGROUND_MENU_PATH "assets/imgs/ParallexBG.png"
#define BACKGROUND_DEMO_PATH "assets/imgs/demo-bg-sprite.jpg"
#define BACKGROUND_OPTIMUS_PRIME_PATH "assets/imgs/main-bg.png"
#define BACKGROUND_TEST_PATH "assets/imgs/SceneOne.png"
#define BACKGROUND_ROCK_PATH "assets/imgs/rockbackground.png"
#define BACKGROUND_CIPHER_PATH "assets/imgs/cipher.png"
#define BACKGROUND_CIPHER_COMPLETE_PATH "assets/imgs/cipher_complete.png"
#define FOREGROUND_CIPHER_PATH "assets/imgs/cipher_foreground.png"
#define BACKGROUND_VIGENERE_PATH "assets/imgs/vigenere-cipher.png"
#define BACKGROUND_BRAILLE_PATH "assets/imgs/braille_cipher.png"

sf::Texture menuBgTexture;


/* Keys */

#define KEYS_SPRITE_PATH "assets/sprites/Keys.png"
const sf::IntRect KEY_SPRITE_ROCK(sf::Vector2i(0, 0), sf::Vector2i(32, 32));
const sf::IntRect KEY_SPRITE_HORSE(sf::Vector2i(96, 0), sf::Vector2i(32, 32));
const sf::IntRect KEY_SPRITE_CIPHER(sf::Vector2i(32, 0), sf::Vector2i(32, 32));


/* Fonts */

#define UI_FONT_HEAD_LOCATION "assets/fonts/8-bit Arcade In.ttf"
#define UI_FONT_BODY_LOCATION "assets/fonts/Retro Gaming.ttf"

/* UI Sprite */
#define UI_SPRITE_PATH "assets/sprites/GUI.png"

// SPECIFIC PORTIONS OF THE TEXTURE TO RENDER
const sf::IntRect UI_SPR_BTN_SQUARE(sf::Vector2i(1, 81), sf::Vector2i(14, 14));
const sf::IntRect UI_SPR_BTN_SQUARE_PRESSED(sf::Vector2i(17, 81), sf::Vector2i(14, 14));

const sf::IntRect UI_SPR_BTN(sf::Vector2i(113, 81), sf::Vector2i(30, 14));
const sf::IntRect UI_SPR_BTN_PRESSED(sf::Vector2i(113, 97), sf::Vector2i(30, 14));

const sf::IntRect UI_SPR_DIALOG_BG(sf::Vector2i(0, 96), sf::Vector2i(48, 32));
