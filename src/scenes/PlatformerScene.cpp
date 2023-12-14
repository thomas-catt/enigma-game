bool isPlatformerPlayerInAir = false;
const int platformerPlayerJumpHeight = 200;
const int platformerPlayerOrgY = 500;
float platformerPlayerX = 0;
float platformerJumpStartPlayerX = platformerPlayerX;
float platformerGameSpeed = 4.f;
int platformerDistanceTravelled = 0;
int platformerTargetDistance = 0;
bool platformerGameLost = false;

const int totalPlatformerObstacles = 28;
int platformerObstaclePositions[totalPlatformerObstacles];

const int platformerBgLayers = 8;
sf::Texture platformerBgTextures[platformerBgLayers];

void initPlatformerObstacles() {
    platformerPlayerX = 0;
    platformerJumpStartPlayerX = platformerPlayerX;
    platformerGameSpeed = 4.f;

    platformerDistanceTravelled = 0;
    platformerTargetDistance = 0;
    platformerGameLost = false;


    int lastPosition = SCREEN_W;
    for (int i = 0; i < totalPlatformerObstacles; i++) {
        lastPosition = lastPosition + 270 + (rand() % 600);
        platformerObstaclePositions[i] = lastPosition;
    }
    platformerTargetDistance = lastPosition + SCREEN_W;
}

void onPlatformerEvent(sf::Event event) {
    switch (event.key.code) {
        case sf::Keyboard::Space:
            if (!isPlatformerPlayerInAir) {
                platformerJumpStartPlayerX = platformerPlayerX;
                isPlatformerPlayerInAir = true;
            }
            break;
    }
}

void onPlatformerPreRender(sf::RenderWindow& window) {
    for (int i = 0; i < platformerBgLayers; i++) {
        int movementFactor = (platformerPlayerX * platformerGameSpeed) / (platformerBgLayers + 1 - i);
        movementFactor = movementFactor % platformerBgTextures[i].getSize().x;

        sf::Sprite platformerBg(platformerBgTextures[i]);
        platformerBg.setPosition(-movementFactor, 0);

        sf::Sprite platformerBgNext(platformerBgTextures[i]);
        platformerBgNext.setPosition(platformerBgTextures[i].getSize().x - movementFactor, 0);

        if ((int)(platformerBgNext.getGlobalBounds().left + platformerBgNext.getGlobalBounds().width) < SCREEN_W) {
            platformerBg.setPosition(platformerBg.getPosition().x + platformerBgNext.getGlobalBounds().width,
                                     platformerBg.getPosition().y);
            platformerBgNext.setPosition(platformerBgNext.getPosition().x + platformerBgNext.getGlobalBounds().width,
                                         platformerBgNext.getPosition().y);
        }

        window.draw(platformerBg);
        window.draw(platformerBgNext);
    }
//
//
//    sf::Sprite platformerPlatform(platformerPlatformTexture);
//    platformerPlatform.setPosition(0, SCREEN_H - 100);
//    window.draw(platformerPlatform);
//

    int movementFactor = (platformerPlayerX * platformerGameSpeed);
    movementFactor = movementFactor % SCREEN_W;

    sf::Sprite platformerPlatform(platformerPlatformTexture);
    platformerPlatform.setPosition( - movementFactor, SCREEN_H - 120);

    sf::Sprite platformerPlatformNext(platformerPlatformTexture);
    platformerPlatformNext.setPosition((platformerPlatformTexture.getSize().x * platformerPlatform.getScale().x) - movementFactor, SCREEN_H - 120);

//
//    if ((int)(platformerPlatformNext.getGlobalBounds().left + platformerPlatformNext.getGlobalBounds().width) < SCREEN_W) {
//        platformerPlatform.setPosition(platformerPlatform.getPosition().x + SCREEN_W,
//                                 platformerPlatform.getPosition().y);
//        platformerPlatformNext.setPosition(platformerPlatformNext.getPosition().x + SCREEN_W,
//                                     platformerPlatformNext.getPosition().y);
//    }


    window.draw(platformerPlatform);
    window.draw(platformerPlatformNext);
}

