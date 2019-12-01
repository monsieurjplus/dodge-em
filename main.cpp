#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdint.h>

using namespace std;

typedef struct s_Game {
    uint8_t speedFactor;
    uint16_t screenHeight;
    uint16_t screenWidth;
    bool isPaused;
} Game;

typedef struct s_ControlsEvents {
    int8_t joystickButtonReleased;
    sf::Event::KeyEvent keyReleased;
} ControlsEvents;
/**
 * 
 * Switch Pro Controller Mapping
 *   0 = B  
 *   1 = A
 *   2 = Y
 *   3 = X
 *   4 = L
 *   5 = R
 *   6 = ZL
 *   7 = ZR
 *   8 = -
 *   9 = +
 *  10 = L3
 *  11 = R3
 *  12 = Home
 *  13 = Capture
 * 
 *  Joy PovX = D-Pad Axis X
 *  Joy PovY = D-Pad Axis Y
 *  Joy X = Left joystick Axis X
 *  Joy Y = Left joystick Axis Y
 *  Joy U = Right joystick Axis X
 *  Joy V = Right joystick Axis Y
 * 
 */
typedef struct s_Controls {
    uint8_t ACCEL;
    uint8_t START;
} Controls;

typedef struct s_Map {
    uint16_t internalPadding;
    uint16_t circuitWidth;
    uint16_t circuitSideWidth;
    uint16_t circuitZeroSideSize;
    uint16_t circuitOneSideSize;
    uint16_t circuitTwoSideSize;
} Map;

typedef struct s_AiPrediction {
    bool activeStrategy;
    uint8_t nextCircuit;
    bool nextCircuitIsInternal;
    bool nextCircuitIsExternal;
} AiPrediction;

typedef struct s_Player {
    uint16_t posX;
    uint16_t posY;
    float speed;
    float accel;
    uint16_t angle;

    uint16_t height;
    uint16_t width;
    sf::Texture texture;
    sf::Sprite sprite;

    uint8_t circuit; // ext to int: 0, 1, 2, 3
    bool movingFromCircuit;
    uint8_t frameStartCircuitMove;
    bool leftToRight;
    
    bool useJoystick;
    uint8_t joystickId;

    uint8_t collectedItems;
    uint8_t lives;
    bool hasLost;

    bool controlByAI;
    AiPrediction aiPrediction;
} Player;

typedef struct s_Item {
    uint16_t posX;
    uint16_t posY;
    uint16_t height;
    uint16_t width;

    sf::Sprite sprite;

    bool isCollected;
} Item;

void initPlayer1(Player * player, Map map, bool isHuman, bool useJoystick, uint8_t joystickId, bool firstInit)
{
    player->posX                  = map.internalPadding;
    player->posY                  = 310.f;
    player->speed                 = 1;
    player->accel                 = 1;
    player->height                = 90.f;
    player->width                 = 90.f;
    player->angle                 = 0.f;
    player->circuit               = 0.f;
    player->frameStartCircuitMove = 0;
    player->movingFromCircuit     = false;
    player->leftToRight           = true;

    if (isHuman == true) {
        player->useJoystick = useJoystick;
        player->controlByAI = false;

        if (player->useJoystick == true) {
            player->joystickId = joystickId;
        }

        player->hasLost = false;
        if (firstInit == true) {
            player->lives = 3;
        } else {
            player->lives--;
        }
    } else {
        player->controlByAI = true;
        struct s_AiPrediction playerAiPrediction;
        playerAiPrediction.activeStrategy = false;
        player->aiPrediction              = playerAiPrediction;
    }

    player->sprite.setRotation(0);
    player->sprite.setPosition(sf::Vector2f(player->posX, player->posY));
}

void initPlayer2(Player * player, Map map, bool isHuman, bool useJoystick, uint8_t joystickId)
{
    player->posX                  = 835.f;
    player->posY                  = 725.f;
    player->speed                 = 1;
    player->accel                 = 1;
    player->height                = 90.f;
    player->width                 = 90.f;
    player->angle                 = 0.f;
    player->circuit               = 0.f;
    player->frameStartCircuitMove = 0;
    player->movingFromCircuit     = false;
    player->leftToRight           = false;

    if (isHuman == true) {
        player->useJoystick = useJoystick;
        player->controlByAI = false;

        if (player->useJoystick == true) {    
            player->joystickId  = joystickId;
        }
    } else {
        player->controlByAI = true;
        struct s_AiPrediction playerAiPrediction;
        playerAiPrediction.activeStrategy = false;
        player->aiPrediction              = playerAiPrediction;
    }

    player->sprite.setRotation(0);
    player->sprite.setPosition(sf::Vector2f(player->posX, player->posY));
}

