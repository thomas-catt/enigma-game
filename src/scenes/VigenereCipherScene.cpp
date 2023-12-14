//const std::string messageToDecipher = "Xqvlrv Embog";
const std::string messageToDecipher = "Hajdrn Welyu";

char vigenereCipherInput[255] = "";
char vigenereCipherAnswer[255] = "cipher nigga";
int vigenereCipherInputIndex = 0;

bool showVigenereError = false;
bool showVigenereSuccess = false;

bool vigenereTyping = false;

void onVigenereRender(sf::RenderWindow& window) {
    uiStatus = "Decipher: \"" + messageToDecipher + "\" - [Tab] Type answer";
    menuStatus = "[H] Hint - [Q] Exit\nDecipher the encrypted message \"" + messageToDecipher + "\" and press [Tab] to write your answer in the answer screen. Use the given hint if you are unsure.";

    if (vigenereTyping) {
        sf::RectangleShape darkenBg(sf::Vector2f(SCREEN_W, SCREEN_H));
        darkenBg.setPosition(0, 0);
        darkenBg.setFillColor(sf::Color(0, 0, 0, 100));

        sf::Text vigenereAnswerHeading("Enter your answer", UI_FONT_HEAD);
        vigenereAnswerHeading.setCharacterSize(UI_HEAD_2_SIZE);
        vigenereAnswerHeading.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, 100), sf::Vector2i(vigenereAnswerHeading.getGlobalBounds().width, vigenereAnswerHeading.getGlobalBounds().height), true));

        const int textBoxWidth = 300;
        const int textBoxHeight = 50;

        sf::Text vigenereAnswerBox(vigenereCipherInput, UI_FONT_BODY);
        vigenereAnswerBox.setCharacterSize(textBoxHeight / 1.5);
        vigenereAnswerBox.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, 250), sf::Vector2i(textBoxWidth, textBoxHeight), true));


        sf::RectangleShape vigenereAnswerRect(sf::Vector2f (textBoxWidth + 20, textBoxHeight + 10));
        vigenereAnswerRect.setPosition(vigenereAnswerBox.getPosition().x - 10, vigenereAnswerBox.getPosition().y - 5);
        vigenereAnswerRect.setFillColor(sf::Color::Black);

        if (vigenereAnswerBox.getGlobalBounds().left + vigenereAnswerBox.getGlobalBounds().width > vigenereAnswerRect.getGlobalBounds().left + vigenereAnswerRect.getGlobalBounds().width) {
            vigenereCipherInput[vigenereCipherInputIndex] = '\0';
            vigenereCipherInputIndex--;
        }


        sf::RectangleShape vigenereAnswerRectOutline(sf::Vector2f (vigenereAnswerRect.getSize().x + 10, vigenereAnswerRect.getSize().y + 10));
        vigenereAnswerRectOutline.setPosition(vigenereAnswerRect.getPosition().x - 5, vigenereAnswerRect.getPosition().y - 5);
        vigenereAnswerRectOutline.setFillColor(sf::Color::White);

        window.draw(darkenBg);

        if (showVigenereError) {
            sf::Text vigenereAnswerError("Incorrect answer!", UI_FONT_BODY);
            vigenereAnswerError.setCharacterSize(UI_BODY_2_SIZE);
            vigenereAnswerError.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, SCREEN_H - 250), sf::Vector2i(vigenereAnswerError.getGlobalBounds().width, vigenereAnswerError.getGlobalBounds().height), true));
            vigenereAnswerError.setFillColor(sf::Color::Red);

            window.draw(vigenereAnswerError);
        } else if (showVigenereSuccess) {
            sf::Text vigenereAnswerSuccess("Correct answer!", UI_FONT_BODY);
            vigenereAnswerSuccess.setCharacterSize(UI_BODY_1_SIZE);
            vigenereAnswerSuccess.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, SCREEN_H - 250), sf::Vector2i(vigenereAnswerSuccess.getGlobalBounds().width, vigenereAnswerSuccess.getGlobalBounds().height), true));
            vigenereAnswerSuccess.setFillColor(sf::Color::Green);

            window.draw(vigenereAnswerSuccess);
        }


        sf::Sprite vigenereBtnEnterHint = newButton(sf::Vector2f((SCREEN_W - textBoxWidth) / 2, SCREEN_H - 200));
        vigenereBtnEnterHint.setScale(3, 3);
        sf::Text vigenereBtnEnterTx("Enter", UI_FONT_BODY);
        vigenereBtnEnterTx.setCharacterSize(UI_BODY_3_SIZE);
        vigenereBtnEnterTx.setFillColor(sf::Color::White);
        vigenereBtnEnterTx.setPosition(vigenereBtnEnterHint.getPosition());
        vigenereBtnEnterTx.setOrigin((-UI_BODY_3_SIZE) / 0.75, -UI_BODY_3_SIZE / 1.5);
        sf::Text vigenereBtnEnterLabel("Submit answer", UI_FONT_BODY);
        vigenereBtnEnterLabel.setCharacterSize(UI_BODY_2_SIZE);
        vigenereBtnEnterLabel.setPosition(vigenereBtnEnterHint.getPosition().x + vigenereBtnEnterHint.getGlobalBounds().width + 5, vigenereBtnEnterHint.getPosition().y);


        sf::Sprite vigenereBtnTabHint = newButton(sf::Vector2f((SCREEN_W - textBoxWidth) / 2, SCREEN_H - 150));
        vigenereBtnTabHint.setScale(3, 3);
        sf::Text vigenereBtnTabTx("Tab", UI_FONT_BODY);
        vigenereBtnTabTx.setCharacterSize(UI_BODY_3_SIZE);
        vigenereBtnTabTx.setFillColor(sf::Color::White);
        vigenereBtnTabTx.setPosition(vigenereBtnTabHint.getPosition());
        vigenereBtnTabTx.setOrigin((-UI_BODY_3_SIZE) / 0.5, -UI_BODY_3_SIZE / 1.5);
        sf::Text vigenereBtnTabLabel("Close", UI_FONT_BODY);
        vigenereBtnTabLabel.setCharacterSize(UI_BODY_2_SIZE);
        vigenereBtnTabLabel.setPosition(vigenereBtnTabHint.getPosition().x + vigenereBtnTabHint.getGlobalBounds().width + 5, vigenereBtnTabHint.getPosition().y);


        if (framecount > (REFRESH_RATE / 2))
        {
            // if half a second has passed, change the icon into a pressed button
            vigenereBtnEnterHint.setTextureRect(UI_SPR_BTN_PRESSED);
            vigenereBtnTabHint.setTextureRect(UI_SPR_BTN_PRESSED);

            // also move the text a little lower too
            vigenereBtnEnterTx.setPosition(vigenereBtnEnterTx.getPosition().x, vigenereBtnEnterTx.getPosition().y + 2);
            vigenereBtnTabTx.setPosition(vigenereBtnTabTx.getPosition().x, vigenereBtnTabTx.getPosition().y + 2);
        }


        window.draw(vigenereAnswerHeading);
        window.draw(vigenereAnswerRectOutline);
        window.draw(vigenereAnswerRect);
        window.draw(vigenereAnswerBox);
        window.draw(vigenereBtnEnterHint);
        window.draw(vigenereBtnEnterLabel);
        window.draw(vigenereBtnEnterTx);
        window.draw(vigenereBtnTabHint);
        window.draw(vigenereBtnTabLabel);
        window.draw(vigenereBtnTabTx);
    }
}

