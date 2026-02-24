#include "Maze.h"

class NavigationRobot : public Maze {
	public:
		NavigationRobot();
		NavigationRobot(Space, Space, string); // Use this constructor to customize start and end points of maze 
									   //as well as starting direction of robot

		void traverse(); // This function solves the maze

		void moveSpace();
		void cwTurn();
		void ccwTurn();
		void uTurn();

		bool barrierAhead();
		bool barrierOnRight();
		bool barrierOnLeft();

		void createVirtualBarrier();
		void drawVirtualBarrier();

		bool virtualBarrierAhead();
		bool virtualBarrierOnRight();
		bool virtualBarrierOnLeft();

		bool deadEnd();

		bool rightLeftFork();
		bool rightForwardFork();
		bool leftForwardFork();
		bool threeWayFork();

		void returnFromDeadEnd();
		void navigateRightLeftFork();
		void navigateRightForwardFork();
		void navigateLeftForwardFork();
		void navigateThreeWayFork();
	
	private:
		Space position;
		string direction;
		int rowIndex;
		int colIndex;

};

NavigationRobot::NavigationRobot() : Maze(), position(start), direction("down")
{
	rowIndex = position.getRow() - 1;        // Subtract rows by 1 and columns by 'A' to attain proper index of arrays
	colIndex = position.getColumn() - 'A';   // This makes it easier to code maze solver
}

NavigationRobot::NavigationRobot(Space st, Space e, string dir) : Maze(st, e), position(start), direction(dir) 
{
	rowIndex = position.getRow() - 1;        // Subtract rows by 1 and columns by 'A' to attain proper index of arrays
	colIndex = position.getColumn() - 'A';   // This makes it easier to code maze solver
}

void NavigationRobot::cwTurn()
{
	if (direction == "right")
		direction = "down";
	else if (direction == "down")
		direction = "left";
	else if (direction == "left")
		direction = "up";
	else if (direction == "up")
		direction = "right";
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
	output_file << "Turning right" << endl;
}

void NavigationRobot::ccwTurn()
{
	if (direction == "right")
		direction = "up";
	else if (direction == "down")
		direction = "right";
	else if (direction == "left")
		direction = "down";
	else if (direction == "up")
		direction = "left";
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
	output_file << "Turning left" << endl;
}

void NavigationRobot::uTurn()
{
	if (direction == "right")
		direction = "left";
	else if (direction == "down")
		direction = "up";
	else if (direction == "left")
		direction = "right";
	else if (direction == "up")
		direction = "down";
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
	output_file << "Turning around" << endl;
}

void NavigationRobot::moveSpace() 
{
	if (barrierAhead())
	{
		output_file << "Barrier ahead. Cannot move forward" << endl;
		exit(1);
	}

	if (virtualBarrierAhead())
		output_file << "Something is wrong" << endl;

	if (direction == "right")
		colIndex += 1;
	else if (direction == "down")
		rowIndex += 1;
	else if (direction == "left")
		colIndex -= 1;
	else if (direction == "up")
		rowIndex -= 1;
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}

	position = s[rowIndex][colIndex];
	output_file << "New position is ";
	position.display();

	
	//veCursorToSpace(position);
	Sleep(500);
	cout << "\b ";
	moveCursorToSpace(position);
	cout << "*";
}