void initItems(std::vector<s_Item> * items) 
{
    items->empty();

    std::vector<std::pair<uint16_t, uint16_t> > itemsPositions;

    // Circuit 0 (external)

    // Top left corner
    std::pair<uint16_t, uint16_t> itemTL(30, 35);
    itemsPositions.push_back(itemTL);

    // Left vertical
    std::pair<uint16_t, uint16_t> itemLV1(30, 140);
    itemsPositions.push_back(itemLV1);

    std::pair<uint16_t, uint16_t> itemLV2(30, 245);
    itemsPositions.push_back(itemLV2);

    std::pair<uint16_t, uint16_t> itemLV3(30, 550);
    itemsPositions.push_back(itemLV3);

    std::pair<uint16_t, uint16_t> itemLV4(30, 655);
    itemsPositions.push_back(itemLV4);

    std::pair<uint16_t, uint16_t> itemLV5(30, 760);
    itemsPositions.push_back(itemLV5);

    // Bottom left corner
    std::pair<uint16_t, uint16_t> itemBL(30, 865);
    itemsPositions.push_back(itemBL);

    // Top horizontal
    std::pair<uint16_t, uint16_t> itemTH1(135, 35);
    itemsPositions.push_back(itemTH1);

    std::pair<uint16_t, uint16_t> itemTH2(240, 35);
    itemsPositions.push_back(itemTH2);

    std::pair<uint16_t, uint16_t> itemTH3(345, 35);
    itemsPositions.push_back(itemTH3);

    std::pair<uint16_t, uint16_t> itemTH4(550, 35);
    itemsPositions.push_back(itemTH4);

    std::pair<uint16_t, uint16_t> itemTH5(655, 35);
    itemsPositions.push_back(itemTH5);

    std::pair<uint16_t, uint16_t> itemTH6(760, 35);
    itemsPositions.push_back(itemTH6);

    // Bottom horizontal
    std::pair<uint16_t, uint16_t> itemBH1(135, 865);
    itemsPositions.push_back(itemBH1);

    std::pair<uint16_t, uint16_t> itemBH2(240, 865);
    itemsPositions.push_back(itemBH2);

    std::pair<uint16_t, uint16_t> itemBH3(345, 865);
    itemsPositions.push_back(itemBH3);

    std::pair<uint16_t, uint16_t> itemBH4(550, 865);
    itemsPositions.push_back(itemBH4);

    std::pair<uint16_t, uint16_t> itemBH5(655, 865);
    itemsPositions.push_back(itemBH5);

    std::pair<uint16_t, uint16_t> itemBH6(760, 865);
    itemsPositions.push_back(itemBH6);

    // Top right corner
    std::pair<uint16_t, uint16_t> itemTR(865, 35);
    itemsPositions.push_back(itemTR);

    // Right vertical
    std::pair<uint16_t, uint16_t> itemRV1(865, 140);
    itemsPositions.push_back(itemRV1);

    std::pair<uint16_t, uint16_t> itemRV2(865, 245);
    itemsPositions.push_back(itemRV2);

    std::pair<uint16_t, uint16_t> itemRV3(865, 350);
    itemsPositions.push_back(itemRV3);

    std::pair<uint16_t, uint16_t> itemRV4(865, 550);
    itemsPositions.push_back(itemRV4);

    std::pair<uint16_t, uint16_t> itemRV5(865, 655);
    itemsPositions.push_back(itemRV5);

    std::pair<uint16_t, uint16_t> itemRV6(865, 760);
    itemsPositions.push_back(itemRV6);

    // Bottom right corner
    std::pair<uint16_t, uint16_t> itemBR(865, 865);
    itemsPositions.push_back(itemBR);


    // Circuit 1

    // Top left corner
    std::pair<uint16_t, uint16_t> itemC1TL(135, 140);
    itemsPositions.push_back(itemC1TL);

    // Left vertical
    std::pair<uint16_t, uint16_t> itemC1LV1(135, 245);
    itemsPositions.push_back(itemC1LV1);

    std::pair<uint16_t, uint16_t> itemC1LV2(135, 350);
    itemsPositions.push_back(itemC1LV2);

    std::pair<uint16_t, uint16_t> itemC1LV3(135, 550);
    itemsPositions.push_back(itemC1LV3);

    std::pair<uint16_t, uint16_t> itemC1LV4(135, 655);
    itemsPositions.push_back(itemC1LV4);

    // Bottom left corner
    std::pair<uint16_t, uint16_t> itemC1BL(135, 760);
    itemsPositions.push_back(itemC1BL);

    // Top horizontal
    std::pair<uint16_t, uint16_t> itemC1TH1(240, 140);
    itemsPositions.push_back(itemC1TH1);

    std::pair<uint16_t, uint16_t> itemC1TH2(345, 140);
    itemsPositions.push_back(itemC1TH2);

    std::pair<uint16_t, uint16_t> itemC1TH3(550, 140);
    itemsPositions.push_back(itemC1TH3);

    std::pair<uint16_t, uint16_t> itemC1TH4(655, 140);
    itemsPositions.push_back(itemC1TH4);

    // Top right corner
    std::pair<uint16_t, uint16_t> itemC1TR(760, 140);
    itemsPositions.push_back(itemC1TR);

    // Bottom horizontal
    std::pair<uint16_t, uint16_t> itemC1BH1(240, 760);
    itemsPositions.push_back(itemC1BH1);

    std::pair<uint16_t, uint16_t> itemC1BH2(345, 760);
    itemsPositions.push_back(itemC1BH2);

    std::pair<uint16_t, uint16_t> itemC1BH3(550, 760);
    itemsPositions.push_back(itemC1BH3);

    std::pair<uint16_t, uint16_t> itemC1BH4(655, 760);
    itemsPositions.push_back(itemC1BH4);

    // Right vertical
    std::pair<uint16_t, uint16_t> itemC1RV1(760, 245);
    itemsPositions.push_back(itemC1RV1);

    std::pair<uint16_t, uint16_t> itemC1RV2(760, 350);
    itemsPositions.push_back(itemC1RV2);

    std::pair<uint16_t, uint16_t> itemC1RV3(760, 550);
    itemsPositions.push_back(itemC1RV3);

    std::pair<uint16_t, uint16_t> itemC1RV4(760, 655);
    itemsPositions.push_back(itemC1RV4);

    // Bottom right corner
    std::pair<uint16_t, uint16_t> itemC1BR(760, 760);
    itemsPositions.push_back(itemC1BR);


    // Circuit 2

    // Top left corner
    std::pair<uint16_t, uint16_t> itemC2TL(240, 245);
    itemsPositions.push_back(itemC2TL);

    // Left vertical
    std::pair<uint16_t, uint16_t> itemC2LV1(240, 350);
    itemsPositions.push_back(itemC2LV1);

    std::pair<uint16_t, uint16_t> itemC2LV2(240, 550);
    itemsPositions.push_back(itemC2LV2);

    // Bottom left corner
    std::pair<uint16_t, uint16_t> itemC2BL(240, 655);
    itemsPositions.push_back(itemC2BL);

    // Top horizontal
    std::pair<uint16_t, uint16_t> itemC2TH1(345, 245);
    itemsPositions.push_back(itemC2TH1);

    std::pair<uint16_t, uint16_t> itemC2TH2(550, 245);
    itemsPositions.push_back(itemC2TH2);

    // Top right corner
    std::pair<uint16_t, uint16_t> itemC2TR(655, 245);
    itemsPositions.push_back(itemC2TR);

    // Bottom horizontal
    std::pair<uint16_t, uint16_t> itemC2BH1(345, 655);
    itemsPositions.push_back(itemC2BH1);

    std::pair<uint16_t, uint16_t> itemC2BH2(550, 655);
    itemsPositions.push_back(itemC2BH2);

    // Right vertical
    std::pair<uint16_t, uint16_t> itemC2RV1(655, 350);
    itemsPositions.push_back(itemC2RV1);

    std::pair<uint16_t, uint16_t> itemC2RV2(655, 550);
    itemsPositions.push_back(itemC2RV2);

    // Bottom right corner
    std::pair<uint16_t, uint16_t> itemC2BR(655, 655);
    itemsPositions.push_back(itemC2BR);


    // Circuit 3

    // Top left corner
    std::pair<uint16_t, uint16_t> itemC3TL(345, 350);
    itemsPositions.push_back(itemC3TL);

    // Bottom left corner
    std::pair<uint16_t, uint16_t> itemC3BL(345, 550);
    itemsPositions.push_back(itemC3BL);

    // Top right corner
    std::pair<uint16_t, uint16_t> itemC3TR(550, 350);
    itemsPositions.push_back(itemC3TR);

    // Bottom right corner
    std::pair<uint16_t, uint16_t> itemC3BR(550, 550);
    itemsPositions.push_back(itemC3BR);

    for (std::size_t itemIndex = 0; itemIndex < itemsPositions.size(); ++itemIndex) {
        sf::Texture itemTexture;
        if (!itemTexture.loadFromFile("gfx/barrel.png"))
        {
            // erreur...
        }

        s_Item item;
        item.height      = 30;
        item.width       = 30;
        item.posX        = itemsPositions[itemIndex].first;
        item.posY        = itemsPositions[itemIndex].second;
        item.isCollected = false;
        item.sprite.setTexture(itemTexture);
        item.sprite.setPosition(sf::Vector2f(itemsPositions[itemIndex].first, itemsPositions[itemIndex].second));

        items->push_back(item);
    }
}

