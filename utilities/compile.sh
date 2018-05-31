#!/usr/bin/env sh

read_project_info() 
{
	FILENAME=".project_info"
	while read -r project_info
	do
		case $project_info in 
			*"PROJECT_FOLDER_NAME"*)
				PROJECT_FOLDER_NAME=${project_info##*=};;
			*"PROJECT_NODE_NAME"*)
				PROJECT_NODE_NAME=${project_info##*=};;
		esac
	done < $FILENAME

	echo 'PROJECT_FOLDER_NAME=$PROJECT_FOLDER_NAME; PROJECT_NODE_NAME=$PROJECT_NODE_NAME'
}

eval $(read_project_info)
echo  $PROJECT_FOLDER_NAME $PROJECT_NODE_NAME
#catkin_make $PROJECT_FOLDER_NAME $PROJECT_NODE_NAME
