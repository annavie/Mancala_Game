#ifndef BOARDCONSTANTS_H
#define BOARDCONSTANTS_H

namespace BoardConstants {
    constexpr int kTotalPositions = 14;
    constexpr int kPlayablePits = 12;  // Number of pits that are playable (excluding the stores)

    constexpr int kPitsPerPlayer = 6;
    constexpr int kPlayer1StoreIndex = 12;
    constexpr int kPlayer2StoreIndex = 13;
    constexpr int kMaxPitIndex = kPlayablePits - 1;
}

#endif // BOARDCONSTANTS_H
