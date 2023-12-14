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
        "A plain path caught my eye...",
        "I ventured deeper...",
        "The path behind faded darker and darker....",
        "I was lost.",
        "But something. Someone... pulled me in further..."
};

int introSecondsPassed = INTRO_SCREEN_TIME - 1;

void onIntroRender(sf::RenderWindow& window);

Scene initIntroScene(int lastIntro = -1, int lastSecondsPassed = INTRO_SCREEN_TIME - 1) {
    Scene scene;

    scene.name = "Intro";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_INTRO;
    scene.playerEnabled = false;
    scene.backgroundEnabled = false;
    scene.musicFilePath = MUSIC_SELFTALK_PATH;

    currentIntro = lastIntro;
    introSecondsPassed = lastSecondsPassed;

    scene.musicEnabled = currentIntro < 1;

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
