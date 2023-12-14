/* SFML */
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

/* Native */
#include <iostream>
#include <math.h>
#include <fstream>

/* Header files */
#include "include/Constants.h"
#include "include/Globals.h"
#include "include/Assets.h"

/* Data loading files & General Helper */
#include "src/Dialog.cpp"
#include "src/Preload.cpp"
#include "src/Helper.cpp"

/* Scene files */
#include "src/scenes/DemoScene.cpp"
#include "src/scenes/OverworldScene.cpp"
#include "src/scenes/IntroScene.cpp"
#include "src/scenes/CreditsScene.cpp"
#include "src/scenes/EndScene.cpp"
#include "src/scenes/MenuScene.cpp"
#include "src/scenes/SnakeScene.cpp"
#include "src/scenes/RockScene.cpp"
#include "src/scenes/OptimusPrimeScene.cpp"
#include "src/scenes/PlatformerScene.cpp"
#include "src/scenes/CipherScene.cpp"
#include "src/scenes/PuzzleCipherScene.cpp"
#include "src/scenes/VigenereCipherScene.cpp"
#include "src/scenes/BrailleCipherScene.cpp"

/* Source files */
#include "src/UI.cpp"
#include "src/Audio.cpp"
#include "src/SceneInit.cpp"
#include "src/Physics.cpp"
#include "src/Game.cpp"
#include "src/Render.cpp"
#include "src/EventHandler.cpp"
#include "src/Override.cpp"

int main() {
    srand(time(0));

    // Code starts off here, setting up the window:

    sf::RenderWindow window(sf::VideoMode(SCREEN_W, SCREEN_H), WINDOW_TITLE);
    window.setFramerateLimit(REFRESH_RATE);

    uiView = sf::View(sf::Vector2f(SCREEN_W/2, SCREEN_H/2), sf::Vector2f(SCREEN_W, SCREEN_H));
    defaultView = sf::View(sf::Vector2f(SCREEN_W/2, SCREEN_H/2), sf::Vector2f(SCREEN_W, SCREEN_H));

    // Preloading the fonts and UI spritesheet:
    loadAssets();

    // Loading the first scene, the MenuScene.cpp: (initMenuScene is defined in
    // MenuScene.cpp)

    loadScene(initMenuScene());

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // All events go straight to the EventHandler in the
            // EventHandler.cpp file. The event handling is forked down to
            // various levels in that file.
            EventHandler(event);

            if (event.type == sf::Event::Closed)
                window.close();
        }

        // This PhysicsLoop (Physics.cpp) ensures the player is not inside of any
        // hitboxes before any rendering occurs.
        PhysicsLoop();

        // Finally, when everything is set, the Render (Render.cpp) renders all
        // the relevant stuff onto the screen. (This also manages other stuff
        // that may occur while rendering.
        Render(window);
        window.display();
    }

    return 0;
}