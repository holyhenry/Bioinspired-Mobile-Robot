#include <ODriveArduino.h>
#include <stlport.h>
#include <Eigen30.h>

using Eigen::MatrixXd;

MatrixXd T(3, 3);
static float dis_x = 0.09;
static float dis_y = 0;
static float theta = PI/6;

void setup()
{
   Serial.begin(115200);

   get_transmision_matrix(T, dis_x, dis_y, theta);
  /* add setup code here */
   //   m(0, 0) = 3;
   //   m(1, 0) = 2.5;
   //   m(0, 1) = -1;
   //   m(1, 1) = m(1, 0) + m(0, 1);

}

void loop()
{

  /* add main program code here */
   Serial.print(T(0,0), 5);
   Serial.print(", \t");
   Serial.println(T(0,1), 5);
   Serial.print("\t\t");
   Serial.print(T(1,0), 5);
   Serial.print(", \t");
   Serial.println(T(1,1), 5);
  
     
     delay(2000);
}
