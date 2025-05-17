// BowlingGameTest.cpp
#include "BowlingGame.cpp"
#include "BowlingGame.h"
#include <cassert>
#include <iostream>
#include <utility>

void testPerfectGame() {
    Player p("Perfect");

    // Add 9 strike frames
    for (int i = 0; i < 9; ++i) {
        Frame f;
        f.addRoll(10);
        p.addFrame(f);
    }

    // 10th frame + 2 bonus rolls inside same frame
    Frame last;
    last.addRoll(10);  // 10th frame strike
    last.addRoll(10);  // bonus roll 1
    last.addRoll(10);  // bonus roll 2
    p.addFrame(last);

    assert(p.calculateScore() == 300);
}

void testAllSpares() {
    Player p("Spares");

    // First 9 frames: all spares
    for (int i = 0; i < 9; ++i) {
        Frame f;
        f.addRoll(5);
        f.addRoll(5);
        p.addFrame(f);
    }

    // 10th frame + 1 bonus roll
    Frame last;
    last.addRoll(5);
    last.addRoll(5);
    last.addRoll(5); // bonus
    p.addFrame(last);

    assert(p.calculateScore() == 150);
}

void testNormalGame() {
    Player p("Normal");
    vector<pair<int, int>> rolls = {
        {1,4}, {4,5}, {6,3}, {5,3}, {3,3}, {4,4}, {2,6}, {2,7}, {1,8}, {0,9}
    };
    for (auto& pair : rolls) {
        Frame f;
        f.addRoll(pair.first);
        f.addRoll(pair.second);
        p.addFrame(f);
    }
    assert(p.calculateScore() == 80);
}

int main() {
    try {
        testPerfectGame();
        testAllSpares();
        testNormalGame();
        cout << "All test cases passed successfully!" << endl;
    } catch (const exception& ex) {
        cerr << "Test failed: " << ex.what() << endl;
        return 1;
    }
    return 0;
}

