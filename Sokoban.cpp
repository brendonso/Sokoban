#include "Sokoban.hpp"

Sokoban::Sokoban(sf::Vector2u windowSize, std::string newFile)
    : wSize(windowSize), filename(newFile) {
    Wall.loadFromFile("resources/block.png");
    Box.loadFromFile("resources/crate_03.png");
    Empty.loadFromFile("resources/ground_01.png");
    Storage.loadFromFile("resources/ground_04.png");
    playerFront.loadFromFile("resources/Front.png");
    playerBack.loadFromFile("resources/Back.png");
    greenBox.loadFromFile("resources/crate_green.png");
    playerRight.loadFromFile("resources/Right.png");
    playerLeft.loadFromFile("resources/Left.png");
    caution.loadFromFile("resources/Left.png");
    other.loadFromFile("resources/ground_01.png");
}

sf::Texture Sokoban::checkPhoto(char type) {
    switch (type) {
        case '#': return Wall;
        case '.': return other;
        case 'a': 
            value += 1;
            return Storage;
        case 'A': return Box;
        case '@': return playerFront;
        default: return other;
    }
}

void Sokoban::setData(char newData, sf::Texture photo) {
    grid.push_back(std::make_pair(newData, photo));
}

void Sokoban::random(float seed) {
    std::srand(static_cast<unsigned int>(seed * 1000));
    size_t newPos;


    for (size_t i = 0; i < grid.size(); ++i) {
        if (grid[i].first == 'A') { 
        newPos = static_cast<size_t>(std::rand() % grid.size());
            if(grid[newPos].first != '#' && grid[newPos].first != 'A' && grid[newPos].first != 'a') {
                grid[i].first = '.';
                grid[i].second = Empty; //cleared
                grid[newPos].first = 'A';
                grid[newPos].second = Box;
            }
        }
        if (grid[i].first == 'a') { 
        newPos = static_cast<size_t>(std::rand() % grid.size());
            if(grid[newPos].first != '#' && grid[newPos].first != 'A' && grid[newPos].first != 'a') {
                grid[i].first = '.';
                grid[i].second = Empty; //cleared
                grid[newPos].first = 'a';
                grid[newPos].second = Storage;
            }
        }
    }
    for (size_t i = 0; i < grid.size(); ++i) {
        if (grid[i].first == '@') {
            grid[i].first = '.';
            grid[i].second = Empty;
            break;
        }
    }
    
    do {
        newPos = static_cast<size_t>(std::rand() % grid.size());
    } while (grid[newPos].first == '#' || grid[newPos].first == 'A' || grid[newPos].first == 'a');
    grid[newPos].first = '@';
    grid[newPos].second = playerFront;
}



std::istream& operator>>(std::istream& in, Sokoban& info) {
    in >> info.h >> info.wof;
    info.setwSize({info.h, info.wof});
    
    char data;
    for (unsigned int i = 0; i < info.h * info.wof; i++) {
        in >> data;
        sf::Texture photo = info.checkPhoto(data);
        info.setData(data, photo);
    }
    return in;
}

void Sokoban::save(size_t playerIndex, size_t lastDirection) {
    prev.playerIndex = playerIndex;
    prev.lastDirection = lastDirection;
    prev.grid = grid;
    prev.wins = wins;
    prev.value = value;
    Logs.push(prev); 
}

void Sokoban::moveBack() {
    if (!Logs.empty()) {
        prevLogs prev = Logs.top(); //recieves data
        Logs.pop();

        grid = prev.grid;
        wins = prev.wins;
        value = prev.value;
    }
}


void Sokoban::draw(sf::RenderTarget& window, sf::RenderStates states) const {
    size_t width = wof;
    size_t row = 0;
    size_t col = 0;

    for (size_t i = 0; i < grid.size(); i++) {
        const auto& data = grid[i];
        if (col >= width) {
            col = 0;
            row++;
        }

        sf::Sprite sprite;

        if (data.first == 'A' || data.first == '@') {
            sf::Sprite background;
            background.setTexture(Empty);
            background.setPosition(64 * col, 64 * row);
            window.draw(background, states);
        }
        sprite.setTexture(data.second);
        sprite.setPosition(64 * col, 64 * row);
        window.draw(sprite, states);
        col++;
    }
    
    sf::Text stats = text;
    sf::Text Controls = text;
    stats.setCharacterSize(25);
    Controls.setCharacterSize(20);


    if(value != wins) {
    stats.setString("Crates: " + std::to_string(wins) + " | " + std::to_string(value) + "    |    Timer: " + std::to_string(time) + "    |    Record: " + std::to_string(record));
    Controls.setString("WASD = Movement     R = Backwards     E = Drag Box     V = Restart");
    } else if (value == wins) {
        stats.setString("You completed in " + std::to_string(completionTime) + " seconds.");
        Controls.setString("N = New Map      T = Try same map");
    }
    
    stats.setPosition(3*64, (row + 1) * 64);
    Controls.setPosition(3*64, (row + 1.5) * 64);
    window.draw(Controls);
    window.draw(stats);
}

void Sokoban::movePlayer(Direction direction) {
    size_t width = wof;
    size_t height = h;

    for (size_t i = 0; i < grid.size(); ++i) {
        if (grid[i].first == '@') {
            size_t row = i / width;
            size_t col = i % width;

            size_t nextIndex = 0;
            size_t nextNextIndex = 0;

            switch (direction) {
                case Up:
                    if (row > 0) {
                        grid[i].second  = playerBack;
                        nextIndex = (row - 1) * width + col;
                        nextNextIndex = (row - 2) * width + col;
                    }
                    save(i, nextNextIndex);
                    break;
                case Down:
                    if (row < height - 1) {
                        grid[i].second  = playerFront;
                        nextIndex = (row + 1) * width + col;
                        nextNextIndex = (row + 2) * width + col;
                    }
                    save(i, nextNextIndex);
                    break;
                case Right:
                    if (col < width - 1) {
                        grid[i].second = playerRight;
                        nextIndex = row * width + (col + 1);
                        nextNextIndex = row * width + (col + 2);
                    }
                    save(i, nextNextIndex);
                    break;
                case Left:
                    if (col > 0) {
                        grid[i].second = playerLeft;
                        nextIndex = row * width + (col - 1);
                        nextNextIndex = row * width + (col - 2);
                    }
                    save(i, nextNextIndex);
                    break;
                case Drag: {
                    size_t boxIndex = prev.lastDirection;
                    size_t previousPlayerIndex = prev.playerIndex;
                    if (grid[boxIndex].first != '.' && grid[boxIndex].first != '#' && grid[boxIndex].first != 'a') {
                    grid[boxIndex].first = '.';
                    grid[boxIndex].second = Empty;
                    grid[i].first = 'A';

                    grid[previousPlayerIndex].first = '@';
                    grid[previousPlayerIndex].second = grid[i].second;
                    grid[i].second = Box;
                    }
                    break; 
                }
                case Back:
                if (!Logs.empty()) {
                    moveBack();
                }
                break; 
            }

            auto& curr = grid[i];
            auto& next = grid[nextIndex];
            auto& nextNext = grid[nextNextIndex]; 

            if (next.first != '#' && next.first != 'a') { 
                if (next.first == 'A') {
                    if (nextNext.first == '#' || nextNext.first == 'A') {
                        return;
                    }

                    if (nextNext.first == 'a') {
                        next.first = '#';
                        next.second = greenBox;
                        wins += 1;
                    }
                    nextNext = next;
                }
                next = curr;
                curr.first = '.';
                curr.second = other;
            }
            break;
        }
    }
}

