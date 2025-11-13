#pragma once
#include "../../Engine/GUI/BaseGUI.h"
#include "../GameClient.h"
#include "SudokuBoard.h"
#include "SudokuGenerator.h"
#include <vector>
#include "../GUIs/Entity/ClockCountDownLine.h"
#include "Effekseer/Effekseer.h"
enum TypeSudoku {
	NORMAL_SUDOKU,
	LEVEL_SUDOKU
};

class GUISudoku : public BaseGUI
{
public:
	GUISudoku(void);
	~GUISudoku(void);
public:
	void initGUI();
    void update(float dt) override;
    void newGame();
    void newGame(sudoku::Difficulty d);
	void newGameLevel();
    void onBackKey();
    void onButtonRelease(int buttonID, Touch* touch);
    sudoku::Difficulty curDiff;
    void showGUI(Node* parent /* = NULL */, bool hasFog /* = true */);
	void showGUIWithMode(TypeSudoku type);
    void onHint();

private:
	ClockCountDownLine* clock;
    BaseButton *btnBack, *btnSound, *btnSetting;
    sudoku::Board board_;
    bool notesMode_             = false;
    DrawNode* grid_         = nullptr;
    Node* numbersLayer_     = nullptr;
    Label* statusLabel_     = nullptr;
    LayerColor* selectRect_ = nullptr;
    MenuItemLabel* arrayMenuNumber[9];
    LayerColor* arrayBgSelect[9];
    LayerColor* arrayRelatedHighlight[27]; // 9 for row + 9 for column + 9 for 3x3 box
    Label* numberLabels_[9][9]; // Array to store reusable number labels
    BaseButton *btnErase, *btnNotes, *btnUndo, *btnSave, *btnLoad, *btnHint, *btnNewGame;
    BaseButton* arrayButtonNumber [9];
    int selR_ = -1, selC_ = -1;
    float cellSize;
    float boardSize;
    Vec2 origin;
    int lives_ = 3;
    Sprite* heartIcons_[3] = {nullptr, nullptr, nullptr};
    Label* timeLabel_ = nullptr;
    Label* bestTimeLabel_ = nullptr;
    float elapsedSeconds_ = 0.0f;
    int bestSeconds_ = -1; // -1 means no best yet
    bool isSolved_ = false;
    float timeSinceLastSave_ = 0.0f;

    struct Move
    {
        int r;
        int c;
        int prevValue;
        uint16_t prevNotes;
        int newValue;
        uint16_t newNotes;
        bool isNoteToggle;
    };
    std::vector<Move> undoStack_;

    
    void drawGrid();
    void redrawNumbers();
    void setSelected(int r, int c);
    void unSelect();
    void onDigit(int d);
    void onErase();
    void onToggleNotes();
    void onUndo();
    
    void onNewGame();
    void onSaveGame();
    void onLoadGame();
    Vec2 cellToPos(int r, int c, float cellSize, Vec2 origin);
    void selectNumber(int number);
    void highlightRelatedCells(int r, int c);
    void clearRelatedHighlights();
    void initHeartsUI();
    void updateHeartsUI();
    void loseLife();
    void playCellEffect(int r, int c, Color4B color);
    void showConflicts(int r, int c, int v);
    void saveToPrefs();
    bool loadFromPrefsIfAny();
    std::string serializeBoard() const;
    bool deserializeBoard(const std::string& data);
    void updateTimeLabels();
    static std::string formatTimeMMSS(int totalSeconds);
    void animateInitialNumbers();
    void initNumberLabels();
    void drawGridLines();
    void showGameOverDialog();
    void onContinueGame();
    void onEndGame();
    void onFinishGame();
    void runFinishGrayOut(const std::function<void()>& onComplete);
    void runWinSparkleThenResult(const std::function<void()>& onComplete);

    // --- First-time tutorial ---
    void startTutorialIfFirstTime();
    void beginTutorial();
    void advanceTutorial();
    void endTutorial();
    void positionPointerAtCell(int r, int c);
    void positionPointerAtNumber(int d);

    bool tutorialActive_ = false;
    int tutStep_ = 0; // 0: tap target cell, 1: tap number
    int tutTargetR_ = -1, tutTargetC_ = -1, tutTargetVal_ = 0;
    Sprite* tutPointer_ = nullptr;
    LayerColor* tutHighlight_ = nullptr;

	int bestLevel;
	int currentLevel;
	TypeSudoku typeGame;
	Text* labelStateLevel;
	void showString(string message);
	efk::EffectManager* manager;
	efk::EffectEmitter* emitter;
	efk::EffectEmitter* hitEffect;
};

