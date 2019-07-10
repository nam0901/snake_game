#include "Tetris_MovingObject.h"
#include "Tetris_StandingObject.h"
#include <string.h>

//typedef enum
//{
//	UP,
//	DOWN,
//	LEFT,
//	RIGHT
//} MO_Direction_t;

//static int CheckForCollision(Coordinate_t *CheckingBlock, MO_Direction_t Direction);
static int MovingObject_Init();
static int MovingObject_DeInit();
static int MovingObject_Generate();
static int MovingObject_MoveLeft();
static int MovingObject_MoveRight();
static int MovingObject_MoveDown();
static int MovingObject_Rotate();
static int MovingObject_Check();
static int MovingObject_CheckAbleMove();
static int MovingObject_CalculateDropPlace();

static void MovingObject_GraphicInit();
static void MovingObject_GraphicDeInit();
static void MovingObject_GraphicClear();
static void MovingObject_GraphicUpdate();
static void MovingObject_GraphicShow();

#define NULL_ (void*)0;
MovingObject_t MovingObject =
{
	MovingObject_Init,
	MovingObject_DeInit,
	MovingObject_Generate,
	MovingObject_MoveLeft,
	MovingObject_MoveRight,
	MovingObject_MoveDown,
	MovingObject_Rotate,
	MovingObject_Check,
	MovingObject_CheckAbleMove,
	MovingObject_CalculateDropPlace,

	MovingObject_GraphicInit,
	MovingObject_GraphicDeInit,
	MovingObject_GraphicClear,
	MovingObject_GraphicUpdate,
	MovingObject_GraphicShow
};

//int CheckForCollision(Coordinate_t *CheckingBlock, MO_Direction_t Direction)
//{
//	for(i = 0; i < 4; i++)
//	{
//		VirtualBlock[i].Column = MovingObject.Block[i].Column;
//		VirtualBlock[i].Row = MovingObject.Block[i].Row - 1;
//		if(VirtualBlock[i].Column < 0)
//		{
//			MovingObject.able_moveDown = false;	// Unable to move down because boundary reached
//			break;
//		}
//		if(StandingObject.is_Existed(VirtualBlock[i]))
//		{
//			MovingObject.able_moveDown = false;	// Unable to move down because of collision
//			break;
//		}
//	}
//}
int MovingObject_Init()
{
//	MovingObject.GraphicObj.initialize();
//	MovingObject.GraphicObj.display_off();
//	MovingObject.GraphicObj.display_on();
	MovingObject.NextShape[0] = (Block_Shape_t)(rand()%7);
	MovingObject.NextShape[1] = (Block_Shape_t)(rand()%7);
	MovingObject.NextShape[2] = (Block_Shape_t)(rand()%7);
	MovingObject.Generate();
	return 0;
}

int MovingObject_DeInit()
{
//	MovingObject.GraphicObj.clear(0);
//	MovingObject.GraphicObj.display_off();
	return 0;
}

int MovingObject_Generate()
{
	switch(MovingObject.NextShape[0])
	{
		case Block_Bar:
		{
			MovingObject.Block[0].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[0].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[1].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[1].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[2].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[2].Row		= (uint16_t)(TETRIS_ROW_NUMBER+2);
			MovingObject.Block[3].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[3].Row		= (uint16_t)(TETRIS_ROW_NUMBER+3);
		}
		break;
		case Block_Square:
		{
			MovingObject.Block[0].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[0].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[1].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[1].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[2].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[2].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[3].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[3].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
		}
		break;
		case Block_L:
		{
			MovingObject.Block[0].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[0].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[1].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[1].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[2].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[2].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[3].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[3].Row		= (uint16_t)(TETRIS_ROW_NUMBER+2);
		}
		break;
		case Block_L_mirror:
		{
			MovingObject.Block[0].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[0].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[1].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[1].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[2].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[2].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[3].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[3].Row		= (uint16_t)(TETRIS_ROW_NUMBER+2);
		}
		break;
		case Block_Z:
		{
			MovingObject.Block[0].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2+1);
			MovingObject.Block[0].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[1].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[1].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[2].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[2].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[3].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[3].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
		}
		break;
		case Block_Z_mirror:
		{
			MovingObject.Block[0].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[0].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[1].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[1].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[2].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[2].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[3].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2+1);
			MovingObject.Block[3].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
		}
		break;
		case Block_T:
		{
			MovingObject.Block[0].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2+1);
			MovingObject.Block[0].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[1].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[1].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
			MovingObject.Block[2].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2);
			MovingObject.Block[2].Row		= (uint16_t)(TETRIS_ROW_NUMBER+1);
			MovingObject.Block[3].Column	= (uint16_t)(TETRIS_COLUMN_NUMBER/2-1);
			MovingObject.Block[3].Row		= (uint16_t)(TETRIS_ROW_NUMBER);
		}
		break;
	}

	MovingObject.NextShape[0] = MovingObject.NextShape[1];
	MovingObject.NextShape[1] = MovingObject.NextShape[2];
	MovingObject.NextShape[2] = (Block_Shape_t)(rand()%7);

	MovingObject.Check();
	return 0;
}

