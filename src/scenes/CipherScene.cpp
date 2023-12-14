int completedCiphers;
void onCipherSceneCreate() {
    completedCiphers = (int)puzzleCipherCompleted + (int)vigenereCipherCompleted + (int)brailleCipherCompleted;
    menuStatus = "Complete all ciphers here to obtain the key.\n\nCiphers completed: " + std::to_string(completedCiphers)+ "/3";

    switch (completedCiphers) {
        case 0:
            createPopup("Complete all ciphers", "Complete all ciphers in this area to obtain the final key.");
            break;
        case 1:
            createPopup("Complete all ciphers", "Great, you have completed one cipher and obtained the key.");
            break;
        case 2:
            createPopup("Complete all ciphers", "You have completed two ciphers, only one remaining now.");
            break;
        case 3:
            createPopup("Congratulations", "You have completed all the ciphers. Now find your way out.");
            menuStatus = "Find your way out.";
            break;
    }

//    if (puzzleCipherCompleted && vigenereCipherCompleted) {
//    }
}

Scene initCipherScene() {
    Scene scene;
    completedCiphers = (int)puzzleCipherCompleted + (int)vigenereCipherCompleted + (int)brailleCipherCompleted;

    scene.name = "Cipher Scene";
    scene.type = SCENE_GAME;
    scene.location = SCENE_CIPHER_GAME;
    scene.backgroundSpritePath = BACKGROUND_CIPHER_PATH;
    if (completedCiphers == 3)
        scene.backgroundSpritePath = BACKGROUND_CIPHER_COMPLETE_PATH;
    scene.foregroundEnabled = true;
    scene.foregroundSpritePath = FOREGROUND_CIPHER_PATH;
    scene.musicFilePath = MUSIC_MAZE_PATH;
    if (completedCiphers > 0)
        scene.musicEnabled = false;

    scene.defaultPlayerPos = sf::Vector2f(100, 100);
    scene.defaultPlayerDir = PLAYER_SPRITE_RIGHT;
    scene.view = sf::View(sf::FloatRect(scene.defaultPlayerPos.x, scene.defaultPlayerPos.y, 400, 300));
//    scene.playerSpeedMultiplier = 3;

    scene.colliderHitboxes[0] = sf::IntRect(0, 0, SCREEN_W, 80);
    scene.colliderHitboxes[1] = sf::IntRect(0, 0, 60, 250);
    scene.colliderHitboxes[2] = sf::IntRect(0, 200, 140, 90);
    scene.colliderHitboxes[3] = sf::IntRect(80, 200, 60, 120);
    scene.colliderHitboxes[4] = sf::IntRect(235, 200, 240, 140);
    scene.colliderHitboxes[5] = sf::IntRect(0, 0, 30, SCREEN_H);
    scene.colliderHitboxes[6] = sf::IntRect(30, 420, 30, SCREEN_H);
    scene.colliderHitboxes[7] = sf::IntRect(30, 420, 110, 140);
    scene.colliderHitboxes[8] = sf::IntRect(230, 420, 255, 140);
    scene.colliderHitboxes[9] = sf::IntRect(314, 23, 83, 300);
    scene.colliderHitboxes[10] = sf::IntRect(27, 665, SCREEN_W, 100);
    scene.colliderHitboxes[11] = sf::IntRect(314, 423, 83, 300);
    scene.colliderHitboxes[12] = sf::IntRect(567, 203, 137, 132);
    scene.colliderHitboxes[13] = sf::IntRect(648, 12, 100, 200);
    scene.colliderHitboxes[14] = sf::IntRect(570, 424, 51, 70);
    scene.colliderHitboxes[15] = sf::IntRect(570, 450, 146, 100);
    scene.colliderHitboxes[16] = sf::IntRect(674, 278, 100, 200);
    scene.colliderHitboxes[17] = sf::IntRect(650, 500, 100, 200);

    scene.colliderHitboxes[18] = sf::IntRect(291, 113, 13, 50);
    scene.colliderHitboxes[19] = sf::IntRect(68, 383, 18, 40);
    scene.colliderHitboxes[20] = sf::IntRect(40, 410, 40, 14);
    scene.colliderHitboxes[21] = sf::IntRect(232, 337, 46, 16);
    scene.colliderHitboxes[22] = sf::IntRect(422, 344, 50, 17);
    scene.colliderHitboxes[23] = sf::IntRect(628, 344, 40, 17);
    scene.colliderHitboxes[24] = sf::IntRect(59, 567, 32, 56);
    scene.colliderHitboxes[25] = sf::IntRect(402, 610, 10, 28);
    scene.colliderHitboxes[26] = sf::IntRect(402, 570, 30, 10);
    scene.colliderHitboxes[27] = sf::IntRect(143, 546, 85, 9);
    scene.colliderHitboxes[28] = sf::IntRect(488, 546, 82, 9);

    InteractionPoint goBackInteraction;
    goBackInteraction.position = sf::Vector2f(638, 427);
    goBackInteraction.label = "Downstairs...?";
    goBackInteraction.dialog = playerCipherGoBackDialog();
    goBackInteraction.name = INTERACTION_TALK;
    scene.interactibles[0] = goBackInteraction;

    int currentNPCIndex = 1;

    if (!puzzleCipherCompleted){
        InteractionPoint puzzleCipherInteraction;
        puzzleCipherInteraction.position = sf::Vector2f(340.f, 320.f);
        puzzleCipherInteraction.name = INTERACTION_TRAVEL;
        puzzleCipherInteraction.label = "Enter puzzle";
        puzzleCipherInteraction.travelTo = SCENE_CIPHER_PUZZLE;
        scene.interactibles[currentNPCIndex] = puzzleCipherInteraction;
        currentNPCIndex++;
    }


    if (!brailleCipherCompleted){
        InteractionPoint vigenereCipherInteraction;
        vigenereCipherInteraction.position = sf::Vector2f(512.f, 71.924);
        vigenereCipherInteraction.name = INTERACTION_TRAVEL;
        vigenereCipherInteraction.label = "Enter puzzle";
        vigenereCipherInteraction.travelTo = SCENE_CIPHER_BRAILLE;
        scene.interactibles[currentNPCIndex] = vigenereCipherInteraction;
        currentNPCIndex++;
    }


    if (!vigenereCipherCompleted){
        InteractionPoint brailleCipherInteraction;
        brailleCipherInteraction.position = sf::Vector2f(165.f, 71.924);
        brailleCipherInteraction.name = INTERACTION_TRAVEL;
        brailleCipherInteraction.label = "Enter puzzle";
        brailleCipherInteraction.travelTo = SCENE_CIPHER_VIGENERE;
        scene.interactibles[currentNPCIndex] = brailleCipherInteraction;
        currentNPCIndex++;
    }


    return scene;
 }

