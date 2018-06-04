package turtlebot3_environment_scanner;

public interface obstacle_point extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "turtlebot3_environment_scanner/obstacle_point";
  static final java.lang.String _DEFINITION = "float64 x\nfloat64 y\nfloat32 angle\nfloat32 distance\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  double getX();
  void setX(double value);
  double getY();
  void setY(double value);
  float getAngle();
  void setAngle(float value);
  float getDistance();
  void setDistance(float value);
}
