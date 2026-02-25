# Micromouse
This project is divided into two parts. The first part is C++ code which solves a maze *from the perspective of the robot.*
The robot does not have a bird's-eye view of the maze and can only see spaces/walls in front of it, as well as spaces/walls
on its sides. There are two components to this algorithm. The first is a dead-end filler. That is, if the robot reaches a dead end,
it will return to the maze fork that led it to the dead-end, while also creating a virtual barrier behind itself, so that it
knows not to take that path again. The second component of that algorithm is a method to navigate forks. Say, for example, that the robot moves 
upwards from space D5 to space C5, and there is a barried ahead (therefore, the robot cannot move to B5) with open spaces on the right (C6)
and the left (C4). The first time the robot reaches C5 as it comes from D5, it will go towards the direction of the maze end. If the maze end is in columns 1-4,
it will go left. Otherwise, it will go right. The second time the robot reaches C5 coming from D5, it will go in the opposite direction of how
it went the first time. Should the robot move from D5 to C5 another time, it will do as follows: on odd-numbered moves, it will turn as it did the
first time, while on even-numbered moves, it will turn as it did the second time.

The second part of this project is a wall follower algorithm in Arduino. The algorithm is designed such that the robot
follows the left wall until it reaches the end of the maze. The robot also utilizes a feedback algorithm which centers it should
the robot veer too far off to either side. There is another feedback algorithm, in which, if the robot is stuck at a wall for a while,
it backs up and straightens out. Since the motors in this project did not have encoders, the feedback is from the sensors.
