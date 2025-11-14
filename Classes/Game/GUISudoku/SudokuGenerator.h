// SudokuGenerator.h
#pragma once
#include "SudokuTypes.h"

namespace sudoku
{

enum class Difficulty
{
    EASY,
    MEDIUM,
    HARD,
    EXPERT
};

struct SudokuLevelConfig {
	int level;
	double difficultyNorm;
	int blankCells;
	int timeLimitSec;
};

class Generator
{
public:
    static Grid makeFull();                                     // filled valid board
    static Grid makePuzzle(Difficulty d = Difficulty::MEDIUM);  // unique-solution puzzle
	static Grid makePuzzleLevel(int level);  // unique-solution puzzle

	static SudokuLevelConfig getSudokuConfig(int L);   // unique-solution puzzle
private:
    static int removalsFor(Difficulty d);
};

}  // namespace sudoku
