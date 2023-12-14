char brailleCipherInput[255] = "";
char brailleCipherAnswer[255] = "we ran out of ideas so fuck it, cipher nigga 2";
int brailleCipherInputIndex = 0;

bool showBrailleError = false;
bool showBrailleSuccess = false;

bool brailleTyping = false;

void onBrailleRender(sf::RenderWindow& window) {
    uiStatus = "Solve the puzzle - [H] Hint - [Tab] Type answer";
    menuStatus = "[H] Hint - [Q] Exit\nDecipher the encrypted message \"" + messageToDecipher + "\" and press [Tab] to write your answer in the answer screen. Use the given hint if you are unsure.";

    if (brailleTyping) {
        sf::RectangleShape darkenBg(sf::Vector2f(SCREEN_W, SCREEN_H));
        darkenBg.setPosition(0, 0);
        darkenBg.setFillColor(sf::Color(0, 0, 0, 100));

        sf::Text brailleAnswerHeading("Enter your answer", UI_FONT_HEAD);
        brailleAnswerHeading.setCharacterSize(UI_HEAD_2_SIZE);
        brailleAnswerHeading.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, 100), sf::Vector2i(brailleAnswerHeading.getGlobalBounds().width, brailleAnswerHeading.getGlobalBounds().height), true));

        const int textBoxWidth = 600;
        const int textBoxHeight = 30;

        sf::Text brailleAnswerBox(brailleCipherInput, UI_FONT_BODY);
        brailleAnswerBox.setCharacterSize(textBoxHeight / 1.5);
        brailleAnswerBox.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, 250), sf::Vector2i(textBoxWidth, textBoxHeight), true));


        sf::RectangleShape brailleAnswerRect(sf::Vector2f (textBoxWidth + 20, textBoxHeight + 10));
        brailleAnswerRect.setPosition(brailleAnswerBox.getPosition().x - 10, brailleAnswerBox.getPosition().y - 5);
        brailleAnswerRect.setFillColor(sf::Color::Black);

        if (brailleAnswerBox.getGlobalBounds().left + brailleAnswerBox.getGlobalBounds().width > brailleAnswerRect.getGlobalBounds().left + brailleAnswerRect.getGlobalBounds().width) {
            brailleCipherInput[brailleCipherInputIndex] = '\0';
            brailleCipherInputIndex--;
        }


        sf::RectangleShape brailleAnswerRectOutline(sf::Vector2f (brailleAnswerRect.getSize().x + 10, brailleAnswerRect.getSize().y + 10));
        brailleAnswerRectOutline.setPosition(brailleAnswerRect.getPosition().x - 5, brailleAnswerRect.getPosition().y - 5);
        brailleAnswerRectOutline.setFillColor(sf::Color::White);

        window.draw(darkenBg);

        if (showBrailleError) {
            sf::Text brailleAnswerError("Incorrect answer!", UI_FONT_BODY);
            brailleAnswerError.setCharacterSize(UI_BODY_2_SIZE);
            brailleAnswerError.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, SCREEN_H - 250), sf::Vector2i(brailleAnswerError.getGlobalBounds().width, brailleAnswerError.getGlobalBounds().height), true));
            brailleAnswerError.setFillColor(sf::Color::Red);

            window.draw(brailleAnswerError);
        } else if (showBrailleSuccess) {
            sf::Text brailleAnswerSuccess("Correct answer!", UI_FONT_BODY);
            brailleAnswerSuccess.setCharacterSize(UI_BODY_1_SIZE);
            brailleAnswerSuccess.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, SCREEN_H - 250), sf::Vector2i(brailleAnswerSuccess.getGlobalBounds().width, brailleAnswerSuccess.getGlobalBounds().height), true));
            brailleAnswerSuccess.setFillColor(sf::Color::Green);

            window.draw(brailleAnswerSuccess);
        }


        sf::Sprite brailleBtnEnterHint = newButton(sf::Vector2f((SCREEN_W - textBoxWidth) / 2, SCREEN_H - 200));
        brailleBtnEnterHint.setScale(3, 3);
        sf::Text brailleBtnEnterTx("Enter", UI_FONT_BODY);
        brailleBtnEnterTx.setCharacterSize(UI_BODY_3_SIZE);
        brailleBtnEnterTx.setFillColor(sf::Color::White);
        brailleBtnEnterTx.setPosition(brailleBtnEnterHint.getPosition());
        brailleBtnEnterTx.setOrigin((-UI_BODY_3_SIZE) / 0.75, -UI_BODY_3_SIZE / 1.5);
        sf::Text brailleBtnEnterLabel("Submit answer", UI_FONT_BODY);
        brailleBtnEnterLabel.setCharacterSize(UI_BODY_2_SIZE);
        brailleBtnEnterLabel.setPosition(brailleBtnEnterHint.getPosition().x + brailleBtnEnterHint.getGlobalBounds().width + 5, brailleBtnEnterHint.getPosition().y);


        sf::Sprite brailleBtnTabHint = newButton(sf::Vector2f((SCREEN_W - textBoxWidth) / 2, SCREEN_H - 150));
        brailleBtnTabHint.setScale(3, 3);
        sf::Text brailleBtnTabTx("Tab", UI_FONT_BODY);
        brailleBtnTabTx.setCharacterSize(UI_BODY_3_SIZE);
        brailleBtnTabTx.setFillColor(sf::Color::White);
        brailleBtnTabTx.setPosition(brailleBtnTabHint.getPosition());
        brailleBtnTabTx.setOrigin((-UI_BODY_3_SIZE) / 0.5, -UI_BODY_3_SIZE / 1.5);
        sf::Text brailleBtnTabLabel("Close", UI_FONT_BODY);
        brailleBtnTabLabel.setCharacterSize(UI_BODY_2_SIZE);
        brailleBtnTabLabel.setPosition(brailleBtnTabHint.getPosition().x + brailleBtnTabHint.getGlobalBounds().width + 5, brailleBtnTabHint.getPosition().y);


        if (framecount > (REFRESH_RATE / 2))
        {
            // if half a second has passed, change the icon into a pressed button
            brailleBtnEnterHint.setTextureRect(UI_SPR_BTN_PRESSED);
            brailleBtnTabHint.setTextureRect(UI_SPR_BTN_PRESSED);

            // also move the text a little lower too
            brailleBtnEnterTx.setPosition(brailleBtnEnterTx.getPosition().x, brailleBtnEnterTx.getPosition().y + 2);
            brailleBtnTabTx.setPosition(brailleBtnTabTx.getPosition().x, brailleBtnTabTx.getPosition().y + 2);
        }


        window.draw(brailleAnswerHeading);
        window.draw(brailleAnswerRectOutline);
        window.draw(brailleAnswerRect);
        window.draw(brailleAnswerBox);
        window.draw(brailleBtnEnterHint);
        window.draw(brailleBtnEnterLabel);
        window.draw(brailleBtnEnterTx);
        window.draw(brailleBtnTabHint);
        window.draw(brailleBtnTabLabel);
        window.draw(brailleBtnTabTx);
    }
}

