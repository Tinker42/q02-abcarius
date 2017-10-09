/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

// Checks the constructor
TEST(PiezasTest, constructorCheck)
{
  Piezas board;
  ASSERT_TRUE(true);
}

TEST(PiezasTest, pieceAtCheck)
{
	Piezas board;
	Piece ret = board.pieceAt(0, 0);
	ASSERT_EQ(ret, Blank);
}

TEST(PiezasTest, dropThenAt)
{
	Piezas board;
	board.dropPiece(0);
	Piece ret = board.pieceAt(0, 0);
	ASSERT_EQ(ret, X);
}

TEST(PiezasTest, dropOutOfBoundsLessThan)
{
	Piezas board;
	Piece drop = board.dropPiece(-1);
	
	ASSERT_EQ(drop, Invalid);
}

TEST(PiezasTest, dropOutOfBoundsGreaterThan)
{
	Piezas board;
	Piece drop = board.dropPiece(4);
	
	ASSERT_EQ(drop, Invalid);
}

TEST(PiezasTest, dropFirstPieceCol0)
{
	Piezas board;
	Piece turn = board.dropPiece(0);
	
	ASSERT_EQ(X, turn);
}

TEST(PiezasTest, dropSecondPieceCol0)
{
	Piezas board;
	board.dropPiece(0);
	Piece turn = board.dropPiece(0);
	
	ASSERT_EQ(O, turn);
}

TEST(PiezasTest, dropThirdPieceCol0)
{
	Piezas board;
	board.dropPiece(0);
	board.dropPiece(0);
	Piece turn = board.dropPiece(0);
	
	ASSERT_EQ(X, turn);
}

TEST(PiezasTest, dropFourthPieceCol0)
{
	Piezas board;
	board.dropPiece(0);
	board.dropPiece(0);
	board.dropPiece(0);
	Piece turn = board.dropPiece(0);
	
	ASSERT_EQ(Invalid, turn);
}

TEST(PiezasTest, gameStateCheck)
{
	Piezas board;
	Piece ret = board.gameState();

	ASSERT_EQ(ret, Invalid);
}

TEST(PiezasTest, reset)
{
	Piezas board;
	
	board.dropPiece(0);
	board.dropPiece(0);
	board.dropPiece(0);
	board.dropPiece(1);
	board.dropPiece(1);
	board.dropPiece(1);
	board.dropPiece(2);
	board.dropPiece(2);
	board.dropPiece(2);
	board.dropPiece(3);
	board.dropPiece(3);
	board.dropPiece(3);
	board.reset();
	Piece test = board.pieceAt(1,1);
	
	ASSERT_EQ(Blank, test);
}

TEST(PiezasTest, IncompleteGame)
{
	Piezas board;
	
	board.dropPiece(0);
	board.dropPiece(1);
	board.dropPiece(2);
	board.dropPiece(3);
	board.dropPiece(0);
	board.dropPiece(3);

	Piece winner = board.gameState();
	
	ASSERT_EQ(Invalid, winner);
}

TEST(PiezasTest, HorizontalWinner)
{
	Piezas board;
	
	board.dropPiece(2);
	board.dropPiece(0);
	board.dropPiece(0);
	board.dropPiece(1);
	board.dropPiece(1);
	board.dropPiece(3);
	board.dropPiece(2);
	board.dropPiece(1);
	board.dropPiece(3);
	board.dropPiece(2);
	board.dropPiece(0);
	board.dropPiece(3);
	Piece winner = board.gameState();
	
	ASSERT_EQ(X, winner);
}
 
TEST(PiezasTest, GameStateTie)
{
	Piezas board;
	
	board.dropPiece(0);
	board.dropPiece(1);
	board.dropPiece(2);
	board.dropPiece(3);
	board.dropPiece(0);
	board.dropPiece(3);
	board.dropPiece(1);
	board.dropPiece(1);
	board.dropPiece(2);
	board.dropPiece(2);
	board.dropPiece(0);
	board.dropPiece(3);
	Piece winner = board.gameState();
	
	ASSERT_EQ(Blank, winner);
}
 
TEST(PiezasTest, VerticalWinner)
{
	Piezas board;
	
	board.dropPiece(0);
	board.dropPiece(1);
	board.dropPiece(3);
	board.dropPiece(2);
	board.dropPiece(1);
	board.dropPiece(0);
	board.dropPiece(3);
	board.dropPiece(2);
	board.dropPiece(0);
	board.dropPiece(2);
	board.dropPiece(1);
	board.dropPiece(3);
	Piece winner = board.gameState();
	
	ASSERT_EQ(O, winner);
}