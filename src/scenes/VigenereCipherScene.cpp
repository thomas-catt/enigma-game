void onVigenereRender(sf::RenderWindow& window) {

}

void onVigenereEvent(sf::Event event) {

}

void onVigenereStart() {

}

Scene initVigenereCipherScene() {
    Scene scene;
    scene.name = "Vigenere Cipher";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_CIPHER_VIGENERE;
    scene.noView = true;
    scene.playerEnabled = false;
    scene.backgroundSpritePath = BACKGROUND_DEMO_PATH;
}