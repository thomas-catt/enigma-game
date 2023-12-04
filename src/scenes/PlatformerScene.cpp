bool isPlatformerPlayerInAir = false;
const int platformerPlayerJumpHeight = 200;
const int platformerPlayerOrgY = 500;
float platformerPlayerX = 0;
float platformerJumpStartPlayerX = platformerPlayerX;
float platformerGameSpeed = 4.f;
int platformerDistanceTravelled = 0;
int platformerTargetDistance = 0;
bool platformerGameLost = false;

const int totalPlatformerObstacles = 32;
int platformerObstaclePositions[totalPlatformerObstacles];

void initPlatformerObstacles() {
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

void checkHorseCollision() {
    sf::FloatRect horseRect(currentScene.animatedSprites[1].position, sf::Vector2f(horseChar.width, horseChar.height));
    sf::FloatRect playerRect(currentScene.animatedSprites[0].position, sf::Vector2f(playerChar.width, playerChar.height));
    if (horseRect.intersects(playerRect) && !platformerGameLost) {
        miniGameDefeat(MINIGAME_PLATFORMER);
    }
}

void renderPlatformerBackground(sf::RenderWindow& window) {

}

void updatePlatformerGameSpeed() {
    platformerGameSpeed += 0.004f;
}

void checkPlatformerObstacle(sf::Sprite obstacleSprite) {
    if (obstacleSprite.getGlobalBounds().intersects(sf::FloatRect (currentScene.animatedSprites[0].position, sf::Vector2f(10, 10))))
        currentScene.animatedSprites[0].position.x = obstacleSprite.getPosition().x;
}

void onPlatformerRender(sf::RenderWindow& window) {
    renderPlatformerBackground(window);
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
        sf::Sprite obstacleSprite(rockTexture);
        obstacleSprite.setPosition(platformerObstaclePositions[i] - (platformerPlayerX * platformerGameSpeed), platformerPlayerOrgY - rockTexture.getSize().y);
        obstacleSprite.setScale(1.5, 1.5);
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
    platformerPlayerX = 0;
    platformerJumpStartPlayerX = platformerPlayerX;
    platformerGameSpeed = 4.f;

    platformerDistanceTravelled = 0;
    platformerTargetDistance = 0;
    platformerGameLost = false;

    initPlatformerObstacles();
}

Scene initPlatformerScene() {
    Scene scene;
    scene.location = SCENE_PLATFORMER_GAME;
    scene.name = "Horse game";
    scene.type = SCENE_CUSTOM;
    scene.noView = true;
    scene.playerEnabled = false;
    scene.backgroundEnabled = false;

    scene.animatedSprites[0] = playerChar;
    scene.animatedSprites[0].position = sf::Vector2f(500, platformerPlayerOrgY);
    scene.animatedSprites[0].verticalOffset = PLAYER_SPRITE_RIGHT;
    scene.animatedSprites[0].animFrames = PLAYER_ANIM_FRAMES;
    scene.animatedSprites[0].animSpeed = PLAYER_ANIM_SPEED;


    scene.animatedSprites[1] = horseChar;
    scene.animatedSprites[1].position = sf::Vector2f(50, platformerPlayerOrgY);



    return scene;
}