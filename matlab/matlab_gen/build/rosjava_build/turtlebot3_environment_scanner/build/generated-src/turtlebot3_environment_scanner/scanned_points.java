package turtlebot3_environment_scanner;

public interface scanned_points extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "turtlebot3_environment_scanner/scanned_points";
  static final java.lang.String _DEFINITION = "obstacle_point[360] obstacle\nfloat32 min_distance\nfloat32 max_distance\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  java.util.List<turtlebot3_environment_scanner.obstacle_point> getObstacle();
  void setObstacle(java.util.List<turtlebot3_environment_scanner.obstacle_point> value);
  float getMinDistance();
  void setMinDistance(float value);
  float getMaxDistance();
  void setMaxDistance(float value);
}
