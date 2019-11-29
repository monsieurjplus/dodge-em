#include <iostream>
#include <SFML/Graphics.hpp>
#include <stdint.h>

using namespace std;

typedef struct s_Game {
    uint8_t speedFactor;
    uint16_t screenHeight;
    uint16_t screenWidth;
} Game;

typedef struct s_Controls {
    uint8_t BUTTON_A;
    uint8_t BUTTON_B;
    uint8_t BUTTON_ACCEL;
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

    bool controlByAI;
    AiPrediction aiPrediction;
} Player;


void initPlayer1(Player * player, Map map, bool isHuman, bool useJoystick, uint8_t joystickId)
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
    } else {
        player->controlByAI = true;
        struct s_AiPrediction playerAiPrediction;
        playerAiPrediction.activeStrategy = false;
        player->aiPrediction              = playerAiPrediction;
    }

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

    player->sprite.setPosition(sf::Vector2f(player->posX, player->posY));
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

bool isButtonAPressed(Player player, Controls controls)
{
    return (
        player.controlByAI == false &&
        (
            (player.useJoystick == true && sf::Joystick::isButtonPressed(player.joystickId, controls.BUTTON_A)) ||
            (player.useJoystick == false && sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        )
    );
}

bool isButtonBPressed(Player player, Controls controls)
{
    return (
        player.controlByAI == false &&
        (
            (player.useJoystick == true && sf::Joystick::isButtonPressed(player.joystickId, controls.BUTTON_B)) ||
            (player.useJoystick == false && sf::Keyboard::isKeyPressed(sf::Keyboard::B))
        )
    );
}

bool activeAccel(Player player, Controls controls)
{
    return (
        player.controlByAI == false &&
        (
            (player.useJoystick == true && sf::Joystick::isButtonPressed(player.joystickId, controls.BUTTON_ACCEL)) ||
            (player.useJoystick == false && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        )
    ); 
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
        player->accel = 1.5f;
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

    // if (player->controlByAI == true && (playerInHorizontalOpen == true || playerInVerticalOpen == true)) {
    //     std::cout << "horizontal: " << playerInHorizontalOpen << " - vertical: " << playerInVerticalOpen << std::endl;
    // }

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
                        isButtonAPressed(* player, controls) ||
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
                        isButtonBPressed(* player, controls) ||
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
                        isButtonAPressed(* player, controls) ||
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
                        isButtonBPressed(* player, controls) ||
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
                        isButtonAPressed(* player, controls) ||
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
                        isButtonBPressed(* player, controls) ||
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
                        isButtonAPressed(* player, controls) ||
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
                        isButtonBPressed(* player, controls) ||
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

    struct s_Map map;
    map.internalPadding     = 5.f;
    map.circuitWidth        = 100.f;
    map.circuitSideWidth    = 5.f;
    map.circuitZeroSideSize = 315.f;
    map.circuitOneSideSize  = 210.f;
    map.circuitTwoSideSize  = 105.f;


    // Create the window
    sf::RenderWindow window(sf::VideoMode(game.screenWidth, game.screenHeight), "SFML works!");
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
        controls.BUTTON_A     = 1;
        controls.BUTTON_B     = 0;
        controls.BUTTON_ACCEL = 2;
    }



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
    initPlayer1(&player1, map, true, useJoystick, joystickId);
    //initPlayer1(&player1, map, false, useJoystick, joystickId);


    // Player 2 init
    struct s_Player player2;
    if (!player2.texture.loadFromFile("gfx/player2.png"))
    {
        // erreur...
    }
    player2.sprite.setTexture(player2.texture);
    initPlayer2(&player2, map, false, false, 0);
    //initPlayer2(&player2, map, true, false, 0);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (player2.controlByAI == true) {
            defenderAiEngine(&player1, &player2);
        }

        movePlayer(&player1, game, controls);
        movePlayer(&player2, game, controls);

        window.clear();
        window.draw(player1.sprite);
        window.draw(player2.sprite);

        drawMap(&window, map);

        window.display();
    }

    return 0;
}