const int MaxSnakeLength = 6;

 struct Snake {
     sf::Sprite sprite;
     sf::Texture texture;
     sf::Vector2f position;
     sf::Vector2f direction;

     float speed;
     sf::RectangleShape body[MaxSnakeLength];
     int length;

 };


 // Function to initialize the snake
 void initSnake(Snake& snake) {
     if (!snake.texture.loadFromFile(ROCK_TEXTURE_PATH)) {
         std::cout << "Failed to load Snake." << std::endl;
     }

     snake.sprite.setTexture(snake.texture);
     snake.position = sf::Vector2f(173.f, 250.f);
     snake.direction = sf::Vector2f(1.f, 0.f); // Initial direction is to the right
     snake.speed = 16.0f; // Adjust the speed as needed
     snake.length = 5;  // Initial length of the snake

     // Initialize the body segments
     for (int i = 0; i < MaxSnakeLength; ++i) {
         snake.body[i].setSize(sf::Vector2f(16.f, 16.f));  // Adjust the size as needed
         snake.body[i].setFillColor(sf::Color::Green);
     }
 }


 // Function to normalize a vector (make it a unit vector)
 sf::Vector2f normalize(const sf::Vector2f& vector) {
     float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);
     if (length != 0.0f) {
         return vector / length;
     } else {
         return vector;
     }
 }


 // Function to automatically make the snake follow the player
 void followPlayer(Snake& snake, const sf::Vector2f& playerPosition) {
     // Calculate the direction from the head of the snake to the player
     snake.direction = normalize(playerPosition - snake.position);
 }


 // Function to update the snake's position and body segments
 void updateSnake(Snake& snake, float dtSeconds) {
     // Update the snake's position
     snake.position += snake.direction * snake.speed * dtSeconds;

     // Update the body segments
     for (int i = snake.length - 1; i > 0; --i) {
         snake.body[i].setPosition(snake.body[i - 1].getPosition());
     }
     snake.body[0].setPosition(snake.position);
 }


 Scene initSnakeScene() {
     Scene scene;

     scene.name = "Snake Scene";
     scene.type = SCENE_CUSTOM;
     scene.location = SCENE_SNAKE_GAME;
     scene.backgroundSpritePath = BACKGROUND_DEMO_PATH;
     scene.defaultPlayerDir = PLAYER_SPRITE_DOWN;
     scene.defaultPlayerPos = sf::Vector2f(173.f, 250.f);

     scene.view = sf::View(scene.defaultPlayerPos, sf::Vector2f(400.f, 300.f));

     scene.colliderHitboxes[0] = sf::IntRect(330, 125, 16, 16);

     return scene;
 }

