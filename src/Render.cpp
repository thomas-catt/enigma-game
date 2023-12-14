/* Render.cpp
 * This is the heart of the game code. This file has a lot of stuff on player
 * management, scene management and view management that I think can be
 * structured a lot better.
 *
 * */

/* The setView function (should be called "setCamera") sets the camera
 * coordinates according to the position of the character (camera follows player
 * system)
 * */
void setView()
{
    if (!currentScene.playerEnabled)
        return;

    sf::Vector2f playerPos = player.sprite.getPosition();
    sf::Vector2f viewCenter;

    currentScene.view.setCenter(sf::Vector2f(playerPos.x + (PLAYER_SPRITE_WIDTH / 2), playerPos.y + (PLAYER_SPRITE_HEIGHT / 2)));
    viewCenter = currentScene.view.getCenter();
    //    std::cout << "view center: x: " << viewCenter.x << " y: " << viewCenter.y << std::endl;

    int leftCorner = currentScene.view.getSize().x / 2;
    int rightCorner = currentScene.background.getSize().x - leftCorner;
    int topCorner = currentScene.view.getSize().y / 2;
    int bottomCorner = currentScene.background.getSize().y - topCorner;

    bool isViewPassingLeftSide = viewCenter.x < leftCorner;
    bool isViewPassingTopSide = viewCenter.y < topCorner;

    bool isViewPassingRightSide = viewCenter.x > rightCorner;
    bool isViewPassingBottomSide = viewCenter.y > bottomCorner;

    // KEEP CAMERA WITHIN LIMITS

    if (isViewPassingLeftSide && isViewPassingTopSide)
        currentScene.view.setCenter(leftCorner, topCorner);

    else if (isViewPassingRightSide && isViewPassingTopSide)
        currentScene.view.setCenter(rightCorner, topCorner);

    else if (isViewPassingRightSide && isViewPassingBottomSide)
        currentScene.view.setCenter(rightCorner, bottomCorner);

    else if (isViewPassingLeftSide && isViewPassingBottomSide)
        currentScene.view.setCenter(leftCorner, bottomCorner);

    else if (isViewPassingLeftSide)
        currentScene.view.setCenter(leftCorner, viewCenter.y);

    else if (isViewPassingTopSide)
        currentScene.view.setCenter(viewCenter.x, topCorner);

    else if (isViewPassingRightSide)
        currentScene.view.setCenter(rightCorner, viewCenter.y);

    else if (isViewPassingBottomSide)
        currentScene.view.setCenter(viewCenter.x, bottomCorner);
}

void clearScene() {
    uiStatus = "";
    menuStatus = "";
    InteractionPoint nullInteraction;
    player.interactionInRange = nullInteraction;
}

/* The loadScene simply loads up the scene passed as the parameter. The previous
 * scene objects are automatically stashed.
 *
 * */
void loadScene(Scene scene, bool positionFromSaveFile)
{
    if (sceneLoaded) {
        if (loadingScene > 0)
            loadingScene -= SCENE_FADE_SPEED;
        if (loadingScene <= 0)
            sceneLoaded = false;

    } else {
        if (loadingScene < 100) {
            sceneToLoad = scene;
            loadPositionFromFile = positionFromSaveFile;
            loadingScene += SCENE_FADE_SPEED;
        } else {
            sceneLoaded = true;
        }
    }
//    currentMusic.setVolume(loadingScene);
    if (loadingScene < 100 && loadingScene > 0) return;

    clearScene();
    currentScene = scene;
    onSceneInit(currentScene.location);

    if (currentScene.backgroundEnabled) {
        if (!currentScene.background.loadFromFile(currentScene.backgroundSpritePath))
            std::cout << "Failed to load from file: " << currentScene.backgroundSpritePath << std::endl;

        currentScene.backgroundSprite.setTexture(currentScene.background);
    }

    if (currentScene.foregroundEnabled) {
        if (!currentScene.foreground.loadFromFile(currentScene.foregroundSpritePath))
            std::cout << "Failed to load from file: " << currentScene.foregroundSpritePath << std::endl;

        currentScene.foregroundSprite.setTexture(currentScene.foreground);
    }

    if (currentScene.musicEnabled) {
        playMusic(currentScene.musicFilePath);
        currentMusic.setLoop(currentScene.musicLooping);
    }


    if (!player.texture.loadFromFile(PLAYER_SPRITE_PATH))
        std::cout << "Failed to load from file: " << PLAYER_SPRITE_PATH << std::endl;

    sf::Vector2f playerPositionToSet = lastPlayerPosition;
    if (!positionFromSaveFile)
        playerPositionToSet = currentScene.defaultPlayerPos;

    player.sprite.setTexture(player.texture);
    player.sprite.setPosition(playerPositionToSet.x, playerPositionToSet.y);

    player.moving = false;
    player.currentAnimFrame = 0;
    player.direction = currentScene.defaultPlayerDir;

    // Initialize every animating sprite's current frame to the first.
    for (int i = 0; currentScene.animatedSprites[i].animFrames > 0; i++)
    {
        currentScene.animatedSpritesFrames[i] = 1;
    }

    if (currentScene.view.getSize().x == -1) {
        currentScene.view = defaultView;
    }

    playerLoop();
}

