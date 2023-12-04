Scene initOptimusPrimeScene() {
    Scene scene;
    scene.type = SCENE_GAME;
    scene.location = SCENE_OPTIMUS;
    scene.name = "Optimus Prime";
    scene.backgroundSpritePath = BACKGROUND_OPTIMUS_PRIME_PATH;
    scene.defaultPlayerDir = PLAYER_SPRITE_RIGHT;
    scene.defaultPlayerPos = sf::Vector2f(1950, 1260);
    scene.view = sf::View(scene.defaultPlayerPos, sf::Vector2f(SCREEN_W/2, SCREEN_H/2));

    scene.colliderHitboxes[0] = sf::IntRect(1913, 1270, 1, 10);
    scene.colliderHitboxes[1] = sf::IntRect(1240, 1460, 30, 30);
    scene.colliderHitboxes[2] = sf::IntRect(1325, 1460, 30, 30);
    scene.colliderHitboxes[3] = sf::IntRect(1240, 1545, 30, 30);
    scene.colliderHitboxes[4] = sf::IntRect(1325, 1545, 30, 30);
    scene.colliderHitboxes[5] = sf::IntRect(1515, 1486, 30, 30);
    scene.colliderHitboxes[6] = sf::IntRect(1705, 1378, 30, 30);

    int nextNPCIndex = 1;

    scene.animatedSprites[0] = guideChar;
    scene.animatedSprites[0].position = sf::Vector2f(1900, 1260);

    InteractionPoint talkToGuideInteraction;
    talkToGuideInteraction.name = INTERACTION_TALK;
    talkToGuideInteraction.label = "Try to go back";
    talkToGuideInteraction.position = scene.animatedSprites[0].position;
    talkToGuideInteraction.dialog = noGoingBackDialog();
    talkToGuideInteraction.associatedNPC = scene.animatedSprites[0];

    scene.interactibles[0] = talkToGuideInteraction;


    if (!keysStore.rock) {
        scene.animatedSprites[nextNPCIndex] = rockChar;
        scene.animatedSprites[nextNPCIndex].position = sf::Vector2f(1300, 1477);

        InteractionPoint talkToRockInteraction;
        talkToRockInteraction.name = INTERACTION_TALK;
        talkToRockInteraction.label = "Talk";
        talkToRockInteraction.position = scene.animatedSprites[nextNPCIndex].position;
        talkToRockInteraction.dialog = rockDialog();
        talkToRockInteraction.associatedNPC = scene.animatedSprites[nextNPCIndex];

        scene.interactibles[nextNPCIndex] = talkToRockInteraction;
        nextNPCIndex++;
    }

    if (!keysStore.horse) {
        scene.animatedSprites[nextNPCIndex] = platformerChar;
        scene.animatedSprites[nextNPCIndex].position = sf::Vector2f(1500, 1677);

        InteractionPoint talkToHorseInteraction;
        talkToHorseInteraction.name = INTERACTION_TALK;
        talkToHorseInteraction.label = "Talk";
        talkToHorseInteraction.position = scene.animatedSprites[nextNPCIndex].position;
        talkToHorseInteraction.dialog = horseDialog();
        talkToHorseInteraction.associatedNPC = scene.animatedSprites[nextNPCIndex];

        scene.interactibles[nextNPCIndex] = talkToHorseInteraction;
        nextNPCIndex++;
    }


    if (keysStore.rock && keysStore.horse && !keysStore.cipher) {
        scene.animatedSprites[nextNPCIndex] = cipherChar;
        scene.animatedSprites[nextNPCIndex].position = sf::Vector2f(1100, 1477);

        InteractionPoint talkToCipherInteraction;
        talkToCipherInteraction.name = INTERACTION_TALK;
        talkToCipherInteraction.label = "Talk";
        talkToCipherInteraction.position = scene.animatedSprites[nextNPCIndex].position;
        talkToCipherInteraction.dialog = cipherDialog();
        talkToCipherInteraction.associatedNPC = scene.animatedSprites[nextNPCIndex];

        scene.interactibles[nextNPCIndex] = talkToCipherInteraction;
        nextNPCIndex++;
    }


    return scene;
}