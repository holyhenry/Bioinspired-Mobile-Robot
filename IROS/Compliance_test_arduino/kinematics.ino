void forward_kinematics(Matrix2d &FK, float thetaL, float thetaR, float l1, float l2, float w) {
    float x, y;
    float a, alpha, L, beta, thetaL2;
    
    a       = sqrt(pow(w, 2) + pow(l1, 2) - 2 * w * l1 * cos(thetaR));
    alpha   = asin(l1 * sin(thetaR) / a);
    L       = sqrt(pow(l1, 2) + pow(a, 2) - 2 * l1 * a * cos(PI - alpha - thetaL));
    beta    = asin(a * sin(PI - alpha - thetaL) / L);
    thetaL2 = PI - beta;

    Matrix3d T01;
    Matrix3d T12;
    Vector3d p;
    Vector3d FK_full;
    
    T01 << cos(thetaL), -sin(thetaL),  w/2, 
           sin(thetaL), cos(thetaL) ,  0  ,
           0          , 0           ,  1  ;
           
    T12 << cos(thetaL2), -sin(thetaL2), l1, 
           sin(thetaL2), cos(thetaL2) ,  0,
           0           , 0            ,  1;
           
    p << L/2                              , 
         -sqrt(pow(l2, 2) - pow((L/2), 2)),
         1                                ;
    
    FK_full =  T01 * T12 * p;
    FK(0,0) = FK_full(0,0);
    FK(1,0) = FK_full(1,0);
    
}

// precalculated jacobian
void compute_jacobian(MatrixXd &J_out, float thetaL, float thetaR, float l1, float l2, float w) {
  
  J_out(0, 0) = 0.5*l1*((pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + (pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5) - pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*cos(thetaR) - sin(thetaR));
  J_out(0, 1) = 0.5*l1*((-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + (-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(sin(thetaL) - sin(thetaR))*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5) + pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*cos(thetaL) - sin(thetaL));
  J_out(1,0) = -0.5*l1*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*sin(thetaR) + 0.5*l1*cos(thetaR) + 0.5*(pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + 0.5*(pow(l1, 2)*sin(thetaL - thetaR) + l1*w*sin(thetaR))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5);
  J_out(1,1) = 0.5*l1*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2))*sin(thetaL) + 0.5*l1*cos(thetaL) + 0.5*(-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -1.5)*sqrt(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2)) + 0.5*(-pow(l1, 2)*sin(thetaL - thetaR) - l1*w*sin(thetaL))*(-l1*cos(thetaL) + l1*cos(thetaR) + w)*pow(-2.0*pow(l1, 2)*cos(thetaL - thetaR) + 2.0*pow(l1, 2) - 2.0*l1*w*cos(thetaL) + 2.0*l1*w*cos(thetaR) + pow(w, 2), -0.5)*pow(2.0*pow(l1, 2)*cos(thetaL - thetaR) - 2.0*pow(l1, 2) + 2.0*l1*w*cos(thetaL) - 2.0*l1*w*cos(thetaR) + 4.0*pow(l2, 2) - pow(w, 2), -0.5);
  
}