void renderInteraction(sf::RenderWindow &window, InteractionPoint interaction)
{

    sf::Vector2f targetPosition = centerByDimensions(player.sprite.getPosition(), sf::Vector2i(PLAYER_SPRITE_WIDTH, PLAYER_SPRITE_HEIGHT));
    targetPosition.x -= 3;  // Fixing the alignment a little bit
    targetPosition.y -= 40; // To make the icon popup a little above the player's head
    sf::Sprite interactionIcon = newButtonSquare(targetPosition);

    sf::Text interactionText;
    interactionText.setString("E");
    interactionText.setFont(UI_FONT_BODY);
    interactionText.setCharacterSize(UI_SMALL_1_SIZE);
    interactionText.setFillColor(sf::Color::White);
    interactionText.setPosition(interactionIcon.getPosition());
    interactionText.setOrigin(-UI_SMALL_1_SIZE / 2, -UI_SMALL_1_SIZE / 4);

    if (framecount > (REFRESH_RATE / 2) && !isGamePaused)
    {
        // if half a second has passed, change the icon into a pressed button
        interactionIcon.setTextureRect(UI_SPR_BTN_SQUARE_PRESSED);

        // also move the text a little lower too
        interactionText.setPosition(interactionText.getPosition().x, interactionText.getPosition().y + 1);
    }

    window.draw(interactionIcon);
    window.draw(interactionText);
}

void NPCsRenderLoop(sf::RenderWindow &window)
{
    for (int i = 0; currentScene.animatedSprites[i].animFrames > 0; i++)
    {
        NPC npcSprite = currentScene.animatedSprites[i];

        if ((framecount % (REFRESH_RATE * npcSprite.animSpeed / 1000) == 0) && !isGamePaused)
        {
            currentScene.animatedSpritesFrames[i]++;
            if (currentScene.animatedSpritesFrames[i] > npcSprite.animFrames)
                currentScene.animatedSpritesFrames[i] = 1;
        }

        sf::Sprite npc;
        npc.setTexture(npcSprite.texture);
        npc.setScale(npcSprite.scaleX, npcSprite.scaleY);
        npc.setTextureRect(sf::IntRect(npcSprite.width * (currentScene.animatedSpritesFrames[i] - 1), npcSprite.verticalOffset * npcSprite.height, npcSprite.width, npcSprite.height));
        npc.setPosition(centerByDimensions(npcSprite.position, sf::Vector2i(npcSprite.width, npcSprite.height), true));

        window.draw(npc);
    }
}

/* The dialogRender function is responsible for all the dialog related rendering
 * */

