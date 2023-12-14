const int puzzleRows = 3;
const int puzzleCols = 3;

int solvedPuzzleMatrix[puzzleRows][puzzleCols] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
};

int currentPuzzleMatrix[puzzleRows][puzzleCols];

bool puzzleSolvedMessageDisplayed = false;

sf::Vector2i selectedPuzzleRectIndices(-1, -1);

// Function declarations
void handlePuzzleKeyPress(sf::Keyboard::Key key, sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols]);
void shufflePuzzleRectangles(sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols]);
sf::Vector2i getPuzzleRectangleIndices(sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols], sf::RectangleShape& rect);
void swapPuzzleRectangles(sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols], sf::Vector2i index1, sf::Vector2i index2);
void handlePuzzleMousePress(float mouseX, float mouseY, sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols]);
void handlePuzzleCipherMouseClick(sf::Vector2i clickedIndices);
void handlePuzzleCipherEvent(sf::Event event);
bool isPuzzleSolved();

// Global array for puzzleRectangles
sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols];

// Function to swap two values
template <typename T>
void customSwap(T& a, T& b) {
    T temp = a;
    a = b;
    b = temp;
}

void puzzleCipherInit() {
    // Calculate the size of each sub-rectangle
    sf::Vector2u imageSize = puzzleCipherTexture.getSize();
    sf::Vector2u subRectSize(imageSize.x / puzzleCols, imageSize.y / puzzleRows);

    // Set up puzzleRectangles
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            puzzleRectangles[i][j].setSize(sf::Vector2f(subRectSize.x, subRectSize.y));
            puzzleRectangles[i][j].setTexture(&puzzleCipherTexture);
            puzzleRectangles[i][j].setTextureRect(sf::IntRect(j * subRectSize.x, i * subRectSize.y, subRectSize.x, subRectSize.y));
            puzzleRectangles[i][j].setOutlineColor(sf::Color::White);  // Set border color
            puzzleRectangles[i][j].setOutlineThickness(3.f);  // Set border thickness
        }
    }

    // Shuffle puzzleRectangles before the initial positioning
    shufflePuzzleRectangles(puzzleRectangles);

    // Arrange puzzleRectangles in the correct pattern initially
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            puzzleRectangles[i][j].setPosition(j * subRectSize.x, i * subRectSize.y);
        }
    }

    createPopup("Instructions", "Use your mouse to select a puzzle piece. Any puzzle piece clicked will be swapped by the piece at the bottom right.\n\nArrange all the pieces in the correct order to complete the puzzle.\n\nPress Q to close this puzzle.");
//    createImagePopup("assets/sprites/Keys.png");
}

void puzzleCipherRender(sf::RenderWindow& window) {

    // Draw puzzleRectangles
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            window.draw(puzzleRectangles[i][j]);
        }
    }

    // Check if the puzzle is solved
    if (!puzzleSolvedMessageDisplayed && isPuzzleSolved()) {
//        createPopup("Complete", "Congratulations, you solved the puzzle.");
        puzzleCipherCompleted = true;
        loadScene(initCipherScene(), true);

        // Print debugging information
        std::cout << "Solved Matrix:" << std::endl;
        for (int i = 0; i < puzzleRows; ++i) {
            for (int j = 0; j < puzzleCols; ++j) {
                std::cout << solvedPuzzleMatrix[i][j] << ' ';
            }
            std::cout << std::endl;
        }

        std::cout << "Current Arrangement:" << std::endl;
        for (int i = 0; i < puzzleRows; ++i) {
            for (int j = 0; j < puzzleCols; ++j) {
                std::cout << currentPuzzleMatrix[i][j] << ' ';
            }
            std::cout << std::endl;
        }

        puzzleSolvedMessageDisplayed = true;
    }
}

// Function to check if the puzzle is solved
bool isPuzzleSolved() {
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            if (currentPuzzleMatrix[i][j] != solvedPuzzleMatrix[i][j]) {
                return false; // Puzzle is not solved
            }
        }
    }
    return true; // Puzzle is solved
}


void handlePuzzleKeyPress(sf::Keyboard::Key key, sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols]) {
    sf::Vector2i emptyPos = getPuzzleRectangleIndices(puzzleRectangles, puzzleRectangles[2][2]);

    // Check if the empty space is within bounds
    if (emptyPos.x >= 0 && emptyPos.y >= 0) {
        sf::Vector2i adjacentPos = emptyPos;

        // Update the adjacent position based on the key pressed
        switch (key) {
            case sf::Keyboard::Left:
                adjacentPos.y = std::min(adjacentPos.y + 1, puzzleCols - 1);
                break;
            case sf::Keyboard::Right:
                adjacentPos.y = std::max(adjacentPos.y - 1, 0);
                break;
            case sf::Keyboard::Up:
                adjacentPos.x = std::min(adjacentPos.x + 1, puzzleRows - 1);
                break;
            case sf::Keyboard::Down:
                adjacentPos.x = std::max(adjacentPos.x - 1, 0);
                break;
            case sf::Keyboard::Q:
                loadScene(initCipherScene(), true);
                break;

            default:
                // Handle other keys or add logging for unknown keys
                break;
        }

        // Swap the empty space with the adjacent rectangle
        swapPuzzleRectangles(puzzleRectangles, emptyPos, adjacentPos);
    }
}

