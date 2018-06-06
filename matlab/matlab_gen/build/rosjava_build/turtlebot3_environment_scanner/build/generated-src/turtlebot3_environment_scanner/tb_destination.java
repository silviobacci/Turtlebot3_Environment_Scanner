package turtlebot3_environment_scanner;

public interface tb_destination extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "turtlebot3_environment_scanner/tb_destination";
  static final java.lang.String _DEFINITION = "float64 final_destination_x\nfloat64 final_destination_y\nfloat64 destination_x\nfloat64 destination_y\nfloat64 motion_state\nfloat64 tb_x\nfloat64 tb_y\nfloat64 tb_yaw\nfloat64 tb_linear_velocity\nfloat64 tb_angular_velocity\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  double getFinalDestinationX();
  void setFinalDestinationX(double value);
  double getFinalDestinationY();
  void setFinalDestinationY(double value);
  double getDestinationX();
  void setDestinationX(double value);
  double getDestinationY();
  void setDestinationY(double value);
  double getMotionState();
  void setMotionState(double value);
  double getTbX();
  void setTbX(double value);
  double getTbY();
  void setTbY(double value);
  double getTbYaw();
  void setTbYaw(double value);
  double getTbLinearVelocity();
  void setTbLinearVelocity(double value);
  double getTbAngularVelocity();
  void setTbAngularVelocity(double value);
}
