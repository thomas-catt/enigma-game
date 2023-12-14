/* Override.cpp *
 * This file has functions that override the default Render() and EventHandler()
 * for any custom scene that would need access to these functions.
 *
 * */

void onOverrideEvent(sf::Event event) {
    switch (currentScene.location) {
        /* Each of these cases will detect which specific scene is running
         * currently, and passes the event handling to a function for that
         * scene.
         * */

        case SCENE_MAIN_MENU:
            menuEventHandler(event);
            break;

        case SCENE_CIPHER_PUZZLE:
            handlePuzzleCipherEvent(event);
            break;

        case SCENE_PLATFORMER_GAME:
            onPlatformerEvent(event);
            break;

        case SCENE_CIPHER_VIGENERE:
            onVigenereEvent(event);
            break;

        case SCENE_CIPHER_BRAILLE:
            onBrailleEvent(event);
            break;

        /* An example would be:

        case SCENE_OVERWORLD:
            testSceneEvent(event);
            break;
         */
    }
}

void onOverridePreRender(sf::RenderWindow& window) {
    switch (currentScene.location) {
        case SCENE_PLATFORMER_GAME:
            onPlatformerPreRender(window);
            break;
    }
}

void onOverrideRender(sf::RenderWindow& window) {
    switch (currentScene.location) {
        /* Each of these cases will detect which specific scene is running
         * currently, and passes the render handling to a function for that
         * scene.
         * */

        case SCENE_MAIN_MENU:
            onMenuRender(window);
            break;

        case SCENE_CREDITS:
            onCreditsRender(window);
            break;

        case SCENE_INTRO:
            onIntroRender(window);
            break;

        case SCENE_END:
            onEndScreenTextRender(window);
            break;

        case SCENE_ROCK_GAME:
            RockSceneRender(window);
            break;

        case SCENE_CIPHER_PUZZLE:
            puzzleCipherRender(window);
            break;

        case SCENE_PLATFORMER_GAME:
            onPlatformerRender(window);
            break;

        case SCENE_CIPHER_VIGENERE:
            onVigenereRender(window);
            break;

        case SCENE_CIPHER_BRAILLE:
            onBrailleRender(window);
            break;

        /* An example would be:

        case SCENE_OVERWORLD:
            onTestRender(window);
            break;
        */
    }
}