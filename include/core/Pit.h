#ifndef PIT_H
#define PIT_H

class Pit {
private:
    int stones;

public:
    Pit(int initialStones = 4) : stones(initialStones) {}

    int getStones() const { return stones; }
    void setStones(int count) { stones = count; }
    void addStones(int count) { stones += count; }
    int removeStones() { int temp = stones; stones = 0; return temp; }
};

#endif // PIT_H
