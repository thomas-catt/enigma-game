/* DemoScene.cpp *
 * A game scene file. This is just a demo scene with random stuff. This one has
 * hitboxes and a player moving around in some map
 *
 * */

Scene initDemoScene() {
    Scene scene;

    scene.name = "Test Scene";
    scene.type = SCENE_GAME;
    scene.location = SCENE_DEMO_SCENE;
    scene.backgroundSpritePath = BACKGROUND_DEMO_PATH;
    scene.defaultPlayerDir = PLAYER_SPRITE_DOWN;
    scene.defaultPlayerPos = sf::Vector2f(142.f, 212.f);

    scene.view = sf::View(scene.defaultPlayerPos, sf::Vector2f(400.f, 300.f));

    scene.colliderHitboxes[0] = sf::IntRect(330, 125, 35, 62);
    scene.colliderHitboxes[1] = sf::IntRect(422, 128, 90, 80);
    scene.colliderHitboxes[2] = sf::IntRect(100, 110, 150, 110);
    scene.colliderHitboxes[3] = sf::IntRect(66, 0, 126, 153);
    scene.colliderHitboxes[4] = sf::IntRect(192, 68, 30, 32);
    scene.colliderHitboxes[5] = sf::IntRect(192, 0, 351, 70);


    InteractionPoint changeSceneInteraction;
    changeSceneInteraction.name = INTERACTION_TRAVEL;
    changeSceneInteraction.label = "Go to Test Scene";
    changeSceneInteraction.travelTo = SCENE_OVERWORLD;
    changeSceneInteraction.position = sf::Vector2f(175, 180);

    scene.interactibles[0] = changeSceneInteraction;

    InteractionPoint changeSceneInCornerInteraction;
    changeSceneInCornerInteraction.name = INTERACTION_TRAVEL;
    changeSceneInCornerInteraction.label = "Try out some rocks!";
    changeSceneInCornerInteraction.travelTo = SCENE_ROCK_GAME;
    changeSceneInCornerInteraction.position = sf::Vector2f(0, 150);

    scene.interactibles[1] = changeSceneInCornerInteraction;

    return scene;
}

