// BowlingGame.cpp
#include "BowlingGame.h"
#include <iostream>

void Frame::addRoll(int pins) {
    if (pins < 0 || pins > 10)
        throw std::invalid_argument("Invalid pin count");

    // Allow 3 rolls only in the final frame (handled by Player logic)
    if (rolls.size() >= 3)
        throw std::logic_error("Cannot add more than 3 rolls to a frame");

    rolls.push_back(pins);
}

bool Frame::isStrike() const {
    return !rolls.empty() && rolls[0] == 10;
}

bool Frame::isSpare() const {
    return rolls.size() >= 2 && (rolls[0] + rolls[1] == 10);
}

int Frame::getRoll(int index) const {
    if (index < 0 || index >= (int)rolls.size())
        return 0;
    return rolls[index];
}

int Frame::getRollCount() const {
    return (int)rolls.size();
}

int Frame::getScore() const {
    int sum = 0;
    for (int roll : rolls)
        sum += roll;
    return sum;
}

Player::Player(const string& name) : name(name) {}

void Player::addFrame(const Frame& frame) {
    // Allow bonus frames beyond 10th if 10th frame is strike/spare
    if (frames.size() < 10) {
        frames.push_back(frame);
    } else if (frames.size() == 10) {
        // Allow 11th frame if 10th is strike/spare
        if (frames[9].isStrike() || frames[9].isSpare())
            frames.push_back(frame);
        else
            throw logic_error("Cannot add bonus frame without strike or spare in 10th");
    } else if (frames.size() == 11) {
        // Only allow 12th if 10th was strike
        if (frames[9].isStrike())
            frames.push_back(frame);
        else
            throw logic_error("Only one bonus roll allowed after spare in 10th");
    } else {
        throw logic_error("Cannot have more than 12 frames total");
    }
}

int Player::calculateScore() const {
    int score = 0;
    for (size_t i = 0; i < frames.size(); ++i) {
        const Frame& f = frames[i];
        score += f.getScore();

        if (f.isStrike()) {
            if (i + 1 < frames.size()) {
                score += frames[i + 1].getRoll(0);
                if (frames[i + 1].isStrike() && i + 2 < frames.size())
                    score += frames[i + 2].getRoll(0);
                else
                    score += frames[i + 1].getRoll(1);
            }
        } else if (f.isSpare()) {
            if (i + 1 < frames.size())
                score += frames[i + 1].getRoll(0);
        }
    }
    return score;
}

const string& Player::getName() const {
    return name;
}

void BowlingGame::addPlayer(const Player& player) {
    players.push_back(player);
}

void BowlingGame::printScores() const {
    for (const Player& p : players) {
        cout << "Player: " << p.getName() << ", Score: " << p.calculateScore() << endl;
    }
}