void dialogRender(sf::RenderWindow &window)
{
    sf::Sprite dialogBg(uiSpriteTexture);
    dialogBg.setTextureRect(UI_SPR_DIALOG_BG);
    dialogBg.setScale(12, 12);
    dialogBg.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W / 2, 50 + SCREEN_H / 2), sf::Vector2i(UI_SPR_DIALOG_BG.width * dialogBg.getScale().x, UI_SPR_DIALOG_BG.height * dialogBg.getScale().y), true));

    sf::Text dialogHead(currentDialogNPC.name, UI_FONT_HEAD);
    dialogHead.setCharacterSize(UI_HEAD_2_SIZE);
    dialogHead.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W / 2, 50 + SCREEN_H / 5), sf::Vector2i(dialogHead.getCharacterSize() * (currentDialogNPC.name.length() / 2), dialogHead.getCharacterSize()), true));

    sf::Texture dialogNPCTexture;
    if (!dialogNPCTexture.loadFromFile(currentDialogNPC.path))
        std::cout << "Failed to load from file: " << currentDialogNPC.path << std::endl;

    sf::Sprite dialogNPCPic;
    dialogNPCPic.setTexture(dialogNPCTexture);
    dialogNPCPic.setTextureRect(sf::IntRect(0, currentDialogNPC.verticalOffset * currentDialogNPC.height, currentDialogNPC.width, currentDialogNPC.height));
    dialogNPCPic.setScale(100.f / currentDialogNPC.height, 100.f / currentDialogNPC.height);
    dialogNPCPic.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W / 2, SCREEN_H / 6), sf::Vector2i(100 * ((float)currentDialogNPC.width / currentDialogNPC.height), 100), true));

    sf::Text dialogBody(currentDialogText, UI_FONT_BODY);
    dialogBody.setPosition(dialogBg.getPosition().x + 80, dialogBg.getPosition().y + 80);
    dialogBody.setCharacterSize(UI_BODY_2_SIZE);

    char textToSet[256];
    int i;
    for (i = 0; i < currentDialogStrCharacterIndex; i++) {
        textToSet[i] = currentDialogText[i];
    }
    textToSet[i] = '\0';
    dialogBody.setString(textToSet);

    if (framecount % (30 * REFRESH_RATE / 1000) == 0 && currentDialogText[currentDialogStrCharacterIndex] != '\0') {
        currentDialogStrCharacterIndex++;
    }

    textWrapper(dialogBody, (UI_SPR_DIALOG_BG.width * dialogBg.getScale().x) - 165);

    sf::Sprite dialogBtnHint = newButton(sf::Vector2f(SCREEN_W / 2 - 15, 50 + SCREEN_H / 1.18));
    dialogBtnHint.setScale(3, 3);
    sf::Text dialogBtnTx("SPACE", UI_FONT_BODY);
    dialogBtnTx.setCharacterSize(UI_BODY_3_SIZE);
    dialogBtnTx.setFillColor(sf::Color::White);
    dialogBtnTx.setPosition(dialogBtnHint.getPosition());

    std::string dialogBtnTxString = dialogBtnTx.getString();
    dialogBtnTx.setOrigin((-UI_BODY_3_SIZE) / 0.85, -UI_BODY_3_SIZE / 1.5);

    if (framecount > (REFRESH_RATE / 2))
    {
        // if half a second has passed, change the icon into a pressed button
        dialogBtnHint.setTextureRect(UI_SPR_BTN_PRESSED);

        // also move the text a little lower too
        dialogBtnTx.setPosition(dialogBtnTx.getPosition().x, dialogBtnTx.getPosition().y + 2);
    }

    window.draw(dialogNPCPic);
    window.draw(dialogBg);
    window.draw(dialogHead);
    window.draw(dialogBody);
    window.draw(dialogBtnHint);
    window.draw(dialogBtnTx);
}

