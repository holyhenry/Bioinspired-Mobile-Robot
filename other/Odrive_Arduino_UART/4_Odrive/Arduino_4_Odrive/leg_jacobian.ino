

void compute_jacobian(MatrixXd &J_out, float thetaL, float thetaR, float l1, float l2, float w) {
  
  J_out(0, 0) = 0.5*l1*((pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + (pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5) - pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*cos(thetaR) - sin(thetaR));
  J_out(0, 1) = 0.5*l1*((-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + (-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5) + pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*cos(thetaL) - sin(thetaL));
  J_out(1,0) = -0.5*l1*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*sin(thetaR) + 0.5*l1*cos(thetaR) + 0.5*(pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + 0.5*(pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5);
  J_out(1,1) = 0.5*l1*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*sin(thetaL) + 0.5*l1*cos(thetaL) + 0.5*(-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + 0.5*(-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5);
  
}

void test_jacobian(float l1, float l2, float w) {
  MatrixXd J(2, 2);
  MatrixXd J_inv(2, 2);
  float thetaL = 0;
  float thetaR = 0;


  Serial.println("Printing jacobian test");
  // 0,0
  //      [[-0.20073208,  0.20073208],
  //       [ 0.045     ,  0.045     ]]
  thetaL = 0;
  thetaR = 0;
  compute_jacobian(J, thetaL, thetaR, l1, l2, w);
  Serial << "ThetaL = " << thetaL << "\tThetaR = " << thetaR << "\n";
  Serial.print("Arduino\t\t");
  Serial.print(J(0,0), 5);
  Serial.print(", \t");
  Serial.println(J(0,1), 5);
  Serial.print("\t\t");
  Serial.print(J(1,0), 5);
  Serial.print(", \t");
  Serial.println(J(1,1), 5);
  
  Serial.print("Actual \t\t");
  Serial.print(-0.20073208, 5);
  Serial.print(", \t");
  Serial.println(0.20073208, 5);
  Serial.print("\t\t");
  Serial.print( 0.045, 5);
  Serial.print(", \t");
  Serial.println( 0.045, 5);
 
  
  // pi/2,pi/2
  //      [[-0.045     , -0.045     ],
  //       [ 0.01008807, -0.01008807]
  thetaL = PI/2;
  thetaR = PI/2;
  compute_jacobian(J, thetaL, thetaR, l1, l2, w);
  Serial << "ThetaL = " << thetaL << "\tThetaR = " << thetaR << "\n";
  
  Serial.print("Arduino\t\t");
  Serial.print(J(0,0), 5);
  Serial.print(", \t");
  Serial.println(J(0,1), 5);
  Serial.print("\t\t");
  Serial.print(J(1,0), 5);
  Serial.print(", \t");
  Serial.println(J(1,1), 5);
  
  Serial.print("Actual \t\t");
  Serial.print(-0.045, 5);
  Serial.print(", \t");
  Serial.println(-0.045, 5);
  Serial.print("\t\t");
  Serial.print( 0.01008807, 5);
  Serial.print(", \t");
  Serial.println(-0.01008807, 5);
  
  // pi/4,3*pi/4
  //      [[-0.07245831, -0.07245831],
  //      [ 0.0567346 , -0.0567346 ]]
  thetaL = 3*PI/4;
  thetaR = PI/3;
  compute_jacobian(J, thetaL, thetaR, l1, l2, w);
  Serial << "ThetaL = " << thetaL << "\tThetaR = " << thetaR << "\n";
  Serial.print("Arduino\t\t");
  Serial.print(J(0,0), 5);
  Serial.print(", \t");
  Serial.println(J(0,1), 5);
  Serial.print("\t\t");
  Serial.print(J(1,0), 5);
  Serial.print(", \t");
  Serial.println(J(1,1), 5);
  
  Serial.print("Actual \t\t");
  Serial.print(-0.07245831, 5);
  Serial.print(", \t");
  Serial.println(-0.07245831, 5);
  Serial.print("\t\t");
  Serial.print( 0.0567346, 5);
  Serial.print(", \t");
  Serial.println(-0.0567346, 5);

  // pi/8, pi
  //      [[-0.05515189, -0.03579581],
  //      [ 0.04976563, -0.05770009]]
  thetaL = PI;
  thetaR = PI/8;
  compute_jacobian(J, thetaL, thetaR, l1, l2, w);
  Serial << "ThetaL = " << thetaL << "\tThetaR = " << thetaR << "\n";
  Serial.print("Arduino\t\t");
  Serial.print(J(0,0), 5);
  Serial.print(", \t");
  Serial.println(J(0,1), 5);
  Serial.print("\t\t");
  Serial.print(J(1,0), 5);
  Serial.print(", \t");
  Serial.println(J(1,1), 5);
  
  Serial.print("Actual \t\t");
  Serial.print(-0.05515189, 5);
  Serial.print(", \t");
  Serial.println(-0.03579581, 5);
  Serial.print("\t\t");
  Serial.print( 0.04976563, 5);
  Serial.print(", \t");
  Serial.println(-0.05770009, 5);


  ////////////////////////////////////////////////////////////

  Serial.println("Printing jacobian Transpose");
  thetaL = PI;
  thetaR = PI/8;
  compute_jacobian(J, thetaL, thetaR, l1, l2, w);
  J_inv = J.transpose();
  
  Serial << "ThetaL = " << thetaL << "\tThetaR = " << thetaR << "\n";
  Serial.print("Arduino\t\t");
  Serial.print(J_inv(0,0), 5);
  Serial.print(", \t");
  Serial.println(J_inv(0,1), 5);
  Serial.print("\t\t");
  Serial.print(J_inv(1,0), 5);
  Serial.print(", \t");
  Serial.println(J_inv(1,1), 5);
  
  
}
