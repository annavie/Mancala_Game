#ifndef AICONSTANTS_H
#define AICONSTANTS_H

namespace AIConstants {
    constexpr int kPitsPerPlayer = 6;
    constexpr int kTotalPits = 12;
    
    constexpr int kPlayer1Start = 0;
    constexpr int kPlayer1End = kPitsPerPlayer;   
    constexpr int kPlayer2Start = kPitsPerPlayer;   
    constexpr int kPlayer2End = kTotalPits;          

    constexpr int kStoreWeight = 10;
    constexpr int kBonusMultiplier = 20;
    constexpr int kOpponentAdvantagePenalty = 10;
}

#endif // AICONSTANTS_H