int MovingObject_MoveLeft()
{
	int i;
	Coordinate_t VirtualBlock[4];

	if(MovingObject.able_moveLeft == false) return 1;	//Unable to move Left
	for(i = 0; i < 4; i++)
	{
		VirtualBlock[i].Column = MovingObject.Block[i].Column - 1;
		VirtualBlock[i].Row = MovingObject.Block[i].Row;
	}
	memcpy(MovingObject.Block, VirtualBlock, sizeof(Coordinate_t)*4);
	MovingObject.Check();
	return 0;	// Successfully
}

int MovingObject_MoveRight()
{
	int i;
	Coordinate_t VirtualBlock[4];

	if(MovingObject.able_moveRight == false) return 1;	// Unable to move Right
	for(i = 0; i < 4; i++)
	{
		VirtualBlock[i].Column = MovingObject.Block[i].Column + 1;
		VirtualBlock[i].Row = MovingObject.Block[i].Row;
	}
	memcpy(MovingObject.Block, VirtualBlock, sizeof(Coordinate_t)*4);
	MovingObject.Check();
	return 0;	// Successfully
}

int MovingObject_MoveDown()
{
	if(MovingObject.able_moveDown == true)
	{
		Coordinate_t VirtualBlock[4];
		for(int i = 0; i < 4; i++)
		{
			VirtualBlock[i].Column = MovingObject.Block[i].Column;
			VirtualBlock[i].Row = MovingObject.Block[i].Row - 1;
		}
		memcpy(MovingObject.Block, VirtualBlock, sizeof(Coordinate_t)*4);
		MovingObject.Check();
		return 0;	// Successfully
	}
	else
	{
		return 1;	// The game need Update!
	}

}

int MovingObject_Rotate()
{
	Coordinate_t VirtualBlock[4];
	bool _able_Rotate = true;
//	bool _Boundary_Left = false;
//	bool _Boundary_Right = false;
	/* Rotate Left: (Center = Block[1])
	 * DestPoint.Column = Center.Column + (SrcPoint.Row - Center.Row);
	 * DestPoint.Row = Center.Row - (SrcPoint.Column - Center.Column);
	 * */

	for(int i = 0; i < 4; i++)
	{
		VirtualBlock[i].Column = MovingObject.Block[1].Column + (MovingObject.Block[i].Row - MovingObject.Block[1].Row);
		VirtualBlock[i].Row = MovingObject.Block[1].Row - (MovingObject.Block[i].Column - MovingObject.Block[1].Column);
		if( (VirtualBlock[i].Row < 0) || (VirtualBlock[i].Column < 0) || (VirtualBlock[i].Column >= TETRIS_COLUMN_NUMBER) )
		{
			_able_Rotate = false;
			break;
		}
		if(StandingObject.is_Existed(VirtualBlock[i]))
		{
			_able_Rotate = false;
			break;
		}
//		else if(VirtualBlock[i].Column < 0)
//			_Boundary_Left = true;
//		else if(VirtualBlock[i].Column >= TETRIS_COLUMN_NUMBER)
//			_Boundary_Right = true;
	}

	if(_able_Rotate == true)
	{
		memcpy(MovingObject.Block, VirtualBlock, sizeof(Coordinate_t)*4);
		MovingObject.Check();
		return 0;
	}
	else
	{
		return 1;
	}
}

