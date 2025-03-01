#ifndef CONSTANTS_H
#define CONSTANTS_H

namespace Constants {
    constexpr int kTotalPits = 12;       // Total number of pits on the board
    constexpr int kPitsPerPlayer = 6;      // Number of pits per player

    constexpr int kPlayer2PitsRow = 0;
    constexpr int kPlayer1PitsRow = 2;
    
    constexpr int kPlayer2StoreColumn = 0;             // Left-most column for player 2 store
    constexpr int kPlayer1StoreColumn = kPitsPerPlayer + 1; // Right column for player 1 store (7)

    // UI styling constants
    constexpr int kMenuSpacing = 20;
    constexpr int kTitleFontSize = 24;
    constexpr int kStoreFontSize = 18;
    constexpr int kPitFontSize = 20;
    constexpr int kPitBorderRadius = 40;
}

#endif // CONSTANTS_H
