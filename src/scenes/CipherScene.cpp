void onCipherSceneCreate() {
    if (puzzleCipherCompleted) {
        miniGameVictory(MINIGAME_CIPHER, keysStore.cipher);
    }
}

Scene initCipherScene() {
    Scene scene;

    scene.name = "Cipher Scene";
    scene.type = SCENE_GAME;
    scene.location = SCENE_CIPHER_GAME;
    scene.backgroundSpritePath = BACKGROUND_CIPHER_PATH;
    scene.defaultPlayerPos = sf::Vector2f(100, 100);
    scene.defaultPlayerDir = PLAYER_SPRITE_RIGHT;
    scene.view = sf::View(sf::FloatRect(scene.defaultPlayerPos.x, scene.defaultPlayerPos.y, 400, 300));
//    scene.playerSpeedMultiplier = 3;

    scene.colliderHitboxes[0] = sf::IntRect(0, 0, SCREEN_W, 80);
    scene.colliderHitboxes[1] = sf::IntRect(0, 0, 60, 250);
    scene.colliderHitboxes[2] = sf::IntRect(0, 200, 140, 90);
    scene.colliderHitboxes[3] = sf::IntRect(80, 200, 60, 110);
    scene.colliderHitboxes[4] = sf::IntRect(235, 200, 240, 140);
    scene.colliderHitboxes[5] = sf::IntRect(0, 0, 30, SCREEN_H);
    scene.colliderHitboxes[6] = sf::IntRect(30, 420, 30, SCREEN_H);
    scene.colliderHitboxes[7] = sf::IntRect(30, 420, 110, 140);
    scene.colliderHitboxes[8] = sf::IntRect(235, 420, 240, 140);
    scene.colliderHitboxes[9] = sf::IntRect(314, 23, 83, 300);
    scene.colliderHitboxes[10] = sf::IntRect(27, 665, SCREEN_W, 100);
    scene.colliderHitboxes[11] = sf::IntRect(314, 423, 83, 300);
    scene.colliderHitboxes[12] = sf::IntRect(567, 203, 137, 132);
    scene.colliderHitboxes[13] = sf::IntRect(648, 12, 100, 200);
    scene.colliderHitboxes[14] = sf::IntRect(566, 424, 45, 70);
    scene.colliderHitboxes[15] = sf::IntRect(566, 450, 150, 100);
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

    int currentNPCIndex = 0;

    if (!puzzleCipherCompleted){
        scene.animatedSprites[currentNPCIndex] = puzzleCipherChar;
        scene.animatedSprites[currentNPCIndex].position = sf::Vector2f(190.f, 71.924);

        InteractionPoint puzzleCipherInteraction;
        puzzleCipherInteraction.position = scene.animatedSprites[currentNPCIndex].position;
        puzzleCipherInteraction.associatedNPC = scene.animatedSprites[currentNPCIndex];
        puzzleCipherInteraction.name = INTERACTION_TRAVEL;
        puzzleCipherInteraction.label = "Puzzle";
        puzzleCipherInteraction.travelTo = SCENE_CIPHER_PUZZLE;
        scene.interactibles[currentNPCIndex] = puzzleCipherInteraction;
        currentNPCIndex++;
    }


    if (!vigenereCipherCompleted){
        scene.animatedSprites[currentNPCIndex] = puzzleCipherChar;
        scene.animatedSprites[currentNPCIndex].position = sf::Vector2f(590.f, 71.924);

        InteractionPoint vigenereCipherInteraction;
        vigenereCipherInteraction.position = scene.animatedSprites[currentNPCIndex].position;
        vigenereCipherInteraction.associatedNPC = scene.animatedSprites[currentNPCIndex];
        vigenereCipherInteraction.name = INTERACTION_TRAVEL;
        vigenereCipherInteraction.label = "Vigenere";
        vigenereCipherInteraction.travelTo = SCENE_CIPHER_PUZZLE;
        scene.interactibles[currentNPCIndex] = vigenereCipherInteraction;
        currentNPCIndex++;
    }


    return scene;
 }