// Function to shuffle the order of puzzleRectangles randomly
void shufflePuzzleRectangles(sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols]) {

    // Reset the puzzleSolvedMessageDisplayed flag
    puzzleSolvedMessageDisplayed = false;

    // Use the global currentPuzzleMatrix
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            currentPuzzleMatrix[i][j] = solvedPuzzleMatrix[i][j];
        }
    }

    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            int swapI = i + rand() % (puzzleRows - i);
            int swapJ = rand() % puzzleCols;

            // Swap puzzleRectangles and update the currentPuzzleMatrix
            customSwap(puzzleRectangles[i][j], puzzleRectangles[swapI][swapJ]);
            customSwap(currentPuzzleMatrix[i][j], currentPuzzleMatrix[swapI][swapJ]);
        }
    }

    // After shuffling in shufflePuzzleRectangles
    std::cout << "Current Matrix After Shuffling:" << std::endl;
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            std::cout << currentPuzzleMatrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}


// Function to get the indices of the rectangle in the array
sf::Vector2i getPuzzleRectangleIndices(sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols], sf::RectangleShape& rect) {
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            if (&rect == &puzzleRectangles[i][j]) {
                return sf::Vector2i(i, j);
            }
        }
    }
    return sf::Vector2i(-1, -1); // Not found
}

// Function to swap puzzleRectangles in the array
void swapPuzzleRectangles(sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols], sf::Vector2i index1, sf::Vector2i index2) {
    sf::Vector2f tempPosition = puzzleRectangles[index1.x][index1.y].getPosition();
    puzzleRectangles[index1.x][index1.y].setPosition(puzzleRectangles[index2.x][index2.y].getPosition());
    puzzleRectangles[index2.x][index2.y].setPosition(tempPosition);
    customSwap(puzzleRectangles[index1.x][index1.y], puzzleRectangles[index2.x][index2.y]);

    // Update currentPuzzleMatrix based on the swapped puzzleRectangles
    customSwap(currentPuzzleMatrix[index1.x][index1.y], currentPuzzleMatrix[index2.x][index2.y]);

    // Debug output
    std::cout << "Current Matrix After Swapping:" << std::endl;
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            std::cout << currentPuzzleMatrix[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}

void handlePuzzleMousePress(float mouseX, float mouseY, sf::RectangleShape puzzleRectangles[puzzleRows][puzzleCols]) {
    // Convert the mouse coordinates to window coordinates
//    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(static_cast<int>(mouseX), static_cast<int>(mouseY)));
    sf::Vector2f mousePos(mouseX, mouseY);

    // Check if the mouse press is within any rectangle
    for (int i = 0; i < puzzleRows; ++i) {
        for (int j = 0; j < puzzleCols; ++j) {
            sf::FloatRect rectBounds = puzzleRectangles[i][j].getGlobalBounds();
            if (rectBounds.contains(mousePos)) {
                // Reset the color of the previously selected rectangle (if any)
                if (selectedPuzzleRectIndices.x != -1 && selectedPuzzleRectIndices.y != -1) {
                    puzzleRectangles[selectedPuzzleRectIndices.x][selectedPuzzleRectIndices.y].setOutlineColor(sf::Color::White);
                }

                // Update the selected rectangle indices
                selectedPuzzleRectIndices.x = i;
                selectedPuzzleRectIndices.y = j;

                // Change the color of the selected rectangle
                puzzleRectangles[i][j].setOutlineColor(sf::Color::Red);

                // Handle the click on the rectangle (e.g., swap with the empty position)
                sf::Vector2i clickedIndices = getPuzzleRectangleIndices(puzzleRectangles, puzzleRectangles[i][j]);
                handlePuzzleCipherMouseClick(clickedIndices);
                return;
            }
        }
    }
}


// Function to handle a mouse click on a rectangle
void handlePuzzleCipherMouseClick(sf::Vector2i clickedIndices) {
    // Handle the click (e.g., swap with the empty position)
    sf::Vector2i emptyPos = getPuzzleRectangleIndices(puzzleRectangles, puzzleRectangles[2][2]);

    // Check if the empty space is within bounds
    if (emptyPos.x >= 0 && emptyPos.y >= 0) {
        // Swap the empty space with the clicked rectangle
        swapPuzzleRectangles(puzzleRectangles, emptyPos, clickedIndices);
    }
}

void handlePuzzleCipherEvent(sf::Event event) {
    switch (event.type) {
        case sf::Event::KeyPressed:
            handlePuzzleKeyPress(event.key.code, puzzleRectangles);
            break;
        case sf::Event::MouseButtonPressed:
            handlePuzzleMousePress(event.mouseButton.x, event.mouseButton.y, puzzleRectangles);
            break;
        default:
            break;
    }
}

Scene initPuzzleCipherScene() {
    Scene scene;
    scene.name = "Puzzle cipher";
    scene.type = SCENE_CUSTOM;
    scene.location = SCENE_CIPHER_PUZZLE;
    scene.backgroundEnabled = false;
    scene.playerEnabled = false;
    scene.noView = true;
    scene.musicEnabled = false;

    return scene;
}