void drawMap(sf::RenderWindow * window, Map map)
{
    // Map rect 1

    sf::RectangleShape map1Line1(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line1.rotate(0);
    map1Line1.setPosition(sf::Vector2f(map.circuitWidth, map.circuitWidth));

    sf::RectangleShape map1Line2(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line2.rotate(90);
    map1Line2.setPosition(sf::Vector2f(map.circuitWidth, map.circuitWidth));

    sf::RectangleShape map1Line3(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line3.rotate(0);
    map1Line3.setPosition(sf::Vector2f(map.circuitWidth + map.circuitZeroSideSize + map.circuitWidth, map.circuitWidth));

    sf::RectangleShape map1Line4(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line4.rotate(90);
    map1Line4.setPosition(sf::Vector2f(830.f, map.circuitWidth));

    sf::RectangleShape map1Line5(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line5.rotate(0);
    map1Line5.setPosition(sf::Vector2f(map.circuitWidth, map.circuitWidth + map.circuitZeroSideSize + map.circuitWidth + map.circuitZeroSideSize));

    sf::RectangleShape map1Line6(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line6.rotate(90);
    map1Line6.setPosition(sf::Vector2f(map.circuitWidth, map.circuitWidth + map.circuitZeroSideSize + map.circuitWidth));

    sf::RectangleShape map1Line7(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line7.rotate(90);
    map1Line7.setPosition(sf::Vector2f(830.f, map.circuitWidth + map.circuitZeroSideSize + map.circuitWidth));

    sf::RectangleShape map1Line8(sf::Vector2f(map.circuitZeroSideSize, map.circuitSideWidth));
    map1Line8.rotate(0);
    map1Line8.setPosition(sf::Vector2f(map.circuitWidth + map.circuitZeroSideSize + map.circuitWidth, map.circuitWidth + map.circuitZeroSideSize + map.circuitWidth + map.circuitZeroSideSize));


    // Map rect 2

    sf::RectangleShape map2Line1(sf::Vector2f(210, 5));
    map2Line1.rotate(0);
    map2Line1.setPosition(sf::Vector2f(205.f, 205.f));

    sf::RectangleShape map2Line2(sf::Vector2f(210, 5));
    map2Line2.rotate(90);
    map2Line2.setPosition(sf::Vector2f(205.f, 205.f));

    sf::RectangleShape map2Line3(sf::Vector2f(210, 5));
    map2Line3.rotate(0);
    map2Line3.setPosition(sf::Vector2f(205.f, 725.f));

    sf::RectangleShape map2Line4(sf::Vector2f(210, 5));
    map2Line4.rotate(90);
    map2Line4.setPosition(sf::Vector2f(205.f, 515.f));

    sf::RectangleShape map2Line5(sf::Vector2f(210, 5));
    map2Line5.rotate(0);
    map2Line5.setPosition(sf::Vector2f(515.f, 205.f));

    sf::RectangleShape map2Line6(sf::Vector2f(210, 5));
    map2Line6.rotate(90);
    map2Line6.setPosition(sf::Vector2f(725.f, 205.f));

    sf::RectangleShape map2Line7(sf::Vector2f(210, 5));
    map2Line7.rotate(0);
    map2Line7.setPosition(sf::Vector2f(515.f, 725.f));

    sf::RectangleShape map2Line8(sf::Vector2f(210, 5));
    map2Line8.rotate(90);
    map2Line8.setPosition(sf::Vector2f(725.f, 515.f));


    // Map rect 3

    sf::RectangleShape map3Line1(sf::Vector2f(105, 5));
    map3Line1.rotate(0);
    map3Line1.setPosition(sf::Vector2f(310.f, 310.f));

    sf::RectangleShape map3Line2(sf::Vector2f(105, 5));
    map3Line2.rotate(90);
    map3Line2.setPosition(sf::Vector2f(310.f, 310.f));

    sf::RectangleShape map3Line3(sf::Vector2f(105, 5));
    map3Line3.rotate(0);
    map3Line3.setPosition(sf::Vector2f(310.f, 620.f));

    sf::RectangleShape map3Line4(sf::Vector2f(105, 5));
    map3Line4.rotate(90);
    map3Line4.setPosition(sf::Vector2f(310.f, 515.f));

    sf::RectangleShape map3Line5(sf::Vector2f(105, 5));
    map3Line5.rotate(0);
    map3Line5.setPosition(sf::Vector2f(515.f, 310.f));

    sf::RectangleShape map3Line6(sf::Vector2f(105, 5));
    map3Line6.rotate(90);
    map3Line6.setPosition(sf::Vector2f(620.f, 310.f));

    sf::RectangleShape map3Line7(sf::Vector2f(105, 5));
    map3Line7.rotate(0);
    map3Line7.setPosition(sf::Vector2f(515.f, 620.f));

    sf::RectangleShape map3Line8(sf::Vector2f(105, 5));
    map3Line8.rotate(90);
    map3Line8.setPosition(sf::Vector2f(620.f, 515.f));

    // Map center
    
    sf::RectangleShape mapCenter(sf::Vector2f(100.f, 100.f));
    mapCenter.setPosition(sf::Vector2f(415.f, 415.f));

    window->draw(map1Line1);
    window->draw(map1Line2);
    window->draw(map1Line3);
    window->draw(map1Line4);
    window->draw(map1Line5);
    window->draw(map1Line6);
    window->draw(map1Line7);
    window->draw(map1Line8);

    window->draw(map2Line1);
    window->draw(map2Line2);
    window->draw(map2Line3);
    window->draw(map2Line4);
    window->draw(map2Line5);
    window->draw(map2Line6);
    window->draw(map2Line7);
    window->draw(map2Line8);

    window->draw(map3Line1);
    window->draw(map3Line2);
    window->draw(map3Line3);
    window->draw(map3Line4);
    window->draw(map3Line5);
    window->draw(map3Line6);
    window->draw(map3Line7);
    window->draw(map3Line8);

    window->draw(mapCenter);
}

void drawItems(sf::RenderWindow * window, std::vector<s_Item> items)
{
    for (std::size_t itemIndex = 0; itemIndex < items.size(); ++itemIndex) {
        if (items[itemIndex].isCollected == false) {
            window->draw(items[itemIndex].sprite);
        }
    }
}

bool isRightDirectionPressed(Player player, Controls controls)
{
    return (
        player.controlByAI == false &&
        (
            (player.useJoystick == true && sf::Joystick::getAxisPosition(player.joystickId, sf::Joystick::PovX) == 100) ||
            (player.useJoystick == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        )
    );
}

bool isLeftDirectionPressed(Player player, Controls controls)
{
    return (
        player.controlByAI == false &&
        (
            (player.useJoystick == true && sf::Joystick::getAxisPosition(player.joystickId, sf::Joystick::PovX) == -100) ||
            (player.useJoystick == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        )
    );
}

void checkPauseControl(Game * game, Player collectorPlayer, Player defenderPlayer, Controls controls, ControlsEvents controlsEvents)
{
    if (
        (
            collectorPlayer.controlByAI == false &&
            (
                (collectorPlayer.useJoystick == true && sf::Joystick::isButtonPressed(collectorPlayer.joystickId, controls.START)) ||
                (collectorPlayer.useJoystick == false && controlsEvents.keyReleased.code == sf::Keyboard::Enter)
            )
        ) ||
        (
            defenderPlayer.controlByAI == false &&
            (
                (defenderPlayer.useJoystick == true && sf::Joystick::isButtonPressed(defenderPlayer.joystickId, controls.START)) ||
                (defenderPlayer.useJoystick == false && controlsEvents.keyReleased.code == sf::Keyboard::Enter)
            )
        )
    ) {
        std::cout << "change pause" << std::endl;
        if (game->isPaused == true) {
            game->isPaused = false;
        } else {
            game->isPaused = true;
        }
    }
}

bool activeAccel(Player player, Controls controls)
{
    return (
        player.controlByAI == false &&
        (
            (player.useJoystick == true && sf::Joystick::isButtonPressed(player.joystickId, controls.ACCEL)) ||
            (player.useJoystick == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        )
    ); 
}

void collideItems(Player * collectorPlayer, std::vector<s_Item> * items)
{
    for (std::size_t itemIndex = 0; itemIndex < items->size(); ++itemIndex) {
        if (items->at(itemIndex).isCollected == true) {
            continue;
        }

        sf::FloatRect playerBoundingBox = collectorPlayer->sprite.getGlobalBounds();
        sf::FloatRect itemBoundingBox   = items->at(itemIndex).sprite.getGlobalBounds();

        if (playerBoundingBox.intersects(itemBoundingBox)) {
            std::cout << "COLLIDE ITEM " << itemIndex << std::endl;

            items->at(itemIndex).isCollected = true;
            collectorPlayer->collectedItems++;
            break;
        }
    }
}

void collideBetweenPlayers(Player * collectorPlayer, Player * defenderPlayer)
{
    sf::FloatRect collectorPlayerBoundingBox = collectorPlayer->sprite.getGlobalBounds();
    sf::FloatRect defenderPlayerBoundingBox  = defenderPlayer->sprite.getGlobalBounds();

    if (collectorPlayerBoundingBox.intersects(defenderPlayerBoundingBox)) {
        collectorPlayer->hasLost = true;
        std::cout << "PLAYER 2 WINS!" << std::endl;
    }
}

void movePlayer(Player * player, Game game, Controls controls)
{
    sf::Vector2f playerPosition = player->sprite.getPosition();

    // if (player->controlByAI == true) {
    //     if (player->aiPrediction.activeStrategy == true) {
    //         std::cout << "nextCircuit: " << player->aiPrediction.nextCircuit << " - internal: " << player->aiPrediction.nextCircuitIsInternal << " - external: " << player->aiPrediction.nextCircuitIsExternal << std::endl;
    //     } else {
    //         std::cout << "no strategy" << std::endl;
    //     }
    // }

    if (activeAccel(* player, controls) == true) {
        player->accel = 2.f;
    } else {
        player->accel = 1;
    }

    if (player->movingFromCircuit == true) {
        player->frameStartCircuitMove = player->frameStartCircuitMove + 1;

        if (player->frameStartCircuitMove > 15) {
            player->movingFromCircuit     = false;
            player->frameStartCircuitMove = 0;
        }
    }

    bool playerInHorizontalOpen;
    if (
        playerPosition.x >= (415.f + (player->width / 2)) &&
        playerPosition.x <= (415.f + 100.f - (player->width / 2))
    ) {
        playerInHorizontalOpen = true;
    } else {
        playerInHorizontalOpen = false;
    }

    bool playerInVerticalOpen;
    if (
        playerPosition.y >= (415.f + (player->height / 2)) &&
        playerPosition.y <= (415.f + 100.f - (player->height / 2))
    ) {
        playerInVerticalOpen = true;
    } else {
        playerInVerticalOpen = false;
    }

    bool playerCanGoToInternalCircuit;
    if (player->circuit >= 0.f && player->circuit <= 2.f) {
        playerCanGoToInternalCircuit = true;
    } else {
        playerCanGoToInternalCircuit = false;
    }

    bool playerCanGoToExternalCircuit;
    if (player->circuit >= 1.f && player->circuit <= 3.f) {
        playerCanGoToExternalCircuit = true;
    } else {
        playerCanGoToExternalCircuit = false;
    }

    // Player sprite in 0° angle (vertical)
    if (player->angle == 0.f) {
        bool doRotation = false;
        if (player->circuit == 0.f && playerPosition.y < 0) {   
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(100.f, 5.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(925.f - player->width, 5.f + player->height));
            }
        } else if (player->circuit == 1.f && playerPosition.y < 105) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(205.f, 110.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(820.f - player->width, 110.f + player->height));
            }
        } else if (player->circuit == 2.f && playerPosition.y < 210) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(310.f, 215.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(820.f - 110 - player->width, 110 + 110 + player->height));
            }
        } else if (player->circuit == 3.f && playerPosition.y < 315) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(415.f, 320.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(820.f - 110 - 110 - player->width, 110 + 110 + 110 + player->height));
            }
        } else {
            if (player->movingFromCircuit == false && playerInVerticalOpen == true) {
                if (
                    (
                        isRightDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsInternal == true)
                    )
                    &&
                    playerCanGoToInternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(105.f, 0.f));
                    } else {
                        player->sprite.move(sf::Vector2f(-105.f, 0.f));
                    }
                    player->circuit++;
                    player->movingFromCircuit = true;
                } else if (
                    (
                        isLeftDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsExternal == true)
                    )
                    &&
                    playerCanGoToExternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(-105.f, 0.f));
                    } else {
                        player->sprite.move(sf::Vector2f(105.f, 0.f));
                    }
                    player->circuit--;
                    player->movingFromCircuit = true;
                }
            }

            player->sprite.move(sf::Vector2f(0.f, -(player->accel * player->speed * game.speedFactor)));
        }

        if (doRotation == true) {
            if (player->leftToRight == true) {
                player->sprite.setRotation(90.f);
                player->angle = 90.f;
            } else {
                player->sprite.setRotation(270.f);
                player->angle = 270.f;
            }
        }
    }

    // Player sprite in 90° angle (horizontal)
    if (player->angle == 90.f) {
        bool doRotation = false;
        if (player->circuit == 0.f && playerPosition.x > 930) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(925.f, 105.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(925.f - player->width, 925.f - player->height));
            }
        } else if (player->circuit == 1.f && playerPosition.x > (930 - 100 - 5)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(820.f, 210.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(925 - player->width - 110, 925.f - 100 - player->height));
            }
        } else if (player->circuit == 2.f && playerPosition.x > (930 - 105 - 105)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(715.f, 315.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(925 - player->width - 110 - 110, 925.f - 100 - 110 - player->height));
            }
        } else if (player->circuit == 3.f && playerPosition.x > (930 - 105 - 105 - 105)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(610.f, 420.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(925 - player->width - 110 - 110 - 110, 925.f - 100 - 110 - 110 - player->height));
            }
        } else {   
            if (player->movingFromCircuit == false && playerInHorizontalOpen == true) {
                if (
                    (
                        isRightDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsInternal == true)
                    )
                    &&
                    playerCanGoToInternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(0.f, 105.f));
                    } else {
                        player->sprite.move(sf::Vector2f(0.f, -105.f));
                    }
                    player->circuit++;
                    player->movingFromCircuit = true;
                } else if (
                    (
                        isLeftDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsExternal == true)
                    )
                    &&
                    playerCanGoToExternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(0.f, -105.f));
                    } else {
                        player->sprite.move(sf::Vector2f(0.f, 105.f));
                    }
                    player->circuit--;
                    player->movingFromCircuit = true;
                }
            }

            player->sprite.move(sf::Vector2f(player->accel * player->speed * game.speedFactor, 0.f));
        }

        if (doRotation == true) {
            if (player->leftToRight == true) {
                player->sprite.setRotation(180.f);
                player->angle = 180.f;
            } else {
                player->sprite.setRotation(0.f);
                player->angle = 0.f;
            }
        }
    }

    // Player sprite in 180° angle (vertical)
    if (player->angle == 180.f) {
        bool doRotation = false;
        if (player->circuit == 0.f && playerPosition.y > 930) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(925.f - player->width, 925.f));
            } else {
                player->sprite.setPosition(sf::Vector2f(5.f + player->width, 925.f - player->height));
            }
        } else if (player->circuit == 1.f && playerPosition.y > (930 - 100 - 5)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(925.f - player->width - 110, 925.f - 100));
            } else {
                player->sprite.setPosition(sf::Vector2f(105.f + player->width, 925.f - 100 - player->height));
            }
        } else if (player->circuit == 2.f && playerPosition.y > (930 - 105 - 105)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(925.f - player->width - 110 - 100, 925.f - 100 - 110));
            } else {
                player->sprite.setPosition(sf::Vector2f(105.f + player->width + 110, 925.f - 100 - 110 - player->height));
            }
        } else if (player->circuit == 3.f && playerPosition.y > (930 - 105 - 105 - 105)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(925.f - player->width - 110 - 100 - 100, 925.f - 100 - 110 - 110));
            } else {
                player->sprite.setPosition(sf::Vector2f(105.f + player->width + 110 + 110, 925.f - 100 - 110 - 110 - player->height));
            }
        } else {
            if (player->movingFromCircuit == false && playerInVerticalOpen == true) {
                if (
                    (
                        isRightDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsInternal == true)
                    )
                    &&
                    playerCanGoToInternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(-105.f, 0.f));
                    } else {
                        player->sprite.move(sf::Vector2f(105.f, 0.f));
                    }
                    player->circuit++;
                    player->movingFromCircuit = true;
                } else if (
                    (
                        isLeftDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsExternal == true)
                    )   
                    &&
                    playerCanGoToExternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(105.f, 0.f));
                    } else {
                        player->sprite.move(sf::Vector2f(-105.f, 0.f));
                    }
                    player->circuit--;
                    player->movingFromCircuit = true;
                }
            }

            player->sprite.move(sf::Vector2f(0.f, player->accel * player->speed * game.speedFactor));
        }

        if (doRotation == true) {
            if (player->leftToRight == true) {
                player->sprite.setRotation(270.f);
                player->angle = 270.f;
            } else {
                player->sprite.setRotation(90.f);
                player->angle = 90.f;
            }
        }
    }

    // Player sprite in 270° angle (horizontal)
    if (player->angle == 270.f) {
        bool doRotation = false;
        if (player->circuit == 0.f && playerPosition.x < 0) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(5.f, 925.f - player->height));
            } else {
                player->sprite.setPosition(sf::Vector2f(5.f + player->width, 5.f + player->height));
            }
        } else if (player->circuit == 1.f && playerPosition.x < 105) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(105, 925.f - player->height - 110));
            } else {
                player->sprite.setPosition(sf::Vector2f(105 + player->width, 105 + player->height));
            }
        } else if (player->circuit == 2.f && playerPosition.x < (105 + 105)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(210, 925.f - player->height - 110 - 100));
            } else {
                player->sprite.setPosition(sf::Vector2f(105 + 110 + player->width, 105 + 110 + player->height));
            }
        } else if (player->circuit == 3.f && playerPosition.x < (105 + 105 + 105)) {
            doRotation = true;
            if (player->leftToRight == true) {
                player->sprite.setPosition(sf::Vector2f(315, 925.f - player->height - 110 - 100 - 100));
            } else {
                player->sprite.setPosition(sf::Vector2f(105 + 110 + 110 + player->width, 105 + 110 + 110 + player->height));
            }
        } else {
            if (player->movingFromCircuit == false && playerInHorizontalOpen == true) {
                if (
                    (
                        isRightDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsInternal == true)
                    )   
                    &&
                    playerCanGoToInternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(0.f, -105.f));
                    } else {
                        player->sprite.move(sf::Vector2f(0.f, 105.f));
                    }
                    player->circuit++;
                    player->movingFromCircuit = true;
                } else if (
                    (
                        isLeftDirectionPressed(* player, controls) ||
                        (player->controlByAI == true && player->aiPrediction.activeStrategy == true && player->aiPrediction.nextCircuitIsExternal == true)
                    ) 
                    &&
                    playerCanGoToExternalCircuit == true
                ) {
                    if (player->leftToRight == true) {
                        player->sprite.move(sf::Vector2f(0.f, 105.f));
                    } else {
                        player->sprite.move(sf::Vector2f(0.f, -105.f));
                    }
                    player->circuit--;
                    player->movingFromCircuit = true;
                }
            }

            player->sprite.move(sf::Vector2f(-(player->accel * player->speed * game.speedFactor), 0.f));
        }

        if (doRotation == true) {
            if (player->leftToRight == true) {
                player->sprite.setRotation(0.f);
                player->angle = 0.f;
            } else {
                player->sprite.setRotation(180.f);
                player->angle = 180.f;
            }
        }
    }

    playerPosition = player->sprite.getPosition();
    player->posX   = playerPosition.x;
    player->posY   = playerPosition.y;
}