void gameMenuRender(sf::RenderWindow& window) {
    // don't accidentally render the game menu when the player is already on
    // the main menu
    if (currentScene.type == SCENE_MENU) return;

    sf::Text menuTitle("Paused", UI_FONT_HEAD);
    menuTitle.setPosition(25, 25);
    menuTitle.setCharacterSize(UI_HEAD_1_SIZE);
    menuTitle.setFillColor(sf::Color::White);

    sf::Text menuItems[3];
    for (int i = 0; i < gameMenuItemsLength; i++) {
        menuItems[i].setString(gameMenuItemNames[i]);
        menuItems[i].setFont(UI_FONT_BODY);
        menuItems[i].setCharacterSize(UI_BODY_1_SIZE);
        menuItems[i].setPosition(40, 50 + 45 * (i + 2));
        menuItems[i].setFillColor(sf::Color::White);

        if (gameMenuCurrentSelection == i) {
            sf::Text menuSelection;
            menuSelection.setString(">");
            menuSelection.setFont(UI_FONT_BODY);
            menuSelection.setCharacterSize(UI_BODY_1_SIZE);
            menuSelection.setPosition(10, 50 + 45 * (i + 2));
            menuSelection.setFillColor(sf::Color(0, 255, 0));

            menuItems[i].setFillColor(sf::Color(0, 255, 0));
            menuItems[i].setString(gameMenuItemNames[i] + " <");

            window.draw(menuSelection);
        }

        window.draw(menuItems[i]);
    }

    if (menuStatus.length())
    { // this will be true when the uiStatus has text
        sf::Text menuObjectiveText(menuStatus, UI_FONT_BODY);
        menuObjectiveText.setPosition(40, SCREEN_H - 100);
        menuObjectiveText.setCharacterSize(UI_BODY_2_SIZE);
        textWrapper(menuObjectiveText, SCREEN_W - 80);
        std::string textStr = menuObjectiveText.getString();
        menuObjectiveText.setPosition(menuObjectiveText.getPosition().x, menuObjectiveText.getPosition().y - (stringCountOccurences(textStr, '\n') * menuObjectiveText.getCharacterSize()));

        window.draw(menuObjectiveText);
    }

    window.draw(menuTitle);
}


void renderImagePopup(sf::RenderWindow& window, std::string imgPath) {
    sf::Texture popupImgTexture;
    if (!popupImgTexture.loadFromFile(imgPath)) {
        std::cout << "Failed to load popup image: " << imgPath << std::endl;
        return;
    }

    sf::Sprite popupImg(popupImgTexture);
    popupImg.setPosition(centerByDimensions(sf::Vector2f (SCREEN_W/2, SCREEN_H/2), sf::Vector2i(popupImgTexture.getSize().x, popupImgTexture.getSize().y), true));

    sf::Sprite popupBtnHint = newButton(sf::Vector2f(SCREEN_W / 2 - 15, SCREEN_H - 50));
    popupBtnHint.setScale(3, 3);
    sf::Text popupBtnTx("SPACE", UI_FONT_BODY);
    popupBtnTx.setCharacterSize(UI_BODY_3_SIZE);
    popupBtnTx.setFillColor(sf::Color::White);
    popupBtnTx.setPosition(popupBtnHint.getPosition());

    std::string popupBtnTxString = popupBtnTx.getString();
    popupBtnTx.setOrigin((-UI_BODY_3_SIZE) / 0.85, -UI_BODY_3_SIZE / 1.5);

    if (framecount > (REFRESH_RATE / 2))
    {
        // if half a second has passed, change the icon into a pressed button
        popupBtnHint.setTextureRect(UI_SPR_BTN_PRESSED);

        // also move the text a little lower too
        popupBtnTx.setPosition(popupBtnTx.getPosition().x, popupBtnTx.getPosition().y + 2);
    }

    window.draw(popupImg);
    window.draw(popupBtnHint);
    window.draw(popupBtnTx);
}

