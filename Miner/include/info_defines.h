#ifndef INFO_DEFINES_H
#define INFO_DEFINES_H

enum class GameType {
    Beginner,
    Medium,
    Expert
};

enum class GameStatus {
    NotStarted,
    Running,
    IsOver,
    Passed
 };

struct Presets {
    static const int BEGINNER_COL_COUNT = 9;
    static const int BEGINNER_ROW_COUNT = 9;
    static const int BEGINNER_MINE_COUNT = 10;

    static const int MEDIUM_COL_COUNT = 16;
    static const int MEDIUM_ROW_COUNT = 16;
    static const int MEDIUM_MINE_COUNT = 40;

    static const int EXPERT_COL_COUNT = 30;
    static const int EXPERT_ROW_COUNT = 16;
    static const int EXPERT_MINE_COUNT = 99;
};


#endif // INFO_DEFINES_H
