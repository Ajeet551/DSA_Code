
#if UML_CLASS_DIAGRAM
+----------------+                  
|    Frame       |                  
+----------------+
| - rolls: vector<int>
+----------------+
| + addRoll(pins: int): void
| + isStrike(): bool
| + isSpare(): bool
| + getRoll(index: int): int
| + getRollCount(): int
| + getScore(): int
+----------------+

+----------------+
|    Player      |
+----------------+
| - name: string
| - frames: vector<Frame>
+----------------+
| + Player(name: string)
| + addFrame(frame: Frame): void
| + calculateScore(): int
| + getName(): string
+----------------+

+----------------+
|  BowlingGame   |
+----------------+
| - players: vector<Player>
+----------------+
| + addPlayer(player: Player): void
| + printScores(): void
+----------------+
#endif

// BowlingGame.h
#pragma once
#include <vector>
#include <stdexcept>
#include <string>
using namespace std;

/* Frame Class */
class Frame {
private:
    vector<int> rolls;

public:
    void addRoll(int pins);
    bool isStrike() const;
    bool isSpare() const;
    int getRoll(int index) const;
    int getRollCount() const;
    int getScore() const;
};

/* Player Class */
class Player {
private:
    string name;
    vector<Frame> frames;

public:
    Player(const string& name);
    void addFrame(const Frame& frame);
    int calculateScore() const;
    const string& getName() const;
};

/* Bowling Game Class */
class BowlingGame {
private:
    vector<Player> players;

public:
    void addPlayer(const Player& player);
    void printScores() const;
};


