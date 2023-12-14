/* MenuScene.cpp *
 * A non-game scene file. This will be the main menu of the game in production.
 * This scene disables the player movement, and has its methods for Event
 * handling and rendering. (Custom override methods must be defined properly in
 * the onOverrideEvent and onOverrideRender methods properly).
 *
 * */
SceneLocation lastSceneLocation;
sf::Vector2f lastPlayerPosition;

void onMenuNavigation(InputAction action, int value = 0) {
    switch (action) {
        case INPUT_NAVIGATE:
            // Incrementing an enum (Casting back and forth between int and enum MenuItem):
            // https://stackoverflow.com/a/3475181
            menuCurrentSelection = (MenuItem)((int)menuCurrentSelection + value);

            if ((int)menuCurrentSelection < 0) menuCurrentSelection = (MenuItem)(menuItemsLength - 1);
            else if ((int)menuCurrentSelection >= menuItemsLength) menuCurrentSelection = (MenuItem)(0);

            break;

        case INPUT_SELECT:
            switch (menuCurrentSelection) {
                case MENU_PLAY:
//                    loadScene(initDemoScene());
                    if (newGame)
                        loadScene(initIntroScene());
                    else
                        handleTravel(lastSceneLocation, true);
                    break;

                case MENU_ABOUT:
                    loadScene(initCreditsScene());
                    break;

                case MENU_QUIT:
                    exit(0);
                    break;

            }
            break;

    }
}

