/* CreditsScene.cpp
 * Contains the credits
 *
 * */


/* The first letter of each of these strings determine if the text will appear
 * as a heading or just as body text.
 *
 */

const char creditsData[64][256] = {
    "#CREDITS",
    "#",
    "#Realm Of Enigmas",
    "A top-down platformer game presented by:",
    "#",
    "23L-2555 Armaghan Ahmed",
    "23L-3001 Arham Khurram",
    "23L-3066 M. Ibrahim",
    "23L-3065 Jabeen Zahra",
    "23L-XXXX Amar Waqar",
    "#",
    "#Technologies",
    "Coded with <3 in C++.",
    "Made possible with the SFML Graphics library.",
    "#",
};

int totalCreditsHeight;

void onCreditsRender(sf::RenderWindow& window) {
    int currentWidgetPosition = 0;
    for (int i = 0; creditsData[i][0] != '\0'; i++) {
            sf::Font creditsFont;
            int fontSize;
            char textToWrite[256];
            if (creditsData[i][0] == '#') {
                creditsFont = UI_FONT_HEAD;
                fontSize = UI_HEAD_1_SIZE;

            }
            else {
                creditsFont = UI_FONT_BODY;
                fontSize = UI_BODY_2_SIZE;
            }

            // Empty space:
            if (creditsData[i][1] == '\0') {
                currentWidgetPosition += 40;
                continue;
            }


            int j;
            for (j = (creditsData[i][0] == '#'); creditsData[i][j] != '\0'; j++) {
                textToWrite[j - (creditsData[i][0] == '#')] = creditsData[i][j];
            }
            textToWrite[j - (creditsData[i][0] == '#')] = '\0';


            sf::Text creditsTx(textToWrite, creditsFont);
            creditsTx.setCharacterSize(fontSize);
            creditsTx.setPosition(centerByDimensions(sf::Vector2f(SCREEN_W/2, totalCreditsHeight + currentWidgetPosition), sf::Vector2i(creditsTx.getGlobalBounds().width, creditsTx.getGlobalBounds().height), true));

            window.draw(creditsTx);

            if (creditsData[i][0] == '#') {
                currentWidgetPosition += 100;
            }
            else {
                currentWidgetPosition += 30;
            }
    }

    if (!isGamePaused) totalCreditsHeight--;

    if (totalCreditsHeight + currentWidgetPosition < 0)
        loadScene(initMenuScene());
}

Scene initCreditsScene() {
    Scene scene;

    scene.name = "Credits";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_CREDITS;
    scene.playerEnabled = false;
    scene.backgroundEnabled = false;
    scene.musicFilePath = MUSIC_CREDITS_PATH;
    scene.musicEnabled = !(keysStore.cipher && keysStore.horse && keysStore.rock);

    totalCreditsHeight = SCREEN_H;

    return scene;
}