/* IntroScene.cpp
 * Contains the intro
 *
 * */


/* The first letter of each of these strings determine if the text will appear
 * as a heading or just as body text.
 *
 */

const char introData[64][256] = {
        " ",
        "I was just loitering about around the jungle until...",
        "I saw this intriguing yet visually uninteresting path.",
        "I walked into it, and walked...",
        "Until I realized there's no going back.",
        "I was lost.",
        "But I went further..."
};

int currentIntro = -1;
int introSecondsPassed = INTRO_SCREEN_TIME - 1;
bool introCompleted = false;

void onIntroRender(sf::RenderWindow& window);

Scene initIntroScene(int lastIntro = -1, int lastSecondsPassed = INTRO_SCREEN_TIME - 1) {
    Scene scene;

    scene.name = "Intro";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_INTRO;
    scene.playerEnabled = false;
    scene.backgroundEnabled = false;
    currentIntro = lastIntro;
    introSecondsPassed = lastSecondsPassed;

    introCompleted = false;

    return scene;
}

void onIntroRender(sf::RenderWindow& window) {
    if (introSecondsPassed == INTRO_SCREEN_TIME && introData[currentIntro + 1][0] == '\0') {
        if (!introCompleted) {
            loadScene(initTestScene());

            if (newGame) {
                newGame = false;
//                saveGame();
            }
        }
        introCompleted = true;
    }
    sf::Text introTx(introData[currentIntro], UI_FONT_BODY);
    introTx.setCharacterSize(UI_BODY_3_SIZE);
    introTx.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, SCREEN_H/2), sf::Vector2i(introTx.getGlobalBounds().width, introTx.getGlobalBounds().height), true));

    window.draw(introTx);

    if (introSecondsPassed >= INTRO_SCREEN_TIME && !introCompleted) {
        introSecondsPassed = 0;
        loadScene(initIntroScene(currentIntro, introSecondsPassed));
    }

    if (!loadingScene) {
        if (framecount % REFRESH_RATE == 0 && !isGamePaused)
            introSecondsPassed++;
    } else if (sceneLoaded && loadingScene == 100) {
        // Screen has fully faded in
        currentIntro++;
    }

}
