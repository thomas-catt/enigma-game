Scene initTestScene()
{
    Scene scene;

    scene.name = "Overworld";
    scene.type = SCENE_GAME;
    scene.location = SCENE_OVERWORLD;
    scene.backgroundSpritePath = BACKGROUND_TEST_PATH;
    scene.defaultPlayerPos = sf::Vector2f(600, 600);
    scene.defaultPlayerDir = PLAYER_SPRITE_DOWN;

    scene.view = sf::View(scene.defaultPlayerPos, sf::Vector2f(400.f, 300.f));

//    scene.animatedSprites[0] = guideChar;
//    scene.animatedSprites[0].position = sf::Vector2f(580, 200);

//    scene.colliderHitboxes[0] = sf::IntRect(0, 446, 600, 160);
//    scene.colliderHitboxes[1] = sf::IntRect(0, 114, 96, 38);
//    scene.colliderHitboxes[2] = sf::IntRect(513, 104, 71, 182);
//    scene.colliderHitboxes[3] = sf::IntRect(655, 106, 79, 183);
//    scene.colliderHitboxes[4] = sf::IntRect(655, 106, 79, 183);
//    scene.colliderHitboxes[5] = sf::IntRect(409, 294, 166, 77);
//    scene.colliderHitboxes[6] = sf::IntRect(666, 403, 93, 124);
//    scene.colliderHitboxes[7] = sf::IntRect(274, 4435, 321, 177);
//    scene.colliderHitboxes[8] = sf::IntRect(642, 446, 446, 160);
//    scene.colliderHitboxes[9] = sf::IntRect(0, 291, 233, 287);
//    scene.colliderHitboxes[10] = sf::IntRect(178, 350, 142, 187);

    scene.colliderHitboxes[0] =  sf::IntRect(2, 119, 94, 32);
    scene.colliderHitboxes[1] =  sf::IntRect(194, 117, 45, 30);
    scene.colliderHitboxes[2] =  sf::IntRect(272, 170, -35, -28);
    scene.colliderHitboxes[3] =  sf::IntRect(239, 140, 31, 28);
    scene.colliderHitboxes[4] =  sf::IntRect(272, 170, 48, 31);
    scene.colliderHitboxes[5] =  sf::IntRect(324, 202, 38, 30);
    scene.colliderHitboxes[6] =  sf::IntRect(368, 220, 34, 28);
    scene.colliderHitboxes[7] =  sf::IntRect(408, 247, 182, 24);
    scene.colliderHitboxes[8] =  sf::IntRect(645, 249, 280, 38);
    scene.colliderHitboxes[9] =  sf::IntRect(924, 215, 47, 34);
    scene.colliderHitboxes[10] =  sf::IntRect(973, 166, 0, 0);
    scene.colliderHitboxes[11] =  sf::IntRect(973, 167, 33, 38);
    scene.colliderHitboxes[12] =  sf::IntRect(1054, 170, 0, 0);
    scene.colliderHitboxes[13] =  sf::IntRect(1056, 122, 30, 30);
    scene.colliderHitboxes[14] =  sf::IntRect(1087, 75, 94, 29);
//    scene.colliderHitboxes[15] =  sf::IntRect(1180, 41, 96, 31);
//    scene.colliderHitboxes[16] =  sf::IntRect(554, 75, 128, 59);
//    scene.colliderHitboxes[17] =  sf::IntRect(451, 140, 118, 99);
//    scene.colliderHitboxes[18] =  sf::IntRect(667, 166, 95, 71);
//    scene.colliderHitboxes[19] =  sf::IntRect(418, 315, 176, 53);
//    scene.colliderHitboxes[20] =  sf::IntRect(652, 299, 88, 92);
//    scene.colliderHitboxes[21] =  sf::IntRect(287, 462, 144, 126);
//    scene.colliderHitboxes[22] =  sf::IntRect(427, 470, 137, 118);
//    scene.colliderHitboxes[23] =  sf::IntRect(549, 490, 51, 111);
//    scene.colliderHitboxes[24] =  sf::IntRect(637, 486, 202, 123);
//    scene.colliderHitboxes[25] =  sf::IntRect(820, 468, 92, 116);
//    scene.colliderHitboxes[26] =  sf::IntRect(900, 453, 123, 111);
//    scene.colliderHitboxes[27] =  sf::IntRect(919, 438, 112, 81);
//    scene.colliderHitboxes[28] =  sf::IntRect(937, 423, 127, 67);
//    scene.colliderHitboxes[29] =  sf::IntRect(1050, 509, -29, -32);
//    scene.colliderHitboxes[30] =  sf::IntRect(1027, 485, 23, 24);
//    scene.colliderHitboxes[31] =  sf::IntRect(1046, 421, 38, 54);
//    scene.colliderHitboxes[32] =  sf::IntRect(125, 408, 107, 162);
//    scene.colliderHitboxes[33] =  sf::IntRect(2, 300, 73, 220);
//    scene.colliderHitboxes[34] =  sf::IntRect(28, 313, 61, 228);
//    scene.colliderHitboxes[35] =  sf::IntRect(67, 343, 55, 198);
//    scene.colliderHitboxes[36] =  sf::IntRect(116, 362, 54, 55);
//    scene.colliderHitboxes[37] =  sf::IntRect(172, 393, 51, 19);
//    scene.colliderHitboxes[38] =  sf::IntRect(280, 438, 20, 31);
//    scene.colliderHitboxes[39] =  sf::IntRect(176, 230, 151, 105);
//    scene.colliderHitboxes[40] =  sf::IntRect(939, 394, 210, -47);
//    scene.colliderHitboxes[41] =  sf::IntRect(1184, 177, 53, 33);
//    scene.colliderHitboxes[42] =  sf::IntRect(1243, 200, 0, 0);
//    scene.colliderHitboxes[43] =  sf::IntRect(1150, 197, 102, 43);
//    scene.colliderHitboxes[44] =  sf::IntRect(1118, 224, 97, 44);
//    scene.colliderHitboxes[45] =  sf::IntRect(1067, 246, 150, 47);
//    scene.colliderHitboxes[46] =  sf::IntRect(1042, 279, 219, 48);
//    scene.colliderHitboxes[47] =  sf::IntRect(1024, 308, 202, 50);
//    scene.colliderHitboxes[48] =  sf::IntRect(1275, 363, 0, 0);
//    scene.colliderHitboxes[49] =  sf::IntRect(951, 366, 257, 19);

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
