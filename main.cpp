//Brendon So 2024
#include "Sokoban.hpp"

int main(int argc, char* argv[]) {
    sf::Vector2u testWindow(0, 0);
    Sokoban game(testWindow, "resources/map.txt");
    std::ifstream file(game.getFile());
    file >> game;
    Sokoban savedGame = game;
    file.close();

    sf::RenderWindow window(sf::VideoMode(game.width() * TS, (game.height()+1) * TS), "Sokoban");
    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("resources/Tiny5.ttf")) {
    std::cout << "open font error";
    }
    sf::Text text;
    text.setFont(font);
    game.setText(text);

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (!game.isWon()) {
                    game.setCompletion();
                    switch (event.key.code) {
                        case sf::Keyboard::V:
                            clock.restart();
                            game = savedGame;
                            game.setText(text); 
                            break;
                        case sf::Keyboard::Up:
                            game.movePlayer(Up);
                            break;
                        case sf::Keyboard::Left:
                            game.movePlayer(Left);
                            break;
                        case sf::Keyboard::Down:
                            game.movePlayer(Down);
                            break;
                        case sf::Keyboard::Right:
                            game.movePlayer(Right);
                            break;
                        case sf::Keyboard::R:
                            game.movePlayer(Back);
                            break;
                        case sf::Keyboard::E:
                            game.movePlayer(Drag);
                            break;
                        default: break;
                    }
                }
                if (game.isWon()) {
                    switch (event.key.code) {
                        case sf::Keyboard::N: {
                            if (game.getRecord() > game.getCompletion() || game.getRecord() == 0) {
                                game.setRecord(game.getCompletion());
                            }
                            float record = game.getRecord();
                            float seed = game.getCompletion();
                            game = savedGame;
                            game.setRecord(record);
                            game.setText(text);
                            game.random(seed);
                            savedGame = game;
                            clock.restart();
                            break;
                        }
                        case sf::Keyboard::T: {
                            if (game.getRecord() > game.getCompletion() || game.getRecord() == 0) {
                                game.setRecord(game.getCompletion());
                            }
                            float record = game.getRecord();
                            game = savedGame;
                            game.setRecord(record);
                            game.setText(text);
                            clock.restart();
                            break;
                        }
                        default: 
                            break;
                    }
                }
            }
        }
        sf::Time timer = clock.getElapsedTime();
        game.setTime(timer.asSeconds());

        window.clear();
        window.draw(game);
        window.display();
        
    }
}
