package turtlebot3_environment_scanner;

public interface tb_cloud_points extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "turtlebot3_environment_scanner/tb_cloud_points";
  static final java.lang.String _DEFINITION = "float64[360] cloud_x\nfloat64[360] cloud_y\nfloat64 tb_x\nfloat64 tb_y\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  double[] getCloudX();
  void setCloudX(double[] value);
  double[] getCloudY();
  void setCloudY(double[] value);
  double getTbX();
  void setTbX(double value);
  double getTbY();
  void setTbY(double value);
}