void renderPopup(sf::RenderWindow& window, std::string titleText, std::string bodyText) {
    sf::Sprite popupBg(uiSpriteTexture);
    popupBg.setTextureRect(UI_SPR_DIALOG_BG);
    popupBg.setScale(16, 16);
    popupBg.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W / 2, SCREEN_H / 2 - 30), sf::Vector2i(UI_SPR_DIALOG_BG.width * popupBg.getScale().x, UI_SPR_DIALOG_BG.height * popupBg.getScale().y), true));

    sf::Text popupHead(titleText, UI_FONT_HEAD);
    popupHead.setCharacterSize(UI_HEAD_2_SIZE);
    popupHead.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W / 2, SCREEN_H / 6 - 60), sf::Vector2i(popupHead.getCharacterSize() * (titleText.length() / 2), popupHead.getCharacterSize()), true));

    sf::Text popupBody(bodyText, UI_FONT_BODY);
    popupBody.setPosition(popupBg.getPosition().x + 105, popupBg.getPosition().y + 100);
    popupBody.setCharacterSize(UI_BODY_2_SIZE);
    textWrapper(popupBody, (UI_SPR_DIALOG_BG.width - 15) * popupBg.getScale().x);

    sf::Sprite popupBtnHint = newButton(sf::Vector2f(SCREEN_W / 2 - 15, SCREEN_H - 50));
    popupBtnHint.setScale(3, 3);
    sf::Text popupBtnTx("SPACE", UI_FONT_BODY);
    popupBtnTx.setCharacterSize(UI_BODY_3_SIZE);
    popupBtnTx.setFillColor(sf::Color::White);
    popupBtnTx.setPosition(popupBtnHint.getPosition());

    std::string popupBtnTxString = popupBtnTx.getString();
    popupBtnTx.setOrigin((-UI_BODY_3_SIZE) / 0.85, -UI_BODY_3_SIZE / 1.5);

    if (framecount > (REFRESH_RATE / 2))
    {
        // if half a second has passed, change the icon into a pressed button
        popupBtnHint.setTextureRect(UI_SPR_BTN_PRESSED);

        // also move the text a little lower too
        popupBtnTx.setPosition(popupBtnTx.getPosition().x, popupBtnTx.getPosition().y + 2);
    }

    window.draw(popupBg);
    window.draw(popupHead);
    window.draw(popupBody);
    window.draw(popupBtnHint);
    window.draw(popupBtnTx);
}

/* The UILayer function renders the UI of the game. It renders above the game
 * objects, right after setting the uiView as the view (window.setView).
 *
 * */
void UILayer(sf::RenderWindow &window)
{

    if (!isGamePaused)
    {
        /* The bottom statusbar */

        if (uiStatus.length())
        { // this will be true when the uiStatus has text
            sf::RectangleShape uiStatusBg(sf::Vector2f(SCREEN_W, UI_BODY_2_SIZE + 10));
            uiStatusBg.setPosition(0, SCREEN_H - 10);
            uiStatusBg.setOrigin(sf::Vector2f(0, UI_BODY_2_SIZE));
            uiStatusBg.setFillColor(sf::Color(0, 0, 0, 100));
            window.draw(uiStatusBg);
        }

        sf::Text uiStatusTx;
        uiStatusTx.setString(uiStatus);
        uiStatusTx.setFont(UI_FONT_BODY);
        uiStatusTx.setCharacterSize(UI_BODY_2_SIZE);
        uiStatusTx.setFillColor(sf::Color::White);
        uiStatusTx.setPosition(0, SCREEN_H);
        uiStatusTx.setOrigin(-10, UI_BODY_2_SIZE + 10);

        window.draw(uiStatusTx);

        /* The keys indicator: only shown in a game scene */
        if (currentScene.type == SCENE_GAME && guideIntroduced) {
            sf::Sprite keyRock(keysSpriteTexture);
            keyRock.setTextureRect(KEY_SPRITE_ROCK);
            keyRock.setScale(2, 2);
            keyRock.setPosition(SCREEN_W - 228, 36);
            if (!keysStore.rock)
                keyRock.setColor(sf::Color(0, 0, 0, 100));

            sf::Sprite keyHorse(keysSpriteTexture);
            keyHorse.setTextureRect(KEY_SPRITE_HORSE);
            keyHorse.setScale(2, 2);
            keyHorse.setPosition(SCREEN_W - 164, 36);
            if (!keysStore.horse)
                keyHorse.setColor(sf::Color(0, 0, 0, 100));

            sf::Sprite keyCipher(keysSpriteTexture);
            keyCipher.setTextureRect(KEY_SPRITE_CIPHER);
            keyCipher.setScale(2, 2);
            keyCipher.setPosition(SCREEN_W - 100, 36);
            if (!keysStore.cipher)
                keyCipher.setColor(sf::Color(0, 0, 0, 100));

            window.draw(keyRock);
            window.draw(keyHorse);
            window.draw(keyCipher);
        }
    }
    /* The dialogs stuff
     * */

    if (isGamePaused)
    {
        sf::RectangleShape gamePauseScreenDarken(sf::Vector2f(SCREEN_W, SCREEN_H));
        gamePauseScreenDarken.setPosition(0, 0);
        gamePauseScreenDarken.setFillColor(sf::Color(0, 0, 0, 128));

        window.draw(gamePauseScreenDarken);

        if (isPopupOpen) {
            renderPopup(window, currentPopupTitle, currentPopupBodyText);
        } else if (isImagePopupOpen) {
            renderImagePopup(window, currentPopupImage);
        } else if (isDialogOpen) {
            dialogRender(window);
        } else {
            gameMenuRender(window);
        }
    }

    // Scene loading fade:
    if (loadingScene) {
        loadingScene = loadingScene > 100 ? 100 : loadingScene;
        loadingScene = loadingScene < 0 ? 0 : loadingScene;

        sf::RectangleShape sceneLoadScreenDarken(sf::Vector2f(SCREEN_W, SCREEN_H));
        sceneLoadScreenDarken.setPosition(0, 0);
        sceneLoadScreenDarken.setFillColor(sf::Color(0, 0, 0, 255 * loadingScene / 100));

        window.draw(sceneLoadScreenDarken);
    }
}