void onBrailleEvent(sf::Event event) {
    if (brailleTyping && event.type == sf::Event::KeyPressed) {
        char letterToType = event.key.code + 97;
        showBrailleError = false;
        showBrailleSuccess = false;

        if (event.key.code == sf::Keyboard::Backspace) {
            brailleCipherInputIndex--;
            brailleCipherInput[brailleCipherInputIndex] = '\0';

            if (brailleCipherInputIndex < 0)
                brailleCipherInputIndex = 0;

        } else if (event.key.code == sf::Keyboard::Tab) {
            brailleTyping = false;

        } else if (letterToType >= 'a' && letterToType <= 'z' || event.key.code <= sf::Keyboard::Num9 && event.key.code >= sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Space || event.key.code == sf::Keyboard::Comma) {
            if (letterToType >= 'a' && letterToType <= 'z')
                brailleCipherInput[brailleCipherInputIndex] = letterToType;
            else if (event.key.code <= sf::Keyboard::Num9 && event.key.code >= sf::Keyboard::Num0)
                brailleCipherInput[brailleCipherInputIndex] = char(event.key.code + 22);
            else if (event.key.code == sf::Keyboard::Space)
                brailleCipherInput[brailleCipherInputIndex] = ' ';
            else if (event.key.code == sf::Keyboard::Comma)
                brailleCipherInput[brailleCipherInputIndex] = ',';

            brailleCipherInputIndex++;

        } else if (event.key.code == sf::Keyboard::Enter) {
            if (stringCompare(brailleCipherInput, brailleCipherAnswer))
                showBrailleSuccess = true;
            else
                showBrailleError = true;

            if (showBrailleSuccess) {
                // cipher solved

                brailleCipherCompleted = true;
                loadScene(initCipherScene(), true);
            }
        } else {
            std::cout << letterToType << event.key.code <<  std::endl;
        }


    } else if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Q:
                loadScene(initCipherScene(), true);
                break;

            case sf::Keyboard::H:
                createImagePopup("assets/imgs/braille.jpg");
                break;

            case sf::Keyboard::Tab:
                brailleTyping = true;
                break;
        }
    }
}

void onBrailleStart() {
    createPopup("Decipher the image", "You are presented with a unique pattern. Think about various techniques and use the hint to decrypt the image and find the answer.\n\nPress H for the hint. Press [Tab] whenever you are ready to input the answer.\n\nGood luck!");
}

Scene initBrailleCipherScene() {
    Scene scene;
    scene.name = "Braille Cipher";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_CIPHER_BRAILLE;
    scene.noView = true;
    scene.playerEnabled = false;
    scene.backgroundSpritePath = BACKGROUND_BRAILLE_PATH;
    scene.musicEnabled = false;

    return scene;
}