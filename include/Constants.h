/* Constants.h *
 * Includes all the constant values stuff of the entire project, excluding all
 * asset related constants, which are in Assets.h.
 *
 * */

/* Window & Graphics Options */

#define SCREEN_W 800
#define SCREEN_H 600
#define WINDOW_TITLE "Course Project"
#define REFRESH_RATE 60
#define DEBUG_MODE 0

/* Game values */

#define PI 3.141
#define SAVE_FILE_NAME "save.dat"
#define PLAYER_MOVE_MULTIPLIER 2  // PLAYER SPEED
#define INTERACTIBLE_THRESHOLD 60 // DISTANCE TO TRIGGER INTERACTION EVENT
#define MUSIC_MAX_VOL 75
const float MENU_BG_SCROLL_SPEED = 10.f;
const float SCENE_FADE_SPEED = 10.f;
const float INTRO_SCREEN_TIME = 4.f;
const float END_SCREEN_TIME = 31.f;

enum MenuItem
{
    MENU_PLAY,
    MENU_ABOUT,
    MENU_QUIT
};

enum GameMenuItem
{
    GAME_MENU_PLAY,
    GAME_MENU_QUIT
};

/* Game controls */

const sf::Keyboard::Key KEY_UP = sf::Keyboard::W;
const sf::Keyboard::Key KEY_UP_ALT = sf::Keyboard::Up;
const sf::Keyboard::Key KEY_LEFT = sf::Keyboard::A;
const sf::Keyboard::Key KEY_LEFT_ALT = sf::Keyboard::Left;
const sf::Keyboard::Key KEY_DOWN = sf::Keyboard::S;
const sf::Keyboard::Key KEY_DOWN_ALT = sf::Keyboard::Down;
const sf::Keyboard::Key KEY_RIGHT = sf::Keyboard::D;
const sf::Keyboard::Key KEY_RIGHT_ALT = sf::Keyboard::Right;

const sf::Keyboard::Key KEY_ACTION = sf::Keyboard::E;
const sf::Keyboard::Key KEY_NEXT = sf::Keyboard::Space;
const sf::Keyboard::Key KEY_NEXT_ALT = sf::Keyboard::Enter;

const sf::Keyboard::Key KEY_NAV_UP = sf::Keyboard::Up;
const sf::Keyboard::Key KEY_NAV_UP_ALT = sf::Keyboard::W;
const sf::Keyboard::Key KEY_NAV_LEFT = sf::Keyboard::Left;
const sf::Keyboard::Key KEY_NAV_LEFT_ALT = sf::Keyboard::A;
const sf::Keyboard::Key KEY_NAV_DOWN = sf::Keyboard::Down;
const sf::Keyboard::Key KEY_NAV_DOWN_ALT = sf::Keyboard::S;
const sf::Keyboard::Key KEY_NAV_RIGHT = sf::Keyboard::Right;
const sf::Keyboard::Key KEY_NAV_RIGHT_ALT = sf::Keyboard::D;

const sf::Keyboard::Key KEY_NAV_SELECT = sf::Keyboard::Enter;
const sf::Keyboard::Key KEY_NAV_SELECT_ALT = sf::Keyboard::Space;
const sf::Keyboard::Key KEY_NAV_BACK = sf::Keyboard::Escape;

/* Fonts & Sizes */
sf::Font UI_FONT_HEAD, UI_FONT_BODY;
const int UI_HEAD_1_SIZE = 65;
const int UI_HEAD_2_SIZE = 54;
const int UI_HEAD_3_SIZE = 45;
const int UI_BODY_1_SIZE = 30;
const int UI_BODY_2_SIZE = 22;
const int UI_BODY_3_SIZE = 14;
const int UI_SMALL_1_SIZE = 11;
const int UI_SMALL_2_SIZE = 8;
const int UI_SMALL_3_SIZE = 5;

/* Structures & related enums */

/* SceneType defines the type of a Scene struct (in Scene::type).
 * SCENE_MENU is the MenuScene.cpp,
 * SCENE_GAME will be any scene using the engine's player, view, and physics
 * management.
 * SCENE_CUSTOM will be used for any custom handling.
 * */

enum SceneType
{
    SCENE_MENU,
    SCENE_GAME,
    SCENE_CUSTOM
};

/* InputAction for the keyboard navigation. Used by the menu handling.
 * */

enum InputAction
{
    INPUT_NAVIGATE,
    INPUT_SELECT,
    INPUT_BACK
};

/* SceneLocation will basically contain identifiers for all the locations the
 * player can travel to. (A little messy because this is a workaround to the
 * no-OOP restriction we have). Open to improvements.
 *
 * */