void defenderAiEngine(Player * collectorPlayer, Player * defenderPlayer)
{
    if (collectorPlayer->circuit != defenderPlayer->circuit) {
        defenderPlayer->aiPrediction.activeStrategy = true;

        if (collectorPlayer->circuit > defenderPlayer->circuit) {
            // std::cout << "next move is internal" << std::endl;
            defenderPlayer->aiPrediction.nextCircuit           = defenderPlayer->circuit + 1;
            defenderPlayer->aiPrediction.nextCircuitIsInternal = true;
            defenderPlayer->aiPrediction.nextCircuitIsExternal = false; 
        } else {
            // std::cout << "next move is external" << std::endl;
            defenderPlayer->aiPrediction.nextCircuit           = defenderPlayer->circuit - 1;
            defenderPlayer->aiPrediction.nextCircuitIsInternal = false;
            defenderPlayer->aiPrediction.nextCircuitIsExternal = true; 
        }
    } else {
        defenderPlayer->aiPrediction.activeStrategy = false;
    }
}


int main() 
{
    // Config
    struct s_Game game;
    game.speedFactor  = 6;
    game.screenHeight = 930.f;
    game.screenWidth  = 930.f;
    game.isPaused     = true;

    struct s_Map map;
    map.internalPadding     = 5.f;
    map.circuitWidth        = 100.f;
    map.circuitSideWidth    = 5.f;
    map.circuitZeroSideSize = 315.f;
    map.circuitOneSideSize  = 210.f;
    map.circuitTwoSideSize  = 105.f;


    // Create the window
    sf::RenderWindow window(sf::VideoMode(game.screenWidth, game.screenHeight), "Dodge'em");
    window.setFramerateLimit(60);


    // Controller
    bool useJoystick = false;
    unsigned int joystickId;
    for (int joystickIndex = 0; joystickIndex <= 8; joystickIndex++) {
        unsigned int joystickIsConnected;
        if (sf::Joystick::isConnected(joystickIndex))
        {
            joystickId   = joystickIndex;
            useJoystick = true;

            break;
        }
    }

    struct s_Controls controls;
    if (useJoystick == true) {
        controls.ACCEL = 1;
        controls.START = 9;
    }

    struct s_ControlsEvents controlsEvents;
    controlsEvents.joystickButtonReleased = -1;

    sf::Font font;
    if (!font.loadFromFile("fonts/Raleway-Regular.ttf"))
    {
        // erreur...
    }


    // Player 1 init
    struct s_Player player1;
    if (!player1.texture.loadFromFile("gfx/player1.png"))
    {
        // erreur...
    }
    player1.sprite.setTexture(player1.texture);
    initPlayer1(&player1, map, true, useJoystick, joystickId, true);
    //initPlayer1(&player1, map, true, false, 0);


    // Player 2 init
    struct s_Player player2;
    if (!player2.texture.loadFromFile("gfx/player2.png"))
    {
        // erreur...
    }
    player2.sprite.setTexture(player2.texture);
    //initPlayer2(&player2, map, true, useJoystick, joystickId);
    initPlayer2(&player2, map, false, false, 0);

    std::vector<s_Item> items;
    initItems(&items);

    while (window.isOpen())
    {
        if (player1.useJoystick == true || player2.useJoystick == true) {
            sf::Joystick::update();
        }

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::JoystickButtonReleased)
            {
                controlsEvents.joystickButtonReleased = event.joystickButton.button;
                std::cout << "joystick button released!" << std::endl;
                std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
                std::cout << "button: " << event.joystickButton.button << std::endl;
            }

            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code == sf::Keyboard::Enter) {
                    if (player1.hasLost == false) {
                        controlsEvents.keyReleased = event.key;
                        checkPauseControl(&game, player1, player2, controls, controlsEvents);
                    } else {
                        initPlayer1(&player1, map, true, useJoystick, joystickId, false);
                        initPlayer2(&player2, map, false, false, 0);
                        initItems(&items);
                        game.isPaused = true;
                    }
                }
            }
        }
        
        if (game.isPaused == false && player1.hasLost == false) {
            collideItems(&player1, &items);
            collideBetweenPlayers(&player1, &player2);

            if (player2.controlByAI == true) {
                defenderAiEngine(&player1, &player2);
            }

            movePlayer(&player1, game, controls);
            movePlayer(&player2, game, controls);
        } 

        window.clear();
        
        drawMap(&window, map);
        drawItems(&window, items);
        window.draw(player1.sprite);
        window.draw(player2.sprite);

        if (player1.hasLost == true) {
            sf::Text player2WinsText;
            player2WinsText.setFont(font);
            player2WinsText.setString("Player 2 Wins!");
            player2WinsText.setCharacterSize(60);
            player2WinsText.setFillColor(sf::Color::Red);
            player2WinsText.setPosition(sf::Vector2f(280, 400));

            window.draw(player2WinsText);
        }

        window.display();
    }

    return 0;
}