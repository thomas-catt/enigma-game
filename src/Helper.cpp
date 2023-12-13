/* Helper.cpp *
 * Contains simple functions to make certain calculations easier
 *
 * */

/* Calculates and returns the string length till \0
 * */

int  strLength(std::string str) {
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        length++;
    }
    return length;
}

int strLength(char str[]) {
    int length = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        length++;
    }
    return length;
}

/* The centerByDimensions function converts a position to represent the center
 * of the object. By default, SFML's position always represents the top left edge
 * of the objects. This function takes in the dimensions and returns a properly
 * adjusted position vector that points to the center of the object instead of
 * the top left edge.
 *
 * */
sf::Vector2f centerByDimensions(sf::Vector2f orgVector, sf::Vector2i dimensions, bool invertAlignment)
{
    /* The invertAlignment inverts the target location to be opposite to the
     * object instead of pushing within it
     *
     */
    int invertFactor = invertAlignment ? -1 : 1;
    return sf::Vector2f(orgVector.x + (invertFactor * dimensions.x / 2), orgVector.y + (invertFactor * dimensions.y / 2));
}

sf::Text dropShadow(sf::Text tx)
{
    sf::Text txShadow = tx;
    txShadow.setFillColor(sf::Color::Black);
    txShadow.setPosition(txShadow.getPosition().x + 2, txShadow.getPosition().y + 2);

    return txShadow;
}

void textWrapper(sf::Text &text, int width, int continueIndex = 0)
{
    std::string textStr = text.getString();
    int lastSpaceIndex = 0;
    for (int i = continueIndex; i < textStr.length(); i++)
    {
        if (textStr[i] == ' ')
            lastSpaceIndex = i;

        sf::Vector2<float> characterPos = text.findCharacterPos(i);
        if (characterPos.x >= (text.getPosition().x + width))
        {

//            char extraChar = textStr[textStr.length() - 1];
//            for (int j = textStr.length(); j > i; j--)
//            {
//                textStr[j] = textStr[j - 1];
//            }
            textStr[lastSpaceIndex] = '\n';

            text.setString(textStr);
//            text.setString(textStr + extraChar);
            textWrapper(text, width, i + 1);
            break;
        }

    }
}

bool ReadSaveFile(bool& rockKey, bool& snakeKey, bool& cipherKey, SceneLocation& currentSceneLocation, bool& guideIntroduced, sf::Vector2f& lastPlayerPos)
{
    std::ifstream data(SAVE_FILE_NAME);

    if (data.is_open())
    {
        int currentSceneLocationInt = 0;
        int posX, posY;
        int guideIntroducedBool;

        data >> rockKey >> snakeKey >> cipherKey;
        data >> currentSceneLocationInt;
        data >> guideIntroducedBool;
        data >> posX >> posY;

        guideIntroduced = (bool)guideIntroducedBool;
        currentSceneLocation = (SceneLocation)currentSceneLocationInt;
        lastPlayerPos = sf::Vector2f(posX, posY);
    } else {
        return false;
    }
    data.close();
    return true;
}

bool WriteSaveFile(bool rockKey, bool snakeKey, bool cipherKey, SceneLocation currentSceneLocation, bool guideIntroduced, sf::Vector2f lastPlayerPos = sf::Vector2f(-1, -1))
{
    int keys = 0;
    std::ofstream data(SAVE_FILE_NAME);

    if (data.is_open())
    {
        data << rockKey <<  " " << snakeKey  <<  " " << cipherKey  <<  " " << std::endl;
        data << (int)currentSceneLocation << std::endl;
        data << (int)guideIntroduced << std::endl;
        data << (int)lastPlayerPos.x  <<  " " << (int)lastPlayerPos.y << std::endl;
    } else {
        return false;
    }
    data.close();
    return true;
}


int stringLength(char s[]) {
    int length = 0;
    for (int i = 0; s[i] != '\0'; i++)
        length++;

    return length;
}

int stringCountOccurences(std::string str, char key) {
    int occurences = 0;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == key)
            occurences++;
    }

    return occurences;
}

bool stringCompare(char str1[], char str2[]) {
    if (stringLength(str1) != stringLength(str2))
        return false;

    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] != str2[i])
            return false;
    }

    return true;
}