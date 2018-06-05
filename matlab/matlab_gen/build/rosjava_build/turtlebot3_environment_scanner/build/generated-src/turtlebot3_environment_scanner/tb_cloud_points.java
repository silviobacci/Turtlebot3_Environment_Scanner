package turtlebot3_environment_scanner;

public interface tb_cloud_points extends org.ros.internal.message.Message {
  static final java.lang.String _TYPE = "turtlebot3_environment_scanner/tb_cloud_points";
  static final java.lang.String _DEFINITION = "float64[360] cloud_x\nfloat64[360] cloud_y\nfloat32[360] angle\nfloat32[360] distance\nfloat64 tb_x\nfloat64 tb_y\nfloat32 angle_min\nfloat32 angle_max\nfloat32 angle_increment\nfloat32 min_distance\nfloat32 max_distance\n";
  static final boolean _IS_SERVICE = false;
  static final boolean _IS_ACTION = false;
  double[] getCloudX();
  void setCloudX(double[] value);
  double[] getCloudY();
  void setCloudY(double[] value);
  float[] getAngle();
  void setAngle(float[] value);
  float[] getDistance();
  void setDistance(float[] value);
  double getTbX();
  void setTbX(double value);
  double getTbY();
  void setTbY(double value);
  float getAngleMin();
  void setAngleMin(float value);
  float getAngleMax();
  void setAngleMax(float value);
  float getAngleIncrement();
  void setAngleIncrement(float value);
  float getMinDistance();
  void setMinDistance(float value);
  float getMaxDistance();
  void setMaxDistance(float value);
}
