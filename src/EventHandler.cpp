/* EventHandler.cpp
 * This file controls all the Event handling of the program. Any SFML Event
 * handling is fundamentally broken down in this file.
 * */


/* The menuEventHandler function is called from the Override.cpp (visit
 * Override.cpp for explanation) when the MenuScene wants to receive event
 * handling calls. The onMenuNavigation is situated in MenuScene.cpp.
 *
 * */
void menuEventHandler(sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == KEY_NAV_UP || event.key.code == KEY_NAV_UP_ALT)
                onMenuNavigation(INPUT_NAVIGATE, -1);

            else if (event.key.code == KEY_NAV_DOWN || event.key.code == KEY_NAV_DOWN_ALT)
                onMenuNavigation(INPUT_NAVIGATE, 1);

            else if (event.key.code == KEY_NAV_SELECT || event.key.code == KEY_NAV_SELECT_ALT)
                onMenuNavigation(INPUT_SELECT);

            else if (event.key.code == KEY_NAV_BACK)
                onMenuNavigation(INPUT_BACK);

            break;
    }
}

void gameMenuEventHandler(sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            if (event.key.code == KEY_NAV_UP || event.key.code == KEY_NAV_UP_ALT)
                onGameMenuNavigation(INPUT_NAVIGATE, -1);

            else if (event.key.code == KEY_NAV_DOWN || event.key.code == KEY_NAV_DOWN_ALT)
                onGameMenuNavigation(INPUT_NAVIGATE, 1);

            else if (event.key.code == KEY_NAV_SELECT || event.key.code == KEY_NAV_SELECT_ALT)
                onGameMenuNavigation(INPUT_SELECT);

            else if (event.key.code == KEY_NAV_BACK)
                onGameMenuNavigation(INPUT_BACK);

            break;
    }
}



/* This small function is responsible for converting the keyboard direction
 * (from the EventHandler below) into a usable player movementVector.
 *
 * */
void onMovement(sf::Vector2f dir) {
    // Don't carry out movement when the game is paused
    if (isGamePaused) return;

    player.movementVector = dir;
    player.moving = true;
}


/* This function controls the global back function which occurs when the user
 * presses the Esc key.
 * */
void onEscape() {
    if (isPopupOpen || isImagePopupOpen) return hidePopup();
    if (currentScene.type == SCENE_MENU || currentScene.location == SCENE_END) return;
    isGamePaused = !isGamePaused;
    isDialogOpen = false;
    isPopupOpen = false;
    isImagePopupOpen = false;
    player.movementVector = sf::Vector2f(0, 0);
}

/* Finally, the EventHandler is the heart of all the event handling in the
 * entire game. All events are passed to this, and this function forks down the
 * call to the relevant handler (movement handler, interaction handler, menu
 * handler, etc.)
 *
 * */
void EventHandler(sf::Event event) {
    if (loadingScene) return;

    switch (event.type) {
    case sf::Event::KeyPressed:
        // std::cout << "key: " << event.key.code << std::endl;

        switch (event.key.code) {
            case KEY_UP: case KEY_UP_ALT:
                onMovement(sf::Vector2f(player.movementVector.x, -1.f * PLAYER_MOVE_MULTIPLIER));
                break;

            case KEY_DOWN: case KEY_DOWN_ALT:
                onMovement(sf::Vector2f(player.movementVector.x, 1.f * PLAYER_MOVE_MULTIPLIER));
                break;

            case KEY_LEFT: case KEY_LEFT_ALT:
                onMovement(sf::Vector2f(-1.f * PLAYER_MOVE_MULTIPLIER, player.movementVector.y));
                break;

            case KEY_RIGHT: case KEY_RIGHT_ALT:
                onMovement(sf::Vector2f(1.f * PLAYER_MOVE_MULTIPLIER, player.movementVector.y));
                break;

            case KEY_ACTION:
                handleInteraction(player.interactionInRange);
                break;

            case KEY_NEXT: case KEY_NEXT_ALT:
                if (isPopupOpen)
                    hidePopup();
                else
                    nextDialog();

                break;

            case KEY_NAV_BACK:
                onEscape();
                break;

        }

        break;

    case sf::Event::KeyReleased:
        
        if (event.key.code == KEY_UP || event.key.code == KEY_UP_ALT || event.key.code == KEY_DOWN || event.key.code == KEY_DOWN_ALT)
            onMovement(sf::Vector2f(player.movementVector.x, 0));
            
        else if (event.key.code == KEY_LEFT || event.key.code == KEY_LEFT_ALT || event.key.code == KEY_RIGHT || event.key.code == KEY_RIGHT_ALT)
            onMovement(sf::Vector2f(0, player.movementVector.y));
            
        break;

//    case sf::Event::MouseMoved:
//        std::cout << "mouse: x:" << event.mouseMove.x << " y:" << event.mouseMove.y << std::endl;

    default:
        break;
    }

    if (isGamePaused && !isDialogOpen) {
        gameMenuEventHandler(event);
    } else {
        /* This is overriding call which extends the EventHandler to any of the
         * scenes that may also require it.
         * */
        onOverrideEvent(event);
    }
}