void onVigenereEvent(sf::Event event) {
    if (vigenereTyping && event.type == sf::Event::KeyPressed) {
        char letterToType = event.key.code + 97;
        showVigenereError = false;
        showVigenereSuccess = false;

        if (event.key.code == sf::Keyboard::Backspace) {
            vigenereCipherInputIndex--;
            vigenereCipherInput[vigenereCipherInputIndex] = '\0';

            if (vigenereCipherInputIndex < 0)
                vigenereCipherInputIndex = 0;

        } else if (event.key.code == sf::Keyboard::Tab) {
            vigenereTyping = false;

        } else if (letterToType >= 'a' && letterToType <= 'z' || event.key.code == sf::Keyboard::Space) {
            if (letterToType >= 'a' && letterToType <= 'z')
                vigenereCipherInput[vigenereCipherInputIndex] = letterToType;
            else if (event.key.code == sf::Keyboard::Space)
                vigenereCipherInput[vigenereCipherInputIndex] = ' ';

            vigenereCipherInputIndex++;

        } else if (event.key.code == sf::Keyboard::Enter) {
            if (stringCompare(vigenereCipherInput, vigenereCipherAnswer))
                showVigenereSuccess = true;
            else
                showVigenereError = true;

            if (showVigenereSuccess) {
                // cipher solved

                vigenereCipherCompleted = true;
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
                createPopup("HINT", "\"Vigenere\".");
                break;

            case sf::Keyboard::Tab:
                vigenereTyping = true;
                break;
        }
    }
}

void onVigenereStart() {
    createPopup("Decipher the code", "You are provided with a ciphered text and your task is to decrypt the cipher. Think about various techniques and use the hint to figure out the answer.\n\nPress H for the hint. Press [Tab] whenever you are ready to input the answer.\n\nGood luck!");
}

Scene initVigenereCipherScene() {
    Scene scene;
    scene.name = "Vigenere Cipher";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_CIPHER_VIGENERE;
    scene.noView = true;
    scene.playerEnabled = false;
    scene.backgroundSpritePath = BACKGROUND_VIGENERE_PATH;
    scene.musicEnabled = false;

    return scene;
}