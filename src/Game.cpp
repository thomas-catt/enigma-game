/* Game.cpp *
 * Contains all the game logic, other than rendering content on the screen.
 *
 * */

void pauseGame()
{
    isGamePaused = true;
}

void resumeGame()
{
    isGamePaused = false;
    isDialogOpen = false;
    isPopupOpen = false;
    isImagePopupOpen = false;
    gameMenuCurrentSelection = GAME_MENU_PLAY;
}

void saveGame() {
    if (currentScene.location == SCENE_CREDITS || currentScene.location == SCENE_MAIN_MENU || currentScene.type == SCENE_CUSTOM || currentScene.location == SCENE_CIPHER_GAME) return;

    lastSceneLocation = currentScene.location;
    lastPlayerPosition = player.sprite.getPosition();
    WriteSaveFile(keysStore.rock, keysStore.horse, keysStore.cipher, currentScene.location, guideIntroduced, player.sprite.getPosition());
}

int countKeys() {
    return ((int)keysStore.horse + (int)keysStore.rock + (int)keysStore.cipher);
}

std::string setKeysDialogTx() {
    int keys = countKeys();
    std::cout << "totalkeys: " << keys << std::endl;
    if (keys == 3) {
        return "Congratulations... You have collected all three keys!\n\nHead to your guide to seek what's next...";
    }
    else {
        return "You just completed the challenge successfully and obtained a key. Only " + std::to_string(3 - keys) + " more left. Great work!";
    }
}

void miniGameDefeat(Minigame lostMiniGame) {
    minigameFeedbackDialog = lostMiniGameDialog(lostMiniGame);
    showMinigameFeedbackDialog = true;

    loadScene(initOptimusPrimeScene(), true);
}

void miniGameVictory(Minigame wonMiniGame, bool& wonKey) {
    wonKey = true;
    minigameFeedbackDialog = wonMiniGameDialog(wonMiniGame);
    showMinigameFeedbackDialog = true;

    loadScene(initOptimusPrimeScene(), true);
}

void onGameMenuNavigation(InputAction action, int value = 0) {
    switch (action) {
        case INPUT_NAVIGATE:
            // Incrementing an enum (Casting back and forth between int and enum MenuItem):
            // https://stackoverflow.com/a/3475181
            gameMenuCurrentSelection = (GameMenuItem)((int)gameMenuCurrentSelection + value);

        if ((int)gameMenuCurrentSelection < 0) gameMenuCurrentSelection = (GameMenuItem)(gameMenuItemsLength - 1);
            else if ((int)gameMenuCurrentSelection >= gameMenuItemsLength) gameMenuCurrentSelection = (GameMenuItem)(0);

            break;

        case INPUT_SELECT:
            switch (gameMenuCurrentSelection) {
                case GAME_MENU_PLAY:
                    resumeGame();
                    break;

                case GAME_MENU_QUIT:
                    resumeGame();
                    // Save the game whenever the player quits to main menu
                    saveGame();
                    clearScene();
                    loadScene(initMenuScene());
                    break;
            }
            break;

    }
}


/* The playerLoop runs every frame, and handles all the player logic.
 * */
void playerLoop()
{
    if (!player.moving)
        player.currentAnimFrame = 0;
    else if (framecount % (REFRESH_RATE * PLAYER_ANIM_SPEED / 1000) == 0)
    {
        player.currentAnimFrame++;
        if (player.currentAnimFrame > PLAYER_ANIM_FRAMES)
            player.currentAnimFrame = 1;
    }

    bool isDiagonalMovement = abs(player.movementVector.x / PLAYER_MOVE_MULTIPLIER) && abs(player.movementVector.y / PLAYER_MOVE_MULTIPLIER);
    sf::Vector2f effectiveMovementVector = player.movementVector;

    if (player.moving)
    {
        player.prevPosition = player.sprite.getPosition();

        if (player.movementVector.x / PLAYER_MOVE_MULTIPLIER == -1)
            player.direction = PLAYER_SPRITE_LEFT;
        if (player.movementVector.x / PLAYER_MOVE_MULTIPLIER == 1)
            player.direction = PLAYER_SPRITE_RIGHT;
        if (player.movementVector.y / PLAYER_MOVE_MULTIPLIER == -1 && !currentScene.horizontalMovementOnly)
            player.direction = PLAYER_SPRITE_UP;
        if (player.movementVector.y / PLAYER_MOVE_MULTIPLIER == 1 && !currentScene.horizontalMovementOnly)
            player.direction = PLAYER_SPRITE_DOWN;

        // Normalizing input vector

        if (isDiagonalMovement)
        {
            effectiveMovementVector.x = player.movementVector.x * (0.707f);
            effectiveMovementVector.y = player.movementVector.y * (0.707f);
        }

        // Physics checks:
        // Validate new player position before moving the player sprite

        if (!PhysicsValidatePosition(sf::Vector2f(player.sprite.getPosition().x + effectiveMovementVector.x, player.sprite.getPosition().y)))
            effectiveMovementVector.x = 0;

        if (!PhysicsValidatePosition(sf::Vector2f(player.sprite.getPosition().x, player.sprite.getPosition().y + effectiveMovementVector.y)))
            effectiveMovementVector.y = 0;

        if (currentScene.horizontalMovementOnly) {
            effectiveMovementVector.y = 0;
            effectiveMovementVector.x = player.movementVector.x;
        }

        effectiveMovementVector.x *= currentScene.playerSpeedMultiplier;
        effectiveMovementVector.y *= currentScene.playerSpeedMultiplier;

        player.sprite.move(effectiveMovementVector);

//        std::cout << "player position: " << player.sprite.getPosition().x << " " << player.sprite.getPosition().y << std::endl;

        if (player.movementVector.x == 0 && player.movementVector.y == 0)
            player.moving = false;
    }

    sf::IntRect positionRect = sf::IntRect(player.currentAnimFrame * PLAYER_SPRITE_WIDTH, player.direction * PLAYER_SPRITE_HEIGHT, PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT);
    player.sprite.setTextureRect(positionRect);

    setView();
}

