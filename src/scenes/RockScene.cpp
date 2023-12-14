#include <cstdlib>

const float ROCK_FALL_SPEED = 100.0f; // Adjust this value as needed

const int rockGameGroundheight = 900;
const int charheight = 16;

const int rockSceneSize = 960;

const int totalRockGameTime = 60;

// Initialize the rocks, character, and ground
int MaxRocks;

// Initialize the game loop variables
float timeElapsed;

struct Ground {
    sf::Sprite sprite;
    sf::Texture texture;

    Ground() {
        sprite.setPosition(0, rockGameGroundheight - 200);
    }
};

sf::Sprite sceneRocks[8];
Ground ground;

void initRocks(sf::Sprite sceneRocks[], int MaxRocks) {
    for (int i = 0; i < 8; ++i) {
        float x = (float)(rand() % (int)(rockSceneSize));
        float y = (float)(rand() % (int)(rockSceneSize)) - rockSceneSize;
        float yOffset = (float)(rand() % 100);  // Adjust the range as needed
        sceneRocks[i].setTexture(rockTexture);
        sceneRocks[i].setPosition(x, y + yOffset);
        sceneRocks[i].setRotation(rand() % 2 == 0 ? -30 : 30);
    }
}

bool isIntersecting(const sf::FloatRect sprite1, const sf::FloatRect sprite2) {
    return sprite1.intersects(sprite2);
}

void adjustRocks(sf::Sprite sceneRocks[], int MaxRocks) {
    // Collision check and adjustment
    for (int i = 0; i < MaxRocks; ++i) {
        for (int j = i + 1; j < MaxRocks; ++j) {
            if (isIntersecting(sceneRocks[i].getGlobalBounds(), sceneRocks[j].getGlobalBounds())) {
                float x = static_cast<float>(rand() % rockSceneSize);
                sceneRocks[j].setPosition(x, -50);
            } else if (isIntersecting(sceneRocks[i].getGlobalBounds(), ground.sprite.getGlobalBounds())) {
                float x = static_cast<float>(rand() % rockSceneSize);
                sceneRocks[i].setPosition(x, -50);
            } else if (isIntersecting(sceneRocks[i].getGlobalBounds(), sf::FloatRect(player.sprite.getPosition().x + (PLAYER_SPRITE_WIDTH/2), player.sprite.getPosition().y + (PLAYER_SPRITE_HEIGHT/2), PLAYER_SPRITE_WIDTH/4, PLAYER_SPRITE_HEIGHT/4))) {
                float x = static_cast<float>(rand() % rockSceneSize);
                sceneRocks[i].setPosition(x, -50);
//                std::cout << "player dead" << std::endl;
                miniGameDefeat(MINIGAME_ROCK_FALLING);
            }
        }
    }
}


void updateRocks(sf::Sprite sceneRocks[], float dt, int MaxRocks) {
    // Move rocks
    for (int i = 0; i < MaxRocks; ++i) {
        sf::Vector2f position = sceneRocks[i].getPosition();

        if (position.y < rockGameGroundheight + charheight) {
            // Move the rock down with a speed based on delta time
            sceneRocks[i].setPosition(position.x, position.y + ROCK_FALL_SPEED * dt);
        } else {
            float x = static_cast<float>(rand() % static_cast<int>(rockSceneSize));
            float y = static_cast<float>(rand() % static_cast<int>(rockSceneSize)) - rockSceneSize;
            float yOffset = static_cast<float>(rand() % 100);  // Adjust the range as needed
            sceneRocks[i].setPosition(x, y + yOffset);
        }
    }

    // Adjust rocks after moving
    adjustRocks(sceneRocks, MaxRocks);
}
//
//
//void handleInput(Player& player) {
//    // Example: Move the character left and right with arrow keys
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
//        player.sprite.move(-0.05f, 0.0f);
//    }
//    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
//        player.sprite.move(0.05f, 0.0f);
//    }
//}

void spawnRate() {
    if (timeElapsed <= totalRockGameTime / 4) {
        MaxRocks = 4;
    } else if (timeElapsed < totalRockGameTime) {
        MaxRocks = 8;
    } else {
        miniGameVictory(MINIGAME_ROCK_FALLING, keysStore.rock);
    }
}

void RockSceneRender(sf::RenderWindow& window) {
    // Handle player input
//    handleInput(player);
    // Update the game
//    float dt = gameClock.restart().asSeconds();
    if (!isGamePaused) {
        float dt = (float) (framecount == REFRESH_RATE - 1);
        timeElapsed += dt;
        spawnRate();
        updateRocks(sceneRocks, (20 + timeElapsed) / 1000, MaxRocks);
    }

    // Draw the game
    window.draw(ground.sprite);  // Draw ground first
    for (int i = 0; i < MaxRocks; ++i) {
        window.draw(sceneRocks[i]);
    }

    sf::Text timeIndicator("Distance left: " + std::to_string((int)(totalRockGameTime - timeElapsed)) + "m", UI_FONT_BODY);
    timeIndicator.setPosition(centerByDimensions(sf::Vector2f(player.sprite.getPosition().x, 460), sf::Vector2i(timeIndicator.getGlobalBounds().width, 1), true));
    window.draw(dropShadow(timeIndicator));
    window.draw(timeIndicator);
}

void onRockSceneShown() {
    MaxRocks = 8;
    timeElapsed = 0.f;
    initRocks(sceneRocks, MaxRocks);
}

Scene initRockScene() {
    Scene scene;

    scene.name = "Rock Scene";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_ROCK_GAME;
    scene.backgroundSpritePath = BACKGROUND_ROCK_PATH;
    scene.horizontalMovementOnly = true;
    scene.defaultPlayerPos = sf::Vector2f(400, rockGameGroundheight - PLAYER_SPRITE_HEIGHT);
    scene.defaultPlayerDir = PLAYER_SPRITE_RIGHT;
    scene.playerSpeedMultiplier = 2;
//    scene.view = sf::View(sf::FloatRect(scene.defaultPlayerPos.x, scene.defaultPlayerPos.y, 960, 960));
    scene.view = sf::View(sf::FloatRect(scene.defaultPlayerPos.x, scene.defaultPlayerPos.y, 800, 600));
    scene.musicFilePath = MUSIC_ROCK_PATH;

    return scene;
 }