void onMenuRender(sf::RenderWindow& window) {
    menuBgPosition += MENU_BG_SCROLL_SPEED / 10;

    sf::Sprite menuBg(menuBgTexture);
    menuBg.setScale(SCREEN_H / (float)menuBgTexture.getSize().y, SCREEN_H / (float)menuBgTexture.getSize().y);
    menuBg.setPosition(-menuBgPosition, 0);

    sf::Sprite menuBgNext(menuBgTexture);
    menuBgNext.setScale(SCREEN_H / (float)menuBgTexture.getSize().y, SCREEN_H / (float)menuBgTexture.getSize().y);
    menuBgNext.setPosition((menuBgTexture.getSize().x * menuBg.getScale().x) - menuBgPosition, 0);

    if ((int)(menuBgNext.getGlobalBounds().left + menuBgNext.getGlobalBounds().width) < SCREEN_W)
        menuBgPosition -= menuBgNext.getGlobalBounds().width;

    window.draw(menuBg);
    window.draw(menuBgNext);

    sf::Text menuTitle("Realm Of Enigmas", UI_FONT_HEAD);
    menuTitle.setCharacterSize(UI_HEAD_1_SIZE);
    menuTitle.setPosition(40, 0);
    menuTitle.setFillColor(sf::Color(255, 255, 255));

    sf::Text menuItems[3];
    for (int i = 0; i < 3; i++) {
        menuItems[i].setString(menuItemNames[i]);
        if (newGame && menuItemNames[i] == "Play")
            menuItems[i].setString("New game");
        menuItems[i].setFont(UI_FONT_BODY);
        menuItems[i].setCharacterSize(UI_BODY_1_SIZE);
        menuItems[i].setPosition(40, 45 * (i + 2));
        menuItems[i].setFillColor(sf::Color::White);

        if (menuCurrentSelection == i) {
            sf::Text menuSelection;
            menuSelection.setString(">");
            menuSelection.setFont(UI_FONT_BODY);
            menuSelection.setCharacterSize(UI_BODY_1_SIZE);
            menuSelection.setPosition(10, 45 * (i + 2));
            menuSelection.setFillColor(sf::Color(0, 255, 0));

            menuItems[i].setFillColor(sf::Color(0, 255, 0));
            menuItems[i].setString(menuItems[i].getString() + " <");

            window.draw(dropShadow(menuSelection));
            window.draw(menuSelection);
        }

        window.draw(dropShadow(menuItems[i]));
        window.draw(menuItems[i]);
    }

    sf::Sprite menuBtnNavUpHint = newButtonSquare(sf::Vector2f(40, SCREEN_H - 50), true);
    menuBtnNavUpHint.setScale(3, 3);
    sf::Text menuBtnNavUpTx;
    menuBtnNavUpTx.setString("W");
    menuBtnNavUpTx.setFont(UI_FONT_BODY);
    menuBtnNavUpTx.setCharacterSize(UI_BODY_2_SIZE);
    menuBtnNavUpTx.setFillColor(sf::Color::White);
    menuBtnNavUpTx.setPosition(menuBtnNavUpHint.getPosition());
    menuBtnNavUpTx.setOrigin((-UI_BODY_2_SIZE) * 0.5, -UI_BODY_2_SIZE * 0.3);

    sf::Sprite menuBtnNavDownHint = newButtonSquare(sf::Vector2f(90, SCREEN_H - 50), true);
    menuBtnNavDownHint.setScale(3, 3);
    sf::Text menuBtnNavDownTx;
    menuBtnNavDownTx.setString("S");
    menuBtnNavDownTx.setFont(UI_FONT_BODY);
    menuBtnNavDownTx.setCharacterSize(UI_BODY_2_SIZE);
    menuBtnNavDownTx.setFillColor(sf::Color::White);
    menuBtnNavDownTx.setPosition(menuBtnNavDownHint.getPosition());
    menuBtnNavDownTx.setOrigin((-UI_BODY_2_SIZE) * 0.5, -UI_BODY_2_SIZE * 0.3);

    sf::Text menuBtnNavName("Move", UI_FONT_BODY);
    menuBtnNavName.setCharacterSize(UI_BODY_2_SIZE);
    menuBtnNavName.setFillColor(sf::Color::White);
    menuBtnNavName.setPosition(140, menuBtnNavUpHint.getPosition().y + 8);

    sf::Sprite menuBtnSelectHint = newButton(sf::Vector2f(240, SCREEN_H - 50), true);
    menuBtnSelectHint.setScale(3, 3);
    sf::Text menuBtnSelectTx("SPACE", UI_FONT_BODY);
    menuBtnSelectTx.setCharacterSize(UI_BODY_3_SIZE);
    menuBtnSelectTx.setFillColor(sf::Color::White);
    menuBtnSelectTx.setPosition(menuBtnSelectHint.getPosition());
    menuBtnSelectTx.setOrigin((-UI_BODY_3_SIZE) / 0.85, -UI_BODY_3_SIZE / 1.5);

    sf::Text menuBtnSelectName("Select", UI_FONT_BODY);
    menuBtnSelectName.setCharacterSize(UI_BODY_2_SIZE);
    menuBtnSelectName.setFillColor(sf::Color::White);
    menuBtnSelectName.setPosition(340, menuBtnSelectHint.getPosition().y + 8);


    if (framecount > (REFRESH_RATE / 2) && !isGamePaused)
    {
        // if half a second has passed, change the icon into a pressed button
        menuBtnSelectHint.setTextureRect(UI_SPR_BTN_PRESSED);
        menuBtnNavUpHint.setTextureRect(UI_SPR_BTN_SQUARE_PRESSED);
        menuBtnNavDownHint.setTextureRect(UI_SPR_BTN_SQUARE_PRESSED);

        // also move the text a little lower too
        menuBtnSelectTx.setPosition(menuBtnSelectTx.getPosition().x, menuBtnSelectTx.getPosition().y + 2);
        menuBtnNavUpTx.setPosition(menuBtnNavUpTx.getPosition().x, menuBtnNavUpTx.getPosition().y + 2);
        menuBtnNavDownTx.setPosition(menuBtnNavDownTx.getPosition().x, menuBtnNavDownTx.getPosition().y + 2);
    }

    window.draw(menuBtnNavUpHint);
    window.draw(menuBtnNavUpTx);
    window.draw(menuBtnNavDownHint);
    window.draw(menuBtnNavDownTx);
    window.draw(menuBtnNavName);
    window.draw(menuBtnSelectHint);
    window.draw(menuBtnSelectTx);
    window.draw(menuBtnSelectName);
    window.draw(dropShadow(menuTitle));
    window.draw(menuTitle);
}

Scene initMenuScene() {
    Scene scene;

    scene.name = "Main menu";
    scene.location = SCENE_MAIN_MENU;
    scene.type = SCENE_MENU;
    scene.backgroundSpritePath = BACKGROUND_TEST_PATH;
    scene.playerEnabled = false;
    scene.musicFilePath = MUSIC_MENU_PATH;

    menuCurrentSelection = MENU_PLAY;

    vigenereCipherCompleted = false;
    brailleCipherCompleted = false;
    puzzleCipherCompleted = false;

    if (!ReadSaveFile(keysStore.rock, keysStore.horse, keysStore.cipher, lastSceneLocation, guideIntroduced, lastPlayerPosition)) {
        newGame = true;
    }

    return scene;
}

