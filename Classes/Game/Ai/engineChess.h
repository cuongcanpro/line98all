/*
 * engine.h
 *
 *  Created on: 2012-10-27
 *      Author: thor
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#if defined(ANDROID_DEBUG)
#	include <android/log.h>
#	define DEBUG_LOG
#	define DEBUG_TRACE
#	define DEBUG_STATE
#endif

#include <string.h>
#include <vector>
#include <stdlib.h>

#include "zobrist.h"

#ifdef DEBUG_LOG
#	define LOG(x) __android_log_write( \
		ANDROID_LOG_DEBUG, "ChineseChess", x);
#	define LOG1(f,x) __android_log_print( \
		ANDROID_LOG_DEBUG, "ChineseChess", f, x);
#else
#	define LOG(x)
#	define LOG1(f,x)
#endif

#ifdef DEBUG_TRACE
#	define ENTER(x) LOG(x);
#else
#	define ENTER(x)
#endif

namespace chess {

static const int LIMIT_DEPTH = 64;    	// 最大的搜索深度
static const int HASH_SIZE = 1 << 20; 	// 置换表大小
static const int BOOK_SIZE = 16384;   	// 开局库大小
static const int MAX_MOVES = 256;     	// 最大的历史走法数
static const int MAX_GEN_MOVES = 128; 	// 最大的生成走法数
static const int MATE_VALUE = 10000;  	// 最高分值，即将死的分值
// 长将判负的分值，低于该值将不写入置换表
static const int BAN_VALUE = MATE_VALUE - 100;
// 搜索出胜负的分值界限，超出此值就说明已经搜索出杀棋了
static const int WIN_VALUE = MATE_VALUE - 200;
static const int DRAW_VALUE = 20;     	// 和棋时返回的分数(取负值)
static const int ADVANCED_VALUE = 3;  	// 先行权分值
static const int RANDOM_MASK = 7;     	// 随机性分值
static const int NULL_MARGIN = 400;   	// 空步裁剪的子力边界
static const int NULL_DEPTH = 2;      	// 空步裁剪的裁剪深度
static const int HASH_ALPHA = 1;      	// ALPHA节点的置换表项
static const int HASH_BETA = 2;       	// BETA节点的置换表项
static const int HASH_PV = 3;         	// PV节点的置换表项

typedef unsigned char byte;
typedef unsigned short uint16;
typedef unsigned int uint32;
typedef short int16;
typedef int int32;

template <class T>
inline T* begin_ptr(std::vector<T>& v)
{return  v.empty() ? NULL : &v[0];}

template <class T>
inline const T* begin_ptr(const std::vector<T>& v)
{return  v.empty() ? NULL : &v[0];}

template <class T>
inline T* end_ptr(std::vector<T>& v)
{return v.empty() ? NULL : (begin_ptr(v) + v.size());}

template <class T>
inline const T* end_ptr(const std::vector<T>& v)
{return v.empty() ? NULL : (begin_ptr(v) + v.size());}


// 历史走法信息(占4字节)
typedef struct MoveStruct {
	uint16 wmv;
	byte ucpcCaptured;
	byte ucbCheck;
	uint32 dwKey;
	inline void set(int mv, int pcCaptured, bool bCheck, uint32 dwKey) {
		wmv = mv;
		ucpcCaptured = pcCaptured;
		ucbCheck = bCheck;
		this->dwKey = dwKey;
	}
} MoveStruct;

// 置换表项结构
typedef struct HashItem {
	byte ucDepth, ucFlag;
	short svl;
	uint16 wmv, wReserved;
	uint32 dwLock0, dwLock1;
} HashItem;

// 开局库项结构
typedef struct BookItem {
	uint32 dwLock;
	uint16 wmv, wvl;
} BookItem;

// 与搜索有关的全局变量
typedef struct Search {
	int mvResult;                  		// 电脑走的棋
	int nHistoryTable[65536];      		// 历史表
	int mvKillers[LIMIT_DEPTH][2]; 		// 杀手走法表
	HashItem hashTable[HASH_SIZE]; 		// 置换表
	inline Search();
	inline void init();
} Search;

inline Search::Search() {
	init();
}
inline void Search::init() {
	mvResult = 0;
	memset(nHistoryTable, 0, 65536 * sizeof(int));       // 清空历史表
	memset(mvKillers, 0, LIMIT_DEPTH * 2 * sizeof(int)); // 清空杀手走法表
	memset(hashTable, 0, HASH_SIZE * sizeof(HashItem));  // 清空置换表
	LOG1("HashItem size: %d", sizeof(HashItem));
}

class EngineChess {
private:
	// 棋盘范围
	static const int RANK_TOP = 3;
	static const int RANK_BOTTOM = 12;
	static const int FILE_LEFT = 3;
	static const int FILE_RIGHT = 11;

private:
	// 静态辅助查找表
	///////////////////////////////////////////////////////////////////
	// 判断棋子是否在棋盘中的数组
	static const char ccInBoard[256];
	// 判断棋子是否在九宫的数组
	static const char ccInFort[256];
	// 判断步长是否符合特定走法的数组，1=帅(将)，2=仕(士)，3=相(象)
	static const char ccLegalSpan[512];
	// 根据步长判断马是否蹩腿的数组
	static const signed char ccKnightPin[512];
	// 棋盘初始设置
	static const byte cucpcStartup[256];
	static const byte cucpcStartup1[256];
	static const byte cucpcStartup2[256];
	static const byte cucpcStartup3[256];
	static const byte cucpcStartup4[256];
	static const byte cucpcStartup5[256];
	static const byte cucpcStartup6[256];
	static const byte cucpcStartup7[256];
	static const byte cucpcStartup8[256];
	static const byte cucpcStartup9[256];
	static const byte cucpcStartup10[256];
	static const byte cucpcStartup11[256];
	static const byte cucpcStartup12[256];
	static const byte cucpcStartup13[256];
	static const byte cucpcStartup14[256];
	static const byte cucpcStartup15[256];
	static const byte cucpcStartup16[256];
	static const byte cucpcStartup17[256];
	static const byte cucpcStartup18[256];
	static const byte cucpcStartup19[256];
	static const byte cucpcStartup20[256];
	static const byte cucpcStartup21[256];
	static const byte cucpcStartup22[256];
	static const byte cucpcStartup23[256];
	static const byte cucpcStartup24[256];
	static const byte cucpcStartup25[256];
	static const byte cucpcStartup26[256];
	static const byte cucpcStartup27[256];
	static const byte cucpcStartup28[256];
	static const byte cucpcStartup29[256];
	static const byte cucpcStartup30[256];
	static const byte cucpcStartup31[256];
	static const byte cucpcStartup32[256];
	static const byte cucpcStartup33[256];
	static const byte cucpcStartup34[256];
	static const byte cucpcStartup35[256];
	static const byte cucpcStartup36[256];
	static const byte cucpcStartup37[256];
	static const byte cucpcStartup38[256];
	static const byte cucpcStartup39[256];
	static const byte cucpcStartup40[256];
	static const byte cucpcStartup41[256];
	static const byte cucpcStartup42[256];
	static const byte cucpcStartup43[256];
	static const byte cucpcStartup44[256];
	static const byte cucpcStartup45[256];
	static const byte cucpcStartup46[256];
	static const byte cucpcStartup47[256];
	static const byte cucpcStartup48[256];
	static const byte cucpcStartup49[256];
	static const byte cucpcStartup50[256];
	static const byte cucpcStartup51[256];
	static const byte cucpcStartup52[256];
	static const byte cucpcStartup53[256];
	static const byte cucpcStartup54[256];
	static const byte cucpcStartup55[256];
	static const byte cucpcStartup56[256];
	static const byte cucpcStartup57[256];
	static const byte cucpcStartup58[256];
	static const byte cucpcStartup59[256];
	static const byte cucpcStartup60[256];
	static const byte cucpcStartup61[256];
	static const byte cucpcStartup62[256];
	static const byte cucpcStartup63[256];
	static const byte cucpcStartup64[256];
	static const byte cucpcStartup65[256];
	static const byte cucpcStartup66[256];
	static const byte cucpcStartup67[256];
	static const byte cucpcStartup68[256];
	static const byte cucpcStartup69[256];
	static const byte cucpcStartup70[256];
	static const byte cucpcStartup71[256];
	static const byte cucpcStartup72[256];
	static const byte cucpcStartup73[256];
	static const byte cucpcStartup74[256];
	static const byte cucpcStartup75[256];
	static const byte cucpcStartup76[256];
	static const byte cucpcStartup77[256];
	static const byte cucpcStartup78[256];
	static const byte cucpcStartup79[256];
	static const byte cucpcStartup80[256];
	static const byte cucpcStartup81[256];
	static const byte cucpcStartup82[256];
	static const byte cucpcStartup83[256];
	static const byte cucpcStartup84[256];
	static const byte cucpcStartup85[256];
	static const byte cucpcStartup86[256];
	static const byte cucpcStartup87[256];
	static const byte cucpcStartup88[256];
	static const byte cucpcStartup89[256];
	static const byte cucpcStartup90[256];
	static const byte cucpcStartup91[256];
	static const byte cucpcStartup92[256];
	static const byte cucpcStartup93[256];
	static const byte cucpcStartup94[256];
	static const byte cucpcStartup95[256];
	static const byte cucpcStartup96[256];
	static const byte cucpcStartup97[256];
	static const byte cucpcStartup98[256];
	static const byte cucpcStartup99[256];
	static const byte cucpcStartup100[256];
	static const byte cucpcStartup101[256];
	static const byte cucpcStartup102[256];
	static const byte cucpcStartup103[256];
	static const byte cucpcStartup104[256];
	static const byte cucpcStartup105[256];
	static const byte cucpcStartup106[256];
	static const byte cucpcStartup107[256];
	static const byte cucpcStartup108[256];
	static const byte cucpcStartup109[256];
	static const byte cucpcStartup110[256];
	static const byte cucpcStartup111[256];
	static const byte cucpcStartup112[256];
	static const byte cucpcStartup113[256];
	static const byte cucpcStartup114[256];
	static const byte cucpcStartup115[256];
	static const byte cucpcStartup116[256];
	static const byte cucpcStartup117[256];
	static const byte cucpcStartup118[256];
	static const byte cucpcStartup119[256];
	static const byte cucpcStartup120[256];
	static const byte cucpcStartup121[256];
	static const byte cucpcStartup122[256];
	static const byte cucpcStartup123[256];
	static const byte cucpcStartup124[256];
	static const byte cucpcStartup125[256];
	static const byte cucpcStartup126[256];
	static const byte cucpcStartup127[256];
	static const byte cucpcStartup128[256];
	static const byte cucpcStartup129[256];
	static const byte cucpcStartup130[256];
	static const byte cucpcStartup131[256];
	static const byte cucpcStartup132[256];
	static const byte cucpcStartup133[256];
	static const byte cucpcStartup134[256];
	static const byte cucpcStartup135[256];
	static const byte cucpcStartup136[256];
	static const byte cucpcStartup137[256];
	static const byte cucpcStartup138[256];
	static const byte cucpcStartup139[256];
	static const byte cucpcStartup140[256];
	static const byte cucpcStartup141[256];
	static const byte cucpcStartup142[256];
	static const byte cucpcStartup143[256];
	static const byte cucpcStartup144[256];
	static const byte cucpcStartup145[256];
	static const byte cucpcStartup146[256];
	static const byte cucpcStartup147[256];
	static const byte cucpcStartup148[256];
	static const byte cucpcStartup149[256];
	static const byte cucpcStartup150[256];
	static const byte cucpcStartup151[256];
	static const byte cucpcStartup152[256];
	static const byte cucpcStartup153[256];
	static const byte cucpcStartup154[256];
	static const byte cucpcStartup155[256];
	static const byte cucpcStartup156[256];
	static const byte cucpcStartup157[256];
	static const byte cucpcStartup158[256];
	static const byte cucpcStartup159[256];
	static const byte cucpcStartup160[256];
	static const byte cucpcStartup161[256];
	static const byte cucpcStartup162[256];
	static const byte cucpcStartup163[256];
	static const byte cucpcStartup164[256];
	static const byte cucpcStartup165[256];
	static const byte cucpcStartup166[256];
	static const byte cucpcStartup167[256];
	static const byte cucpcStartup168[256];
	static const byte cucpcStartup169[256];
	static const byte cucpcStartup170[256];
	static const byte cucpcStartup171[256];
	static const byte cucpcStartup172[256];
	static const byte cucpcStartup173[256];
	static const byte cucpcStartup174[256];
	static const byte cucpcStartup175[256];
	static const byte cucpcStartup176[256];
	static const byte cucpcStartup177[256];
	static const byte cucpcStartup178[256];
	static const byte cucpcStartup179[256];
	static const byte cucpcStartup180[256];
	static const byte cucpcStartup181[256];
	static const byte cucpcStartup182[256];
	static const byte cucpcStartup183[256];
	static const byte cucpcStartup184[256];
	static const byte cucpcStartup185[256];
	static const byte cucpcStartup186[256];
	static const byte cucpcStartup187[256];
	static const byte cucpcStartup188[256];
	static const byte cucpcStartup189[256];
	static const byte cucpcStartup190[256];
	static const byte cucpcStartup191[256];
	static const byte cucpcStartup192[256];
	static const byte cucpcStartup193[256];
	static const byte cucpcStartup194[256];
	static const byte cucpcStartup195[256];
	static const byte cucpcStartup196[256];
	static const byte cucpcStartup197[256];
	static const byte cucpcStartup198[256];
	static const byte cucpcStartup199[256];
	// 子力位置价值表
	static const byte cucvlPiecePos[7][256];
	// 帅(将)的步长
	static const signed char ccKingDelta[4];
	// 仕(士)的步长
	static const signed char ccAdvisorDelta[4];
	// 马的步长，以帅(将)的步长作为马腿
	static const signed char ccKnightDelta[4][2];
	// 马被将军的步长，以仕(士)的步长作为马腿
	static const signed char ccKnightCheckDelta[4][2];
private:
	// 静态工具方法
	///////////////////////////////////////////////////////////////////
	// 判断棋子是否在棋盘中
	static inline bool IN_BOARD(int sq);
	// 判断棋子是否在九宫中
	static inline bool IN_FORT(int sq);
	// 获得格子的横坐标
	static inline int RANK_Y(int sq);
	// 获得格子的纵坐标
	static inline int FILE_X(int sq);
	// 根据纵坐标和横坐标获得格子
	static inline int COORD_XY(int x, int y);
	// 翻转格子
	static inline int SQUARE_FLIP(int sq);
	// 纵坐标水平镜像
	static inline int FILE_FLIP(int x);
	// 横坐标垂直镜像
	static inline int RANK_FLIP(int y);
	// 格子水平镜像
	static inline int MIRROR_SQUARE(int sq);
	// 格子水平镜像
	static inline int SQUARE_FORWARD(int sq, int sd);
	// 走法是否符合帅(将)的步长
	static inline bool KING_SPAN(int sqSrc, int sqDst);
	// 走法是否符合仕(士)的步长
	static inline bool ADVISOR_SPAN(int sqSrc, int sqDst);
	// 走法是否符合相(象)的步长
	static inline bool BISHOP_SPAN(int sqSrc, int sqDst);
	// 相(象)眼的位置
	static inline int BISHOP_PIN(int sqSrc, int sqDst);
	// 马腿的位置
	static inline int KNIGHT_PIN(int sqSrc, int sqDst);
	// 是否未过河
	static inline bool HOME_HALF(int sq, int sd);
	// 是否已过河
	static inline bool AWAY_HALF(int sq, int sd);
	// 是否在河的同一边
	static inline bool SAME_HALF(int sqSrc, int sqDst);
	// 是否在同一行
	static inline bool SAME_RANK(int sqSrc, int sqDst);
	// 是否在同一列
	static inline bool SAME_FILE(int sqSrc, int sqDst);
	// 获得红黑标记(红子是8，黑子是16)
	static inline int SIDE_TAG(int sd);
	// 获得对方红黑标记
	static inline int OPP_SIDE_TAG(int sd);
	// 获得走法的起点
	static inline int SRC(int mv);
	// 获得走法的终点
	static inline int DST(int mv);
	// 根据起点和终点获得走法
	static inline int MOVE(int sqSrc, int sqDst);
	// 走法水平镜像
	static inline int MIRROR_MOVE(int mv);

private:
	friend struct SortStruct;
	// 轮到谁走，0=红方，1=黑方
	int player;
	byte board[256];
	int vlWhite, vlBlack;           	// 红、黑双方的子力价值
	int nDistance, nMoveNum;        	// 距离根节点的步数，历史走法数
	MoveStruct mvsList[MAX_MOVES];  	// 历史走法信息列表
	ZobristStruct zobr;             	// Zobrist
	static Zobrist zobrist;
	std::vector<MoveStruct> history;	// 这个保留所有历史，而mvsList在吃子后会
										// 被清空。
	int direction;
	Search search;

private:
	// 棋盘方法
	///////////////////////////////////////////////////////////////////
	// 清空棋盘
	inline void clear(void);
	// 清空(初始化)历史走法信息
	inline void clearHistory(void);
	// 交换走子方
	inline void changeSide(void);
	// 在棋盘上放一枚棋子
	void addPiece(int sq, int pc);
	// 从棋盘上拿走一枚棋子
	void delPiece(int sq, int pc);
	// 局面评价函数
	int evaluate(void) const;
	// 是否被将军
	bool inCheck(void) const;
	// 上一步是否吃子
	bool captured(void) const;
	// 搬一步棋的棋子
	int putPiece(int mv);
	// 撤消搬一步棋的棋子
	void undoPut(int mv, int pcCaptured);
	// 走一步棋
	bool move(int mv);
	// 撤消走一步棋
	void undoMove(void);
	// 走一步空步
	void nullMove(void);
	// 撤消走一步空步
	void undoNullMove(void);
	// 判断走法是否合理
	bool testMove(int mv) const;
	// 生成所有走法，如果"bCapture"为"true"则只生成吃子走法
	int generateMoves(int *mvs, bool bCapture = false) const;
	// 判断是否被将军
	bool checked() const;
	// 判断是否被杀
	bool isMate(void);
	// 得到和棋的分值
	inline int getDrawValue(void) const;
	// 检测重复局面，得到重复局面所在的步骤偏移位置
	int getRepeatPos(int nRecur = 1) const;
	// 得到重复局面分值
	inline int getRepeatValue(int nRepStatus) const;
	// 对局面镜像
	void mirror(EngineChess &posMirror) const;
	// 判断是否允许空步裁剪
	inline bool allowNullMove(void) const;

private:
	// 搜索方法
	///////////////////////////////////////////////////////////////////
	// 搜索开局库
	int searchBook(void);
	// 提取置换表项
	int probeHash(int vlAlpha, int vlBeta, int nDepth, int &mv);
	// 保存置换表项
	void recordHash(int nFlag, int vl, int nDepth, int mv);
	// 静态(Quiescence)搜索过程
	int searchQuiescence(int vlAlpha, int vlBeta);
	// 对最佳走法的处理
	void setBestMove(int mv, int nDepth);
	// 超出边界(Fail-Soft)的Alpha-Beta搜索过程
	int searchFull(int vlAlpha, int vlBeta, int nDepth,
			bool bNoNull = false);
	// 根节点的Alpha-Beta搜索过程
	int searchRoot(int nDepth);
	// 迭代加深搜索过程
	int searchMain(float seconds);

public:
	// 棋子编号
	static const int PIECE_KING = 0;
	static const int PIECE_ADVISOR = 1;
	static const int PIECE_BISHOP = 2;
	static const int PIECE_KNIGHT = 3;
	static const int PIECE_ROOK = 4;
	static const int PIECE_CANNON = 5;
	static const int PIECE_PAWN = 6;

	// 局面状态
	static const int NORMAL = 0;
	static const int NORMAL_CAPTURED = 1;
	static const int NORMAL_CHECKED = 2;
	static const int RED_WIN = 3;
	static const int BLACK_WIN = 4;
	static const int DRAW = 5;
	static const int REPEATED = 0x100;
	static const int EXCEEDED_100 = 0x200;

public:
	// 初始化棋盘
	void startup(int direction, int idPos);
	// 走棋, direction: 面向棋盘红方在下侧是 0，否则是1
	bool move(int fromX, int fromY, int toX, int toY);
	// 悔棋
	void undo();
	// 得到走了多少步棋
	inline int getMoveCount() const;
	// 当前该谁走
	inline int getPlayer() const;
	// 得到游戏状态, 如果board指针不为NULL
	// 则还会复制当前棋盘局面信息到board指向的内存中, board 是简化的9x10棋盘
	// 可以是 byte a[10][9] 也可以是 byte a[90]
	// direction: 面向棋盘红方在下侧是 0，否则是1
	int getState(byte* board);
	// 盘面求解, 返回结果在 fromX fromY toX toY 中
	// direction: 面向棋盘红方在下侧是 0，否则是1
	// searchSeconds: 搜索多少秒
	bool findSolution(float searchSeconds, int& fromX, int& fromY,
			int& toX, int& toY);

	inline bool getLastMove(int& fromX, int& fromY, int& toX, int& toY);
};


///////////////////////////////////////////////////////////////////////////

// 判断棋子是否在棋盘中
inline bool EngineChess::IN_BOARD(int sq) {
#if defined(ANDROID_DEBUG)
	if (sq > 255) {
		exit(-1);
	}
#endif
	return ccInBoard[sq] != 0;
}

// 判断棋子是否在九宫中
inline bool EngineChess::IN_FORT(int sq) {
	return ccInFort[sq] != 0;
}

// 获得格子的横坐标
inline int EngineChess::RANK_Y(int sq) {
	return sq >> 4;
}

// 获得格子的纵坐标
inline int EngineChess::FILE_X(int sq) {
	return sq & 15;
}

// 根据纵坐标和横坐标获得格子
inline int EngineChess::COORD_XY(int x, int y) {
	return x + (y << 4);
}

// 翻转格子
inline int EngineChess::SQUARE_FLIP(int sq) {
	return 254 - sq;
}

// 纵坐标水平镜像
inline int EngineChess::FILE_FLIP(int x) {
	return 14 - x;
}

// 横坐标垂直镜像
inline int EngineChess::RANK_FLIP(int y) {
	return 15 - y;
}

// 格子水平镜像
inline int EngineChess::MIRROR_SQUARE(int sq) {
	return COORD_XY(FILE_FLIP(FILE_X(sq)), RANK_Y(sq));
}

// 格子水平镜像
inline int EngineChess::SQUARE_FORWARD(int sq, int sd) {
	return sq - 16 + (sd << 5);
}

// 走法是否符合帅(将)的步长
inline bool EngineChess::KING_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 1;
}

// 走法是否符合仕(士)的步长
inline bool EngineChess::ADVISOR_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 2;
}

// 走法是否符合相(象)的步长
inline bool EngineChess::BISHOP_SPAN(int sqSrc, int sqDst) {
	return ccLegalSpan[sqDst - sqSrc + 256] == 3;
}

// 相(象)眼的位置
inline int EngineChess::BISHOP_PIN(int sqSrc, int sqDst) {
	return (sqSrc + sqDst) >> 1;
}

// 马腿的位置
inline int EngineChess::KNIGHT_PIN(int sqSrc, int sqDst) {
	return sqSrc + ccKnightPin[sqDst - sqSrc + 256];
}

// 是否未过河
inline bool EngineChess::HOME_HALF(int sq, int sd) {
	return (sq & 0x80) != (sd << 7);
}

// 是否已过河
inline bool EngineChess::AWAY_HALF(int sq, int sd) {
	return (sq & 0x80) == (sd << 7);
}

// 是否在河的同一边
inline bool EngineChess::SAME_HALF(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0x80) == 0;
}

// 是否在同一行
inline bool EngineChess::SAME_RANK(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0xf0) == 0;
}

// 是否在同一列
inline bool EngineChess::SAME_FILE(int sqSrc, int sqDst) {
	return ((sqSrc ^ sqDst) & 0x0f) == 0;
}

// 获得红黑标记(红子是8，黑子是16)
inline int EngineChess::SIDE_TAG(int sd) {
	return 8 + (sd << 3);
}

// 获得对方红黑标记
inline int EngineChess::OPP_SIDE_TAG(int sd) {
	return 16 - (sd << 3);
}

// 获得走法的起点
inline int EngineChess::SRC(int mv) {
	return mv & 255;
}

// 获得走法的终点
inline int EngineChess::DST(int mv) {
	return mv >> 8;
}

// 根据起点和终点获得走法
inline int EngineChess::MOVE(int sqSrc, int sqDst) {
	return sqSrc + sqDst * 256;
}

// 走法水平镜像
inline int EngineChess::MIRROR_MOVE(int mv) {
	return MOVE(MIRROR_SQUARE(SRC(mv)), MIRROR_SQUARE(DST(mv)));
}

//////////////////////////////////////////////////////////////////////

// 清空棋盘
inline void EngineChess::clear(void) {
	player = vlWhite = vlBlack = nDistance = 0;
	memset(board, 0, 256);
	zobr.InitZero();
}

// 清空(初始化)历史走法信息
inline void EngineChess::clearHistory(void) {
	mvsList[0].set(0, 0, checked(), zobr.dwKey);
	nMoveNum = 1;
}

inline void EngineChess::changeSide(void) {
	player = 1 - player;
	zobr.Xor(zobrist.Player);
}

// 在棋盘上放一枚棋子
inline void EngineChess::addPiece(int sq, int pc) {
	board[sq] = pc;
	// 红方加分，黑方(注意"cucvlPiecePos"取值要颠倒)减分
	if (pc < 16) {
		vlWhite += cucvlPiecePos[pc - 8][sq];
		zobr.Xor(zobrist.Table[pc - 8][sq]);
	} else {
		vlBlack += cucvlPiecePos[pc - 16][SQUARE_FLIP(sq)];
		zobr.Xor(zobrist.Table[pc - 9][sq]);
	}
}

// 从棋盘上拿走一枚棋子
inline void EngineChess::delPiece(int sq, int pc) {
	board[sq] = 0;
	// 红方减分，黑方(注意"cucvlPiecePos"取值要颠倒)加分
	if (pc < 16) {
		vlWhite -= cucvlPiecePos[pc - 8][sq];
		zobr.Xor(zobrist.Table[pc - 8][sq]);
	} else {
		vlBlack -= cucvlPiecePos[pc - 16][SQUARE_FLIP(sq)];
		zobr.Xor(zobrist.Table[pc - 9][sq]);
	}
}

// 局面评价函数
inline int EngineChess::evaluate(void) const {
	return (player == 0 ? vlWhite - vlBlack : vlBlack - vlWhite)
			+ ADVANCED_VALUE;
}

// 是否被将军
inline bool EngineChess::inCheck(void) const {
	return mvsList[nMoveNum - 1].ucbCheck != 0;
}

// 上一步是否吃子
inline bool EngineChess::captured(void) const {
	if (history.empty())
		return false;
	else
		return history.back().ucpcCaptured != 0;
//	return mvsList[nMoveNum - 1].ucpcCaptured != 0;
}

// 摆放一个棋子
inline int EngineChess::putPiece(int mv) {
	int sqSrc, sqDst, pc, pcCaptured;
	sqSrc = SRC(mv);
	sqDst = DST(mv);
	pcCaptured = board[sqDst];
	if (pcCaptured != 0) {
		delPiece(sqDst, pcCaptured);
	}
	pc = board[sqSrc];
	delPiece(sqSrc, pc);
	addPiece(sqDst, pc);
	return pcCaptured;
}

// 撤消摆放一个棋子
inline void EngineChess::undoPut(int mv, int pcCaptured) {
	int sqSrc, sqDst, pc;
	sqSrc = SRC(mv);
	sqDst = DST(mv);
	pc = board[sqDst];
	delPiece(sqDst, pc);
	addPiece(sqSrc, pc);
	if (pcCaptured != 0) {
		addPiece(sqDst, pcCaptured);
	}
}

// 走一步棋
inline bool EngineChess::move(int mv) {
	int pcCaptured;
	uint32 dwKey;

	dwKey = zobr.dwKey;
	pcCaptured = putPiece(mv);
	if (checked()) {
		undoPut(mv, pcCaptured);
		return false;
	}
	changeSide();
	mvsList[nMoveNum].set(mv, pcCaptured, checked(), dwKey);
	nMoveNum++;
#if defined(ANDROID_DEBUG)
	if (nMoveNum >= MAX_MOVES) {
		LOG("nMoveNum out of range.");
		exit(nMoveNum);
	}
#endif
	nDistance++;
	return true;
}

// 撤消走一步棋
inline void EngineChess::undoMove(void) {
	nDistance--;
	nMoveNum--;
	changeSide();
	undoPut(mvsList[nMoveNum].wmv, mvsList[nMoveNum].ucpcCaptured);
}

// 走一步空步
inline void EngineChess::nullMove(void) {
	uint32 dwKey;
	dwKey = zobr.dwKey;
	changeSide();
	mvsList[nMoveNum].set(0, 0, false, dwKey);
	nMoveNum++;
#if defined(ANDROID_DEBUG)
	if (nMoveNum >= MAX_MOVES) {
		LOG("nMoveNum out of range.");
		exit(nMoveNum);
	}
#endif
	nDistance++;
}

// 撤消走一步空步
inline void EngineChess::undoNullMove(void) {
	nDistance--;
	nMoveNum--;
	changeSide();
}

// 判断是否允许空步裁剪
inline bool EngineChess::allowNullMove(void) const {
	return (player == 0 ? vlWhite : vlBlack) > NULL_MARGIN;
}

// 得到重复局面分值
inline int EngineChess::getRepeatValue(int nRepStatus) const {
	int vlReturn;
	vlReturn = ((nRepStatus & 2) == 0 ? 0 : nDistance - BAN_VALUE)
			+ ((nRepStatus & 4) == 0 ? 0 : BAN_VALUE - nDistance);
	return vlReturn == 0 ? getDrawValue() : vlReturn;
}

// 得到和棋的分值
inline int EngineChess::getDrawValue(void) const {
	return (nDistance & 1) == 0 ? -DRAW_VALUE : DRAW_VALUE;
}

// 得到走了多少步棋
inline int EngineChess::getMoveCount() const {
	return (int)history.size();
}

inline bool EngineChess::getLastMove(int& fromX, int& fromY, int& toX, int& toY) {
	if (history.size() <= 0)
		return false;
	uint32 mv = history.back().wmv;
	int from = SRC(mv);
	int to = DST(mv);
	fromX = FILE_X(from) - 3;
	if (direction == 0)
		fromY = RANK_Y(from) - 3;
	else
		fromY = RANK_FLIP(RANK_Y(from)) - 3;
	toX = FILE_X(to) - 3;
	if (direction == 0)
		toY = RANK_Y(to) - 3;
	else
		toY = RANK_FLIP(RANK_Y(to)) - 3;
	return true;
}

// 当前该谁走
inline int EngineChess::getPlayer() const {
	return player;
}



} // End namespace.


#endif /* ENGINE_H_ */
