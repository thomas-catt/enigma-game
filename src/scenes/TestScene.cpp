Scene initTestScene()
{
    Scene scene;

    scene.name = "Test scene";
    scene.type = SCENE_GAME;
    scene.location = SCENE_TEST_SCENE;
    scene.backgroundSpritePath = BACKGROUND_TEST_PATH;
    scene.defaultPlayerPos = sf::Vector2f(600, 600);
    scene.defaultPlayerDir = PLAYER_SPRITE_DOWN;

    scene.view = sf::View(scene.defaultPlayerPos, sf::Vector2f(400.f, 300.f));

//    scene.animatedSprites[0] = guideChar;
//    scene.animatedSprites[0].position = sf::Vector2f(580, 200);

    scene.colliderHitboxes[0] = sf::IntRect(0, 446, 600, 160);
    scene.colliderHitboxes[1] = sf::IntRect(0, 114, 96, 38);
    scene.colliderHitboxes[2] = sf::IntRect(513, 104, 71, 182);
    scene.colliderHitboxes[3] = sf::IntRect(655, 106, 79, 183);
    scene.colliderHitboxes[4] = sf::IntRect(655, 106, 79, 183);
    scene.colliderHitboxes[5] = sf::IntRect(409, 294, 166, 77);
    scene.colliderHitboxes[6] = sf::IntRect(666, 403, 93, 124);
    scene.colliderHitboxes[7] = sf::IntRect(274, 4435, 321, 177);
    scene.colliderHitboxes[8] = sf::IntRect(642, 446, 446, 160);
    scene.colliderHitboxes[9] = sf::IntRect(0, 291, 233, 287);
    scene.colliderHitboxes[10] = sf::IntRect(178, 350, 142, 187);


    InteractionPoint changeSceneInteraction;
    changeSceneInteraction.name = INTERACTION_TALK;
    changeSceneInteraction.label = "A mysterious cave";
    changeSceneInteraction.dialog = playerBeforeCave();
    changeSceneInteraction.position = sf::Vector2f(590, 100);

    scene.interactibles[0] = changeSceneInteraction;
//
//    InteractionPoint talkToGuideInteraction;
//    talkToGuideInteraction.name = INTERACTION_TALK;
//    talkToGuideInteraction.label = "Talk to stranger";
//    talkToGuideInteraction.position = scene.animatedSprites[0].position;
//    talkToGuideInteraction.dialog = guideIntro();
//    talkToGuideInteraction.associatedNPC = scene.animatedSprites[0];
//
//    scene.interactibles[1] = talkToGuideInteraction;
//
    return scene;
}
