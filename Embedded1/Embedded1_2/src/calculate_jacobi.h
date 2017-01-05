#ifndef CALCULATE_JACOBI_H
#define CALCULATE_JACOBI_H

//for eigen
#include <Eigen/Dense>
#include <Eigen/SVD>
#include <Eigen/Core>
#include <QObject>

#define PI 3.141592654

using namespace Eigen;

class calculate_jacobi:public QObject
{
    Q_OBJECT
public:
    explicit calculate_jacobi(QObject *parent=0);
    void update_inter_para();
    void InitPara(double phi_input,double theta1L_input,double delta1_input,double L1_input,
                  double theta2L_input,double delta2_input);
    Matrix<double,3,3> Rotdx(double angle);
    Matrix<double,3,3> Rotdy(double angle);
    Matrix<double,3,3> Rotdz(double angle);
    Matrix<double,3,2> calculate_Jv(double thetaL,double delta,double L);
    Matrix<double,3,2> calculate_Jw(double thetaL,double delta);
    Matrix<double,3,3> skew_sym(Vector3d vector);
    Matrix<double,6,6> jacobi();
    Matrix<double,4,4> Transformation_matrix();
    Matrix<double,6,1> resolved_rates(Matrix<double,4,4> T);
    Vector3d rot_r(Matrix3d R);
    double rot_theta(Matrix3d R);
    Matrix<double,6,6> pinv(Matrix<double,6,6> J);

private:
    double phi;
    double theta1L;
    double delta1;
    double L1;
    double theta2L;
    double delta2;
    double L2;
    double gripper,v_lim,w_lim,delta_t;
    Vector3d P1b_1L,P2b_2L,Pg_g,t1,P0b_g;
    Matrix<double,3,3> R0b_1b,R1b_2b,R2b_2e,R2e_g;
    Matrix<double,3,2> J1v,J1w,J2v,J2w;
};



#endif // CALCULATE_JACOBI_H
