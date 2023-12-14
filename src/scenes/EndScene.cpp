/* EndScreenTextScene.cpp
 * Contains the endScreen
 *
 * */


/* The first letter of each of these strings determine if the text will appear
 * as a heading or just as body text.
 *
 */

const char endScreenData[64][512] = {
        " ",
        "As Elias emerged from the otherworldly tunnel, a chilling realization gripped him. The air crackled with an otherworldly energy. Home wasn't as he left it. Shadows danced with arcane whispers. Had he merely opened a door or unraveled the very fabric of reality? The line between worlds blurred, leaving Elias to question the true extent of his journey.",
};

int currentEndScreenText = -1;
int endScreenSecondsPassed = END_SCREEN_TIME - 2;
bool endScreenCompleted = false;

void onEndScreenTextRender(sf::RenderWindow& window);

Scene initEndScreenTextScene(int lastEndScreenText = -1, int lastSecondsPassed = END_SCREEN_TIME - 2) {
    Scene scene;

    scene.name = "End screen Text";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_END;
    scene.playerEnabled = false;
    scene.backgroundEnabled = false;
    scene.musicFilePath = MUSIC_END_PATH;

    currentEndScreenText = lastEndScreenText;
    endScreenSecondsPassed = lastSecondsPassed;

    scene.musicEnabled = currentEndScreenText < 0;
    scene.musicLooping = false;

    endScreenCompleted = false;

    return scene;
}

void onEndScreenTextRender(sf::RenderWindow& window) {
    if (endScreenSecondsPassed == END_SCREEN_TIME && endScreenData[currentEndScreenText + 1][0] == '\0') {
        if (!endScreenCompleted) {
            loadScene(initCreditsScene());
            newGame = true;
            keysStore.cipher = false;
            keysStore.rock = false;
            keysStore.horse = false;
            saveGame();
        }
        endScreenCompleted = true;
    }
    sf::Text endScreenTx(endScreenData[currentEndScreenText], UI_FONT_BODY);
    endScreenTx.setCharacterSize(UI_BODY_3_SIZE);
    textWrapper(endScreenTx, SCREEN_W - 200);
    endScreenTx.setPosition(centerByDimensions(sf::Vector2f(100, SCREEN_H/2), sf::Vector2i(0, endScreenTx.getGlobalBounds().height), true));

    window.draw(endScreenTx);

    if (endScreenSecondsPassed >= END_SCREEN_TIME && !endScreenCompleted) {
        endScreenSecondsPassed = 0;
        loadScene(initEndScreenTextScene(currentEndScreenText, endScreenSecondsPassed));
    }

    if (!loadingScene) {
        if (framecount % REFRESH_RATE == 0)
            endScreenSecondsPassed++;
    } else if (sceneLoaded && loadingScene == 100) {
        // Screen has fully faded in
        currentEndScreenText++;
    }

}
