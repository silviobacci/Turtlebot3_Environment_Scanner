#!/usr/bin/env sh

"./compile.sh"

COMMAND_01="roslaunch turtlebot3_gazebo turtlebot3_world.launch"
COMMAND_02="rosrun teleop_twist_keyboard teleop_twist_keyboard.py"
COMMAND_03="rosrun $PROJECT_FOLDER_NAME $PROJECT_NODE_NAME"

gnome-terminal --tab -e "$COMMAND_01" --tab -e "$COMMAND_02" --tab -e "$COMMAND_03"
