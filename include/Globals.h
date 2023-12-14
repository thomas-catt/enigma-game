/* Global.h *
 * Function prototypes for the methods in other files like Render.cpp, Physics
 * .cpp etc.
 *
 * */

void onOverrideEvent(sf::Event event);
void onOverridePreRender(sf::RenderWindow& window);
void onOverrideRender(sf::RenderWindow& window);

Scene currentScene;
void loadScene(Scene scene, bool positionFromSaveFile = false);
void clearScene();
bool PhysicsValidatePosition(sf::Vector2f testPosition);
void renderInteraction(sf::RenderWindow& window, InteractionPoint interaction);
void miniGameDefeat(Minigame lostMiniGame);
void miniGameVictory(Minigame wonMiniGame, bool& wonKey);
void handleDialog(Dialog dialog);
void handleTravel(SceneLocation location, bool positionFromSaveFile = false);
void setView();
void onCipherSceneCreate();

sf::View uiView;
sf::View defaultView;
sf::Clock gameClock;
int framecount = 0;
bool isGamePaused = false;
std::string uiStatus = "";
std::string menuStatus = "";
sf::Texture uiSpriteTexture;
sf::Texture keysSpriteTexture;
sf::Texture puzzleCipherTexture;
sf::Texture rockTexture;
sf::Texture redRockTexture;
sf::Texture platformerPlatformTexture;
sf::Texture platformerObstacleTexture;

bool isDialogOpen = false;
bool isPopupOpen = false;
bool isImagePopupOpen = false;
Dialog currentDialog;
std::string currentDialogText = "";
std::string currentPopupTitle = "";
std::string currentPopupBodyText = "";
std::string currentPopupImage = "";
Scene sceneToLoad;
int loadingScene = 0;
bool sceneLoaded = false;
bool loadPositionFromFile = false;
bool newGame = false;
bool guideIntroduced = false;
int currentDialogIndex = 0;
int currentDialogStrCharacterIndex = 0;
NPC currentDialogNPC;
Dialog minigameFeedbackDialog;
bool showMinigameFeedbackDialog = false;
int currentIntro = -1;
bool introCompleted = false;

bool puzzleCipherCompleted = false;
bool vigenereCipherCompleted = false;
bool brailleCipherCompleted = false;


void pauseGame();
void resumeGame();
void saveGame();
int countKeys();
std::string setKeysDialogTx();

Scene initMenuScene();

sf::Vector2f centerByDimensions(sf::Vector2f orgVector, sf::Vector2i dimensions, bool invertAlignment = false);
sf::Text dropShadow(sf::Text tx);

sf::Sprite newButton(sf::Vector2f position, bool dontCenterByDimensions = false);
sf::Sprite newButtonSquare(sf::Vector2f position, bool dontCenterByDimensions = false);
void createPopup(std::string titleText, std::string bodyText);
void createImagePopup(std::string imgPath);

float menuBgPosition = 0;
MenuItem menuCurrentSelection = MENU_PLAY;
const int menuItemsLength = 3;
std::string menuItemNames[menuItemsLength] = {
    "Play",
    "Credits",
    "Quit",
};

const int gameMenuItemsLength = 2;
GameMenuItem gameMenuCurrentSelection = GAME_MENU_PLAY;
std::string gameMenuItemNames[gameMenuItemsLength] = {
    "Resume",
    "Main Menu",
};