void postInteraction(DialogID DialogIdentifier) {
    switch (DialogIdentifier) {
        case DIALOG_GUIDE_HELP:
            if (countKeys() == 3) {
                loadScene(initEndScreenTextScene());
            }
            break;
        case DIALOG_GUIDE_INTRODUCTION:
            guideIntroduced = true;
            currentScene.interactibles[0].dialog = noGoingBackDialog();
            saveGame();
            break;
        case DIALOG_PLAYER_BEFORE_CAVE:
            loadScene(initOptimusPrimeScene());
            break;
        case DIALOG_ROCK_GAME:
            loadScene(initRockScene());
            break;
        case DIALOG_CIPHER_GAME:
            loadScene(initCipherScene());
            break;
        case DIALOG_PLATFORMER_GAME:
            loadScene(initPlatformerScene());
            break;
        case DIALOG_MINIGAME_VICTORY:
            saveGame();
            break;
        case DIALOG_CIPHER_GOBACK:
            if (puzzleCipherCompleted && vigenereCipherCompleted && brailleCipherCompleted)
                miniGameVictory(MINIGAME_CIPHER, keysStore.cipher);
            break;
    }
}

void nextDialog()
{
    if (!isDialogOpen)
        return;

    if (currentDialogText[currentDialogStrCharacterIndex] != '\0') {
        currentDialogStrCharacterIndex = 200; // Jugaar :(
        return;
    }
    currentDialogIndex++;
    currentDialogStrCharacterIndex = 0;

    if (!currentDialog.messages[currentDialogIndex].speaker.animFrames) {
        // checking if the next dialog message exists
        resumeGame();
        postInteraction(currentDialog.identifier);
    }
    currentDialogText = currentDialog.messages[currentDialogIndex].message;
    currentDialogNPC = currentDialog.messages[currentDialogIndex].speaker;
}

void handleTravel(SceneLocation location, bool positionFromSaveFile)
{

    switch (location)
    {
    case SCENE_DEMO_SCENE:
        loadScene(initDemoScene(), positionFromSaveFile);
        break;
    case SCENE_SNAKE_GAME:
        loadScene(initSnakeScene(), positionFromSaveFile);
        break;
    case SCENE_OVERWORLD:
        loadScene(initTestScene(), positionFromSaveFile);
        break;
    case SCENE_ROCK_GAME:
        loadScene(initRockScene(), positionFromSaveFile);
        break;
    case SCENE_OPTIMUS:
        loadScene(initOptimusPrimeScene(), positionFromSaveFile);
        break;
    case SCENE_CIPHER_GAME:
        loadScene(initCipherScene(), positionFromSaveFile);
        break;
    case SCENE_CIPHER_PUZZLE:
        loadScene(initPuzzleCipherScene(), positionFromSaveFile);
        break;
    case SCENE_CIPHER_VIGENERE:
        loadScene(initVigenereCipherScene(), positionFromSaveFile);
        break;
    case SCENE_CIPHER_BRAILLE:
        loadScene(initBrailleCipherScene(), positionFromSaveFile);
        break;
    case SCENE_PLATFORMER_GAME:
        loadScene(initPlatformerScene(), positionFromSaveFile);
        break;
    }
}

void handleDialog(Dialog dialog)
{
    pauseGame();
    isDialogOpen = true;

    currentDialog = dialog;
    currentDialogIndex = -1;
    currentDialogText = "";
    nextDialog();
}

void handleInteraction(InteractionPoint interaction)
{
    // Don't respond to interactions when the game is paused
    if (isGamePaused)
        return;
    else if (interaction.name == INTERACTION_NULL)
        return;

    switch (interaction.name)
    {
    case INTERACTION_NULL:
        return;
        break;

    case INTERACTION_TRAVEL:
        // Save the game whenever the player goes to a new scene
        saveGame();
        handleTravel(interaction.travelTo);
        break;

    case INTERACTION_TALK:
        // Save the game whenever the player interacts with an NPC
        saveGame();
        handleDialog(interaction.dialog);
        break;
    }
}

void interactionLoop(sf::RenderWindow &window)
{
    // The InteractionPoint variable, this will set the closest interaction to the player
    InteractionPoint interactionInRange;

    for (int i = 0; currentScene.interactibles[i].name != INTERACTION_NULL; i++)
    {
        InteractionPoint interaction = currentScene.interactibles[i];
        sf::Vector2f correctedIntercationPosition = centerByDimensions(interaction.position, sf::Vector2i(INTERACTIBLE_THRESHOLD, INTERACTIBLE_THRESHOLD));
        interaction.position = correctedIntercationPosition;
        int displacementX = abs(interaction.position.x - (player.sprite.getPosition().x + (PLAYER_SPRITE_WIDTH / 2)));
        int displacementY = abs(interaction.position.y - (player.sprite.getPosition().y + (PLAYER_SPRITE_HEIGHT / 2)));

        int displacement = sqrt((displacementX * displacementX) + (displacementY * displacementY));

        if (displacement < INTERACTIBLE_THRESHOLD)
        {
            interactionInRange = interaction;
            player.interactionInRange = interaction;
            renderInteraction(window, interaction);
        }
    }

    player.interactionInRange = interactionInRange;
    if (interactionInRange.name == INTERACTION_NULL)
    { // If there is no interaction in range
        uiStatus = "";
    }
    else
    {
        uiStatus = "[INTERACT] Press E - " + interactionInRange.label;
    }
}
