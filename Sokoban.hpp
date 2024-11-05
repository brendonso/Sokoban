#pragma once

#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <utility>
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

const unsigned int TS = 64;

enum Direction {
    Up,
    Down = 2,
    Left = 3,
    Right = 4,
    Back = 5,
    Drag = 6
};

class Sokoban : public sf::Drawable {
public:
    Sokoban() : wSize{0, 0}, filename{"resources/map.txt"} {}
    Sokoban(sf::Vector2u windowSize, std::string newFile);

    void update(sf::Time dt);
    void movePlayer(Direction WASD);
    void moveBack();
    void dragBack();
    void random(float seed);

    void setText(sf::Text newText) { text = newText; }
    void setRecord(float newRecord) { record = newRecord; }
    void setTime(float newTime) { time = newTime; }
    void setCompletion() { completionTime = time; }
    void setwSize(sf::Vector2u windowSize) { wSize = windowSize; }
    void setX(double newX) { h = newX; }
    void setY(double newY) { wof = newY; }
    void setData(char newData, sf::Texture photo);
    void setReset() { value = 0; }

    unsigned int getX() const { return h; }
    unsigned int getY() const { return wof; }
    std::string getFile() const { return filename; }
    unsigned int width() const { return wof; }
    unsigned int height() const { return h; }
    float getRecord() const { return record; }
    float getCompletion() const { return completionTime; }
    const bool isWon() const { return (value == wins); }
    std::vector<std::pair<char, sf::Texture>> getVector() const { return grid; }

    sf::Texture checkPhoto(char type);
    void save(size_t playerIndex, size_t lastDirection);

    friend std::istream& operator>>(std::istream& in, Sokoban& info);

protected:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    struct prevLogs {
        size_t playerIndex;
        size_t lastDirection;
        std::vector<std::pair<char, sf::Texture>> grid;
        int wins;
        int value;
    };

    sf::Vector2u wSize;
    unsigned int h;
    unsigned int wof;
    std::string filename;

    std::vector<std::pair<char, sf::Texture>> grid;
    std::stack<prevLogs> Logs;
    prevLogs prev;

    sf::Texture Wall;
    sf::Texture Box;
    sf::Texture Empty;
    sf::Texture Storage;
    sf::Texture playerFront;
    sf::Texture playerBack;
    sf::Texture playerRight;
    sf::Texture playerLeft;
    sf::Texture greenBox;
    sf::Texture caution;
    sf::Texture other;

    int wins = 0;
    int value = 0;
    float time = 0;
    float completionTime = 0;
    float record = 0;

    sf::Font font;
    sf::Text text;
};