int MovingObject_Check()
{
	MovingObject.CheckAbleMove();
	MovingObject.CalculateDropPlace();
	return 0;
}

int MovingObject_CheckAbleMove()
{
	Coordinate_t VirtualBlock[4];
	// Check availability to move left
	MovingObject.able_moveLeft = true;
	for(int i = 0; i < 4; i++)
	{
		VirtualBlock[i].Column = MovingObject.Block[i].Column - 1;
		VirtualBlock[i].Row = MovingObject.Block[i].Row;
		if(VirtualBlock[i].Column < 0)
		{
			MovingObject.able_moveLeft = false;	// Unable to move left because boundary reached
			break;
		}
		if(StandingObject.is_Existed(VirtualBlock[i]))
		{
			MovingObject.able_moveLeft = false;	// Unable to move left because of collision
			break;
		}
	}

	// Check availability to move right
	MovingObject.able_moveRight = true;
	for(int i = 0; i < 4; i++)
	{
		VirtualBlock[i].Column = MovingObject.Block[i].Column + 1;
		VirtualBlock[i].Row = MovingObject.Block[i].Row;
		if(VirtualBlock[i].Column >= TETRIS_COLUMN_NUMBER)
		{
			MovingObject.able_moveRight = false;	// Unable to move right because boundary reached
			break;
		}
		if(StandingObject.is_Existed(VirtualBlock[i]))
		{
			MovingObject.able_moveRight = false;	// Unable to move right because of collision
			break;
		}
	}

	// Check availability to move down
	MovingObject.able_moveDown = true;
	for(int i = 0; i < 4; i++)
	{
		VirtualBlock[i].Column = MovingObject.Block[i].Column;
		VirtualBlock[i].Row = MovingObject.Block[i].Row - 1;
		if(VirtualBlock[i].Row < 0)
		{
			MovingObject.able_moveDown = false;	// Unable to move down because boundary reached
			break;
		}
		if(StandingObject.is_Existed(VirtualBlock[i]))
		{
			MovingObject.able_moveDown = false;	// Unable to move down because of collision
			break;
		}
	}
	return 0;
}

int MovingObject_CalculateDropPlace()
{
	bool _able_moveDown = true;
	Coordinate_t VirtualBlock[4];
	Coordinate_t CurrentDropPoint[4];

	memcpy(CurrentDropPoint, MovingObject.Block, sizeof(Coordinate_t)*4);

	while(_able_moveDown == true)
	{
		for(int i = 0; i < 4; i++)
		{
			VirtualBlock[i].Column = CurrentDropPoint[i].Column;
			VirtualBlock[i].Row = CurrentDropPoint[i].Row - 1;
			if(VirtualBlock[i].Row < 0)
			{
				_able_moveDown = false;	// Unable to move down because boundary reached
				break;
			}
			if(StandingObject.is_Existed(VirtualBlock[i]))
			{
				_able_moveDown = false;	// Unable to move down because of collision
				break;
			}
		}
		if(_able_moveDown == true)
			memcpy(CurrentDropPoint, VirtualBlock, sizeof(Coordinate_t)*4);
	}
	memcpy(MovingObject.DropPoint ,CurrentDropPoint, sizeof(Coordinate_t)*4);
	return 0;
}

void MovingObject_GraphicInit()
{
	MovingObject.GraphicObj.initialize();
	MovingObject.GraphicObj.display_off();
	MovingObject.GraphicObj.display_on();
}

void MovingObject_GraphicDeInit()
{
	MovingObject.GraphicObj.clear(0);
	MovingObject.GraphicObj.display_off();
}

void MovingObject_GraphicClear()
{
	MovingObject.GraphicObj.clear();
}

void MovingObject_GraphicUpdate()
{
	Coordinate_t _Temp;
	for(int i = 0; i<4; i++)
	{
		tetris_coordinate_to_position(MovingObject.Block[i], &_Temp);
		MovingObject.GraphicObj.fillRect(_Temp.Column, _Temp.Row, 3, 3, WHITE);
		tetris_coordinate_to_position(MovingObject.DropPoint[i], &_Temp);
		MovingObject.GraphicObj.fillRect(_Temp.Column+1, _Temp.Row+1, 1, 1, WHITE);
	}
}

void MovingObject_GraphicShow()
{
	MovingObject.GraphicObj.update();
}
