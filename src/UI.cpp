/* UI.cpp *
 * Manages the generation of UI widgets.
 *
 * */
#include <SFML/Graphics.hpp>

sf::Sprite newButtonSquare(sf::Vector2f position, bool dontCenterByDimensions)
{
    sf::Sprite widget;
    sf::Vector2i size(UI_SPR_BTN_SQUARE.width, UI_SPR_BTN_SQUARE.height);
    sf::Vector2f finalPos = centerByDimensions(position, size, true);
    if (dontCenterByDimensions)
        finalPos = position;

    widget.setTexture(uiSpriteTexture);
    widget.setTextureRect(UI_SPR_BTN_SQUARE);
    widget.setPosition(finalPos);
    widget.setScale(1.5, 1.5);

    return widget;
}

sf::Sprite newButton(sf::Vector2f position, bool dontCenterByDimensions)
{
    sf::Sprite widget;
    sf::Vector2i size(UI_SPR_BTN.width, UI_SPR_BTN.height);
    sf::Vector2f finalPos = centerByDimensions(position, size, true);
    if (dontCenterByDimensions) {
        finalPos = position;
    }

    widget.setTexture(uiSpriteTexture);
    widget.setTextureRect(UI_SPR_BTN);
    widget.setPosition(finalPos);
    widget.setScale(1.5, 1.5);

    return widget;
}

void createPopup(std::string titleText, std::string bodyText) {
    pauseGame();
    currentPopupTitle = titleText;
    currentPopupBodyText = bodyText;
    isPopupOpen = true;
}

void createImagePopup(std::string imgPath) {
    pauseGame();
    currentPopupImage = imgPath;
    isImagePopupOpen = true;
}


void hidePopup() {
    if (!isDialogOpen)
        resumeGame();
    else {
        isPopupOpen = false;
        isImagePopupOpen = false;
    }
}