void checkHorseCollision() {
    sf::FloatRect horseRect(currentScene.animatedSprites[1].position, sf::Vector2f(horseChar.width, horseChar.height));
    sf::FloatRect playerRect(currentScene.animatedSprites[0].position, sf::Vector2f(playerChar.width, playerChar.height));
    if (horseRect.intersects(playerRect) && !platformerGameLost) {
        miniGameDefeat(MINIGAME_PLATFORMER);
    }
}

void updatePlatformerGameSpeed() {
    platformerGameSpeed += 0.002f;
}

void checkPlatformerObstacle(sf::Sprite obstacleSprite) {
    if (obstacleSprite.getGlobalBounds().intersects(sf::FloatRect (currentScene.animatedSprites[0].position, sf::Vector2f(10, 10))))
        currentScene.animatedSprites[0].position.x = obstacleSprite.getPosition().x;
}

void onPlatformerRender(sf::RenderWindow& window) {
    if (platformerDistanceTravelled > platformerTargetDistance)
        miniGameVictory(MINIGAME_PLATFORMER, keysStore.horse);

    if (isPlatformerPlayerInAir) {
        currentScene.animatedSprites[0].position.y = platformerPlayerOrgY - (platformerPlayerJumpHeight - pow(platformerPlayerX - platformerJumpStartPlayerX - sqrt(platformerPlayerJumpHeight), 2));
        if (currentScene.animatedSprites[0].position.y > platformerPlayerOrgY) {
            currentScene.animatedSprites[0].position.y = platformerPlayerOrgY;
            isPlatformerPlayerInAir = false;
        }
    }

    for (int i = 0; i < totalPlatformerObstacles; i++) {
        sf::Sprite obstacleSprite(platformerObstacleTexture);
        obstacleSprite.setPosition(platformerObstaclePositions[i] - (platformerPlayerX * platformerGameSpeed), platformerPlayerOrgY - (platformerObstacleTexture.getSize().y / 2.5));
        obstacleSprite.setScale(0.5, 0.5);
        checkPlatformerObstacle(obstacleSprite);
        window.draw(obstacleSprite);
    }

    checkHorseCollision();

    if (!isGamePaused) {
        updatePlatformerGameSpeed();

        platformerPlayerX += 1.f;
        platformerDistanceTravelled = platformerPlayerX * platformerGameSpeed;
    }
}

void onPlatformerStart() {
//    initPlatformerObstacles();
}

void loadPlatformerBgLayers() {
    for (int i = 0; i < platformerBgLayers; i++) {
        platformerBgTextures[i].loadFromFile(BACKGROUND_PLATFORMER_PATH_PREFIX + std::to_string(i + 1) + ".png");
    }
}

Scene initPlatformerScene() {
    Scene scene;
    scene.location = SCENE_PLATFORMER_GAME;
    scene.name = "Horse game";
    scene.type = SCENE_CUSTOM;
    scene.noView = true;
    scene.playerEnabled = false;
    scene.backgroundEnabled = false;
    scene.musicFilePath = MUSIC_PLATFORMER_PATH;

    scene.animatedSprites[0] = playerChar;
    scene.animatedSprites[0].position = sf::Vector2f(500, platformerPlayerOrgY);
    scene.animatedSprites[0].verticalOffset = PLAYER_SPRITE_RIGHT;
    scene.animatedSprites[0].animFrames = PLAYER_ANIM_FRAMES;
    scene.animatedSprites[0].animSpeed = PLAYER_ANIM_SPEED;


    scene.animatedSprites[1] = horseChar;
    scene.animatedSprites[1].position = sf::Vector2f(50, platformerPlayerOrgY);

    loadPlatformerBgLayers();
    initPlatformerObstacles();

    return scene;
}