enum SceneLocation
{
    SCENE_INTRO,
    SCENE_END,
    SCENE_OVERWORLD,
    SCENE_DEMO_SCENE,
    SCENE_MAIN_MENU,
    SCENE_CREDITS,
    SCENE_OPTIMUS,
    SCENE_ROCK_GAME,
    SCENE_CIPHER_GAME,
    SCENE_CIPHER_PUZZLE,
    SCENE_CIPHER_VIGENERE,
    SCENE_CIPHER_BRAILLE,
    SCENE_PLATFORMER_GAME,
    SCENE_SNAKE_GAME
};

enum Minigame {
    MINIGAME_ROCK_FALLING,
    MINIGAME_PLATFORMER,
    MINIGAME_CIPHER
};

/* The Interaction enum will list all the interactions of the game. When these
 * interactions are to be made, the code in handleInteraction() will use a
 * switch statement to compare and run the desired function for the
 * intractable.
 */

enum Interaction
{
    INTERACTION_NULL,
    INTERACTION_TRAVEL,
    INTERACTION_TALK
};

enum DialogID {
    DIALOG_NULLID,
    DIALOG_GUIDE_HELP,
    DIALOG_GUIDE_INTRODUCTION,
    DIALOG_PLAYER_BEFORE_CAVE,
    DIALOG_ROCK_GAME,
    DIALOG_PLATFORMER_GAME,
    DIALOG_CIPHER_GAME,
    DIALOG_MINIGAME_VICTORY,
    DIALOG_MINIGAME_DEFEAT,
    DIALOG_CIPHER_GOBACK,
};

/* The NPC struct is primarily for placing animated Non-Playable Characters in
 * a scene. Any scene has an array of these, and NPCs are defined in Assets.h.
 *
 * */
struct NPC
{
    sf::Texture texture;
    std::string path;
    sf::Vector2f position;
    std::string name;
    int verticalOffset = 0;
    int width;
    int height;
    int animFrames = 0; // This initializaton acts as an identifier for any
                        // uninitialized NPC object. If animFrames is 0, then
                        // the NPC is null.
    float scaleX = 1;
    float scaleY = 1;
    int animSpeed;
};

/* Now the dialogs. The DialogOption struct is the building block for each
 * dialog (a conversation with an NPC). This will define each of the individual
 * messages that form a dialog.
 * */

struct DialogOption
{
    NPC speaker;
    std::string message;
};

/* The Dialog struct will define a dialog. This
 * contains all info about the conversation, and an array for each DialogOption.
 * */
struct Dialog
{
    std::string title;
    DialogOption messages[64];
    DialogID identifier = DIALOG_NULLID;
};

/* Finally the InteractionPoint struct itself. This struct defines any point of
 * interaction in a scene.
 * */

struct InteractionPoint
{
    Interaction name = INTERACTION_NULL;
    std::string label = "Interact";
    sf::Vector2f position;
    NPC associatedNPC;
    SceneLocation travelTo;
    Dialog dialog;
};

/* The Scene struct: This struct defines every property of a Scene, from its
 * background to the camera settings, from the player properties to the hitboxes
 * and interactibles. Everything of any Scene is stored in a Scene object.
 * */

struct Scene
{
    SceneType type;
    SceneLocation location;
    std::string name; // SCENE NAME
    bool backgroundEnabled = true;
    std::string backgroundSpritePath;
    sf::Texture background;
    sf::Sprite backgroundSprite;
    bool foregroundEnabled = false;
    std::string foregroundSpritePath;
    sf::Texture foreground;
    sf::Sprite foregroundSprite;
    sf::View view = sf::View(sf::FloatRect(0, 0, -1, -1));

    std::string musicFilePath;
    bool musicEnabled = true;
    bool musicLooping = true;

    bool noView = false;
    bool horizontalMovementOnly = false;
    bool playerEnabled = true;
    int defaultPlayerDir;
    sf::Vector2f defaultPlayerPos;
    int playerSpeedMultiplier = 1;

    sf::IntRect colliderHitboxes[384];
    InteractionPoint interactibles[32]; // TRIGGER POINTS
    NPC animatedSprites[32];
    int animatedSpritesFrames[32]; // This is used by a render loop to store the
                                   // current frame of each animated sprite here
};

struct {
    bool rock = false;
    bool horse = false;
    bool cipher = false;
} keysStore;

/* This struct is just for the player. Contains all related stuff about the
 * player.
 * */

struct
{
    sf::Sprite sprite;
    sf::Vector2f movementVector;
    sf::Texture texture;
    sf::Vector2f prevPosition;
    InteractionPoint interactionInRange;

    bool moving;
    int direction;
    int currentAnimFrame;
} player;