/* Debug mode render:
 * This only runs when the DEBUG_MODE is enabled in Constants.h.
 *
 * */
void renderDebug(sf::RenderWindow &window)
{
    for (int i = 0; currentScene.interactibles[i].name != INTERACTION_NULL; i++)
    {
        sf::Vector2f targetPos = centerByDimensions(currentScene.interactibles[i].position, sf::Vector2i(INTERACTIBLE_THRESHOLD, INTERACTIBLE_THRESHOLD));
        sf::RectangleShape rect(sf::Vector2f(INTERACTIBLE_THRESHOLD, INTERACTIBLE_THRESHOLD));
        rect.setPosition(sf::Vector2f(targetPos.x - (INTERACTIBLE_THRESHOLD / 2), targetPos.y - (INTERACTIBLE_THRESHOLD / 2)));
        rect.setFillColor(sf::Color::Green);
        window.draw(rect);
    }

    for (int i = 0; !(currentScene.colliderHitboxes[i].width - currentScene.colliderHitboxes[i].height == currentScene.colliderHitboxes[i].width); i++)
    {
        sf::IntRect hitbox = currentScene.colliderHitboxes[i];

        sf::RectangleShape rect(sf::Vector2f(hitbox.width, hitbox.height));
        rect.setPosition(sf::Vector2f(hitbox.left, hitbox.top));
        rect.setFillColor(sf::Color(255, 0, 0, 100));
        window.draw(rect);
    }
}

void Render(sf::RenderWindow &window)
{
    window.clear();

    // Sets The DeltaTime:
//    sf::Time elapsed = gameClock.restart();
//    int deltaTime = elapsed.asMilliseconds();

    if (loadingScene) loadScene(sceneToLoad, loadPositionFromFile);

    onOverridePreRender(window);

    if (currentScene.type != SCENE_MENU)
    {
        if (currentScene.playerEnabled)
            playerLoop();

        if (!currentScene.noView)
            window.setView(currentScene.view);
        if (currentScene.backgroundEnabled)
            window.draw(currentScene.backgroundSprite);

        if (currentScene.playerEnabled)
            window.draw(player.sprite);

        NPCsRenderLoop(window);

        if (!isGamePaused)
            interactionLoop(window);

        if (currentScene.foregroundEnabled)
            window.draw(currentScene.foregroundSprite);
    }

    onOverrideRender(window);

    if (DEBUG_MODE)
        renderDebug(window);

    window.setView(uiView);
    UILayer(window);

    framecount++;
    if (framecount >= REFRESH_RATE)
        framecount = 0;
}