bool NavigationRobot::barrierAhead()
{
	if (direction == "up")
	{
		if (horizontalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "down")
	{
		if (horizontalBarrier[rowIndex + 1][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "right")
	{
		if (verticalBarrier[rowIndex][colIndex + 1] == true)
			return true;
		else
			return false;
	}
	else if (direction == "left")
	{
		if (verticalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

bool NavigationRobot::barrierOnRight()
{
	if (direction == "left")
	{
		if (horizontalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "right")
	{
		if (horizontalBarrier[rowIndex + 1][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "up")
	{
		if (verticalBarrier[rowIndex][colIndex + 1] == true)
			return true;
		else
			return false;
	}
	else if (direction == "down")
	{
		if (verticalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

bool NavigationRobot::barrierOnLeft()
{
	{
		if (direction == "right")
		{
			if (horizontalBarrier[rowIndex][colIndex] == true)
				return true;
			else
				return false;
		}
		else if (direction == "left")
		{
			if (horizontalBarrier[rowIndex + 1][colIndex] == true)
				return true;
			else
				return false;
		}
		else if (direction == "down")
		{
			if (verticalBarrier[rowIndex][colIndex + 1] == true)
				return true;
			else
				return false;
		}
		else if (direction == "up")
		{
			if (verticalBarrier[rowIndex][colIndex] == true)
				return true;
			else
				return false;
		}
		else
		{
			output_file << "Error" << endl;
			exit(1);
		}
	}
}

bool NavigationRobot::virtualBarrierAhead()
{
	if (direction == "up")
	{
		if (virtualHorizontalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "down")
	{
		if (virtualHorizontalBarrier[rowIndex + 1][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "right")
	{
		if (virtualVerticalBarrier[rowIndex][colIndex + 1] == true)
			return true;
		else
			return false;
	}
	else if (direction == "left")
	{
		if (virtualVerticalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

bool NavigationRobot::virtualBarrierOnRight()
{
	if (direction == "left")
	{
		if (virtualHorizontalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "right")
	{
		if (virtualHorizontalBarrier[rowIndex + 1][colIndex] == true)
			return true;
		else
			return false;
	}
	else if (direction == "up")
	{
		if (virtualVerticalBarrier[rowIndex][colIndex + 1] == true)
			return true;
		else
			return false;
	}
	else if (direction == "down")
	{
		if (virtualVerticalBarrier[rowIndex][colIndex] == true)
			return true;
		else
			return false;
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

bool NavigationRobot::virtualBarrierOnLeft()
{
	{
		if (direction == "right")
		{
			if (virtualHorizontalBarrier[rowIndex][colIndex] == true)
				return true;
			else
				return false;
		}
		else if (direction == "left")
		{
			if (virtualHorizontalBarrier[rowIndex + 1][colIndex] == true)
				return true;
			else
				return false;
		}
		else if (direction == "down")
		{
			if (virtualVerticalBarrier[rowIndex][colIndex + 1] == true)
				return true;
			else
				return false;
		}
		else if (direction == "up")
		{
			if (virtualVerticalBarrier[rowIndex][colIndex] == true)
				return true;
			else
				return false;
		}
		else
		{
			output_file << "Error" << endl;
			exit(1);
		}
	}
}

bool NavigationRobot::deadEnd()
{
	if ( (barrierAhead() || virtualBarrierAhead() ) && (barrierOnRight() || virtualBarrierOnRight() ) 
		&& (barrierOnLeft() || virtualBarrierOnLeft() )   )
		return true;

	return false;
}

bool NavigationRobot::rightForwardFork()
{
	if (threeWayFork() )
		return false;

	if (!barrierAhead() && !virtualBarrierAhead() && !barrierOnRight() && !virtualBarrierOnRight() )
		return true;

	return false;
}

bool NavigationRobot::leftForwardFork()
{
	if (threeWayFork())
		return false;

	if (!barrierAhead() && !virtualBarrierAhead() && !barrierOnLeft() && !virtualBarrierOnLeft())
		return true;

	return false;
}

bool NavigationRobot::rightLeftFork()
{
	if (threeWayFork())
		return false;

	if (!barrierOnRight() && !barrierOnLeft() && !virtualBarrierOnRight() && !virtualBarrierOnLeft() )
		return true;

	return false;
}

bool NavigationRobot::threeWayFork()
{
	if (!barrierAhead() && !barrierOnRight() && !barrierOnLeft() 
						&& !virtualBarrierAhead() && !virtualBarrierOnRight() && !virtualBarrierOnLeft() )
		return true;

	return false;
}

void NavigationRobot::navigateRightLeftFork()
{
	if (direction == "up")
	{
		s[rowIndex][colIndex].incrementUpwardVisits();
		if (s[rowIndex][colIndex].getUpwardVisits() % 2 == 1) // On first visit to two-way fork 
															  // and on subsequent odd visits, do the following:
		{
			if (colIndex > endColIndex) // That is, the position is to the right of the maze end
			{
				ccwTurn();
				moveSpace();
			}
			else
			{
				cwTurn();
				moveSpace();
			}
		}
		else // On even visits to the fork, pick the opposite direction
		{
			if (colIndex > endColIndex) // That is, the position is to the right of the maze end
			{
				cwTurn();
				moveSpace();
			}
			else
			{
				ccwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "down")
	{
		s[rowIndex][colIndex].incrementDownwardVisits();
		if (s[rowIndex][colIndex].getDownwardVisits() % 2 == 1)
		{
			if (colIndex >= endColIndex)
			{
				cwTurn();
				moveSpace();
			}
			else
			{
				ccwTurn();
				moveSpace();
			}
		}
		else // On even visits
		{
			if (colIndex >= endColIndex)
			{
				ccwTurn();
				moveSpace();
			}
			else
			{
				cwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "right")
	{
		s[rowIndex][colIndex].incrementRightwardVisits();
		if (s[rowIndex][colIndex].getRightwardVisits() %2 == 1)
		{
			if (rowIndex > endRowIndex) // That is, the robot is below the maze end
			{
				ccwTurn();
				moveSpace();
			}
			else
			{
				cwTurn();
				moveSpace();
			}
		}
		else // On even visits to the fork, pick the opposite direction
		{
			if (rowIndex > endRowIndex) // That is, the robot is below the maze end
			{
				cwTurn();
				moveSpace();
			}
			else
			{
				ccwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "left")
	{
		s[rowIndex][colIndex].incrementLeftwardVisits();
		if (s[rowIndex][colIndex].getLeftwardVisits() %2 == 1)
		{
			if (rowIndex < endRowIndex) // That is, the robot is above of the maze
			{
				ccwTurn();
				moveSpace();
			}
			else
			{
				cwTurn();
				moveSpace();
			}
		}
		else // On even visits, pick the opposite direction
		{
			if (rowIndex < endRowIndex) // That is, the robot is above of the maze
			{
				cwTurn();
				moveSpace();
			}
			else
			{
				ccwTurn();
				moveSpace();
			}
		}
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

void NavigationRobot::navigateRightForwardFork()
{
	if (direction == "up")
	{
		s[rowIndex][colIndex].incrementUpwardVisits();
		if (s[rowIndex][colIndex].getUpwardVisits() % 2 == 1) // On first visit to two-way fork 
															  // and on subsequent odd visits, do the following:
		{
			// First work out the cases where the robot is in the same row or column as the maze end
			if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
				{
					cwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze end
				{
					cwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex < endRowIndex) // robot is in upper section
			{
				cwTurn();
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // robot is in lower section
				moveSpace();
		}
		else // On even visits to the fork, pick the opposite direction
		{
			if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
					moveSpace();
				else
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze end
					moveSpace();
				else
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex < endRowIndex) // robot is in upper section
			{
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // robot is in lower section
			{
				cwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "down")
	{
		s[rowIndex][colIndex].incrementDownwardVisits();
		if (s[rowIndex][colIndex].getDownwardVisits() %2 == 0) // On even visits to the fork, pick the opposite direction
		{
			// First work out the cases where the robot is in the same row or column as the maze end
			if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
				{
					cwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze end
				{
					cwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex < endRowIndex) // robot is in upper section
			{
				cwTurn();
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // robot is in lower section
				moveSpace();
		}
		else // On first visit to two-way fork and on subsequent odd visits, do the following:
		{
			if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
					moveSpace();
				else
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze end
					moveSpace();
				else
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex < endRowIndex) // robot is in upper section
			{
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // robot is in lower section
			{
				cwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "right")
	{
		s[rowIndex][colIndex].incrementRightwardVisits();
		if (s[rowIndex][colIndex].getRightwardVisits() % 2 == 1)
		{
			{
				// First work out the cases where the robot is in the same row or column as the maze end
				if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
				{
					if (rowIndex < endRowIndex) // The robot is directly above the maze end
					{
						cwTurn();
						moveSpace();
					}
					else
						moveSpace();
				}
				else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
				{
					if (colIndex < endColIndex) // The robot is directly to the left of the maze end
						moveSpace();
					else
					{
						cwTurn();
						moveSpace();
					}
				}
				else if (rowIndex < endRowIndex) // robot is in upper section
				{
					cwTurn();
					moveSpace();
				}
				else if (rowIndex > endRowIndex)  // robot is in lower section
					moveSpace();
			}
		}
		else // On even visits to the fork, pick the opposite direction
		{
			if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
					moveSpace();
				else
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze end
				{
					cwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex < endRowIndex) // robot is in upper section
				moveSpace();
			else if (rowIndex > endRowIndex)  // robot is in lower section
			{
				cwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "left")
	{
		s[rowIndex][colIndex].incrementLeftwardVisits();
		if (s[rowIndex][colIndex].getLeftwardVisits() % 2 == 0) // On even visits, pick the opposite direction
		{
			{
				// First work out the cases where the robot is in the same row or column as the maze end
				if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
				{
					if (rowIndex < endRowIndex) // The robot is directly above the maze end
					{
						cwTurn();
						moveSpace();
					}
					else
						moveSpace();
				}
				else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
				{
					if (colIndex < endColIndex) // The robot is directly to the left of the maze end
						moveSpace();
					else
					{
						cwTurn();
						moveSpace();
					}
				}
				else if (rowIndex < endRowIndex) // robot is in upper section
				{
					cwTurn();
					moveSpace();
				}
				else if (rowIndex > endRowIndex)  // robot is in lower section
					moveSpace();
			}
		}
		else
		{
			{
				// First work out the cases where the robot is in the same row or column as the maze end
				if (colIndex == endColIndex) // That is, the robot is in the same column as the maze end
				{
					if (rowIndex < endRowIndex) // The robot is directly above the maze end
						moveSpace();
					else
					{
						cwTurn();
						moveSpace();
					}
				}
				else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
				{
					if (colIndex < endColIndex) // The robot is directly to the left of the maze end
					{
						cwTurn();
						moveSpace();
					}
					else
						moveSpace();
				}
				else if (rowIndex < endRowIndex) // robot is in upper section
					moveSpace();
				else if (rowIndex > endRowIndex)  // robot is in lower section
				{
					cwTurn();
					moveSpace();
				}
			}
		}
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

void NavigationRobot::navigateLeftForwardFork()
{
	if (direction == "up")
	{
		s[rowIndex][colIndex].incrementUpwardVisits();
		if (s[rowIndex][colIndex].getUpwardVisits() % 2 == 1) // On first visit to two-way fork 
															  // and on subsequent odd visits, do the following:
		{
			if (colIndex == endColIndex) // The robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
			{
				ccwTurn();
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // Robot is in lower section
				moveSpace();
		}
		else // On even visits pick the opposite direction
		{
			if (colIndex == endColIndex) // The robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
				moveSpace();
			else if (rowIndex > endRowIndex) // Robot is in lower section
			{
				ccwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "down")
	{
		s[rowIndex][colIndex].incrementDownwardVisits();
		if (s[rowIndex][colIndex].getDownwardVisits() % 2 == 0) // On even visits, pick the opposite direction 
		{
			if (colIndex == endColIndex) // The robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
			{
				ccwTurn();
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // Robot is in lower section
				moveSpace();
		}
		else
		{
			if (colIndex == endColIndex) // The robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // The robot is directly above the maze end
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // The robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // The robot is directly to the left of the maze
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
				moveSpace();
			else if (rowIndex > endRowIndex) // Robot is in lower section
			{
				ccwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "right")
	{
		s[rowIndex][colIndex].incrementRightwardVisits();
		if (s[rowIndex][colIndex].getRightwardVisits() % 2 == 1) // On first visit to two-way fork 
																 // and on subsequent odd visits, do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // Robot is directly to the left of the maze
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
				moveSpace();
			else if (rowIndex > endRowIndex) // Robot is in lower section
			{
				ccwTurn();
				moveSpace();
			}	
		}
		else // On even visits, pick the opposite direction
		{
			if (colIndex == endColIndex) // Robot and maze are in the same columnmov
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // Robot is directly to the left of the maze
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
			{
				ccwTurn();
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // Robot is in lower section
				moveSpace();
		}
	}
	else if (direction == "left")
	{
		s[rowIndex][colIndex].incrementLeftwardVisits();
		if (s[rowIndex][colIndex].getLeftwardVisits() % 2 == 0) // On even visits pick the opposite direction
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // Robot is directly to the left of the maze
					moveSpace();
				else
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
				moveSpace();
			else if (rowIndex > endRowIndex) // Robot is in lower section
			{
				ccwTurn();
				moveSpace();
			}
		}
		else // On first visit and subsequent odd visits do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // Robot is directly to the left of the maze
				{
					ccwTurn();
					moveSpace();
				}
				else
					moveSpace();
			}
			else if (rowIndex < endRowIndex) // Robot is in upper section
			{
				ccwTurn();
				moveSpace();
			}
			else if (rowIndex > endRowIndex) // Robot is in lower section
				moveSpace();
		}
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

void NavigationRobot::navigateThreeWayFork()
{
	if (direction == "up")
	{
		s[rowIndex][colIndex].incrementUpwardVisits();
		if (s[rowIndex][colIndex].getUpwardVisits() % 3 == 1) // At every 3n + 1 visits to three-way fork, starting with n = 0, 
															  //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze
				{
					cwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // Robot is directly to the left of maze end
				{
					cwTurn();
					moveSpace();
				}
				else // Robot is directly to the right of maze end
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower left corner
				moveSpace();
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
				moveSpace();
		}
		else if (s[rowIndex][colIndex].getUpwardVisits() % 3 == 2) // At every 3n + 2 visits to three-way fork, starting with n = 0, 
																   //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze
				{
					ccwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
					moveSpace();
				else						 // Robot is directly to the right of maze end
					moveSpace();			 // else statement not needed. It's just to simplify the code
											 // by making it parallel to other cases
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				ccwTurn();
				moveSpace();
			}
		}
		else // At every 3n + 3 visits to three-way fork, starting with n = 0, 
			 //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze
					moveSpace();
				else // Robot is directly below the maze
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex) // Robot is directly to the left of maze end
				{
					ccwTurn();
					moveSpace();
				}
				else // Robot is directly to the right of maze end
				{
					cwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				cwTurn();
				moveSpace();
			}
		}

	}
	else if (direction == "down")
	{
		s[rowIndex][colIndex].incrementDownwardVisits();
		if (s[rowIndex][colIndex].getDownwardVisits() % 3 == 1) // At every 3n + 1 visits to three-way fork, starting with n = 0, 
															    //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
					moveSpace();
				else // Robot is directly below the maze end
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
				{
					ccwTurn();
					moveSpace();
				}
				else						 // Robot is directly to the right of maze end
				{
					cwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				cwTurn();
				moveSpace();
			}
		}
		else if (s[rowIndex][colIndex].getDownwardVisits() % 3 == 2) // At every 3n + 2 visits to three-way fork, starting with n = 0, 
																	 //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
				{
					cwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze end
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
					moveSpace();
				else						 // Robot is directly to the right of maze end
					moveSpace();			 //else statement not needed, but it's included for parallelism
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				ccwTurn();
				moveSpace();
			}
		}
		else // At every 3n + 3 visits to three-way fork, starting with n = 0, 
			 //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
				{
					ccwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze end
					moveSpace();
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
				{
					cwTurn();
					moveSpace();
				}
				else						 // Robot is directly to the right of maze end
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
				moveSpace();
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
				moveSpace();
		}
	}
	else if (direction == "right")
	{
		s[rowIndex][colIndex].incrementRightwardVisits();
		if (s[rowIndex][colIndex].getRightwardVisits() % 3 == 1) // At every 3n + 1 visits to three-way fork, starting with n = 0, 
																 //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
				{
					cwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze end
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
					moveSpace();
				else						 // Robot is directly to the right of maze end
				{
					cwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
				moveSpace();
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				cwTurn();
				moveSpace();
			}
			
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				ccwTurn();
				moveSpace();
			}
		}
		else if (s[rowIndex][colIndex].getRightwardVisits() % 3 == 2) // At every 3n + 2 visits to three-way fork, starting with n = 0, 
																	  //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
					moveSpace();
				else // Robot is directly below the maze end
					moveSpace(); // else statement not needed but included for parallelism
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
				{
					cwTurn();
					moveSpace();
				}
				else						 // Robot is directly to the right of maze end
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
				moveSpace();
		}
		else // At every 3n + 3 visits to three-way fork, starting with n = 0, 
			 //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
				{
					ccwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze end
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
				{
					ccwTurn();
					moveSpace();
				}
				else						 // Robot is directly to the right of maze end
					moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				cwTurn();
				moveSpace();
			}
		}
	}
	else if (direction == "left")
	{
		s[rowIndex][colIndex].incrementLeftwardVisits();
		if (s[rowIndex][colIndex].getLeftwardVisits() % 3 == 1) // At every 3n + 1 visits to three-way fork, starting with n = 0, 
																//do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
				{
					ccwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze end
				{
					cwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
				{
					cwTurn();
					moveSpace();
				}
				else						 // Robot is directly to the right of maze end
					moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
				moveSpace();
		}
		else if (s[rowIndex][colIndex].getLeftwardVisits() % 3 == 2) // At every 3n + 2 visits to three-way fork, starting with n = 0, 
																	 //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
					moveSpace();
				else // Robot is directly below the maze end
					moveSpace(); // else statement not needed, but included for parallelism
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
				{
					ccwTurn();
					moveSpace();
				}
				else						 // Robot is directly to the right of maze end
				{
					cwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
				moveSpace();
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
				moveSpace();
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				cwTurn();
				moveSpace();
			}
		}
		else // At every 3n + 3 visits to three-way fork, starting with n = 0, 
			 //do the following:
		{
			if (colIndex == endColIndex) // Robot and maze end are in the same column
			{
				if (rowIndex < endRowIndex) // Robot is directly above the maze end
				{
					cwTurn();
					moveSpace();
				}
				else // Robot is directly below the maze end
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if (rowIndex == endRowIndex) // Robot and maze end are in the same row
			{
				if (colIndex < endColIndex)  // Robot is directly to the left of maze end
					moveSpace();
				else						 // Robot is directly to the right of maze end
				{
					ccwTurn();
					moveSpace();
				}
			}
			else if ((colIndex < endColIndex) && (rowIndex > endRowIndex)) // Robot is in bottom left corner
			{
				ccwTurn();
				moveSpace();
			}
			else if ((colIndex < endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper left corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex < endRowIndex)) // Robot is in upper right corner
			{
				cwTurn();
				moveSpace();
			}
			else if ((colIndex > endColIndex) && (rowIndex > endRowIndex)) // Robot is in lower right corner
			{
				ccwTurn();
				moveSpace();
			}
		}
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

void NavigationRobot::returnFromDeadEnd()
{
	uTurn();
	while ((position != end) && !rightLeftFork() && !rightForwardFork() && !leftForwardFork() && !threeWayFork())
	{
		if (!barrierAhead() && !virtualBarrierAhead())
		{
			Sleep(500);
			drawVirtualBarrier();
			moveSpace();
		}
		else if (!barrierOnRight() && !virtualBarrierOnRight())
		{
			cwTurn();
			Sleep(500);
			drawVirtualBarrier();
			moveSpace();
		}
		else if (!barrierOnLeft() && !virtualBarrierOnLeft())
		{
			ccwTurn();
			Sleep(500);
			drawVirtualBarrier();
			moveSpace();
		}
		else if (deadEnd())
		{
			output_file << "Error. Stuck in infinite loop" << endl;
			exit(1);
		}

		//Sleep(500);
		createVirtualBarrier();
	}
}

void NavigationRobot::createVirtualBarrier()
{
	if (direction == "right")
		virtualVerticalBarrier[rowIndex][colIndex] = true;
	else if (direction == "left")
		virtualVerticalBarrier[rowIndex][colIndex + 1] = true;
	else if (direction == "down")
		virtualHorizontalBarrier[rowIndex][colIndex] = true;	
	else if (direction == "up")
		virtualHorizontalBarrier[rowIndex + 1][colIndex] = true;
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

void NavigationRobot::drawVirtualBarrier()
{
	cout << "\b ";
	if (direction == "right")
	{
		moveCursorToVerticalBarrier(position, -1);
		changeColor(12);
		cout << "| ";
		changeColor(7);
	}
	else if (direction == "left")
	{
		moveCursorToVerticalBarrier(position, 1);
		changeColor(12);
		cout << "| ";
		changeColor(7);
	}
	else if (direction == "down")
	{
		moveCursorToHorizontalBarrier(position, 1);
		changeColor(9);
		cout << "---";
		changeColor(7);
	}

	else if (direction == "up")
	{
		moveCursorToHorizontalBarrier(position, -1);
		changeColor(9);
		cout << "---";
		changeColor(7);
	}
	else
	{
		output_file << "Error" << endl;
		exit(1);
	}
}

void NavigationRobot::traverse()
{
	while (position != end)
	{
		if (!rightLeftFork() && !rightForwardFork() && !leftForwardFork() && !threeWayFork() )
		{
			if (!barrierAhead() && !virtualBarrierAhead() )
				moveSpace();
			else if (!barrierOnRight() && !virtualBarrierOnRight() )
			{
				cwTurn();
				moveSpace();
			}
			else if (!barrierOnLeft() && !virtualBarrierOnLeft() )
			{
				ccwTurn();
				moveSpace();
			}
			else if (deadEnd())
				returnFromDeadEnd();
		}
		else if (rightLeftFork() )
			navigateRightLeftFork();
		else if (rightForwardFork() )
			navigateRightForwardFork();
		else if (leftForwardFork() )
			navigateLeftForwardFork();
		else if (threeWayFork())
			navigateThreeWayFork();
	}
	moveCursorToBottom();
	output_file << "Congratulations! You completed the maze" << endl;
}