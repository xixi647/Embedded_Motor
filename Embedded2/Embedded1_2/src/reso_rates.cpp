#include "reso_rates.h"
#include <math.h>
#include <iomanip>
#include <iostream>

using namespace std;

Reso_Rates::Reso_Rates(QObject *parent) :
    QObject(parent)
{
}
void Reso_Rates::InitPara(double phi_input, double theta1L_input, double delta1_input, double L1_input,
                           double theta2L_input, double delta2_input)
{
    phi=phi_input;
    theta1L=theta1L_input;
    delta1=delta1_input;
    L1=L1_input;
    theta2L=theta2L_input;
    delta2=delta2_input;
    L2=25;
    gripper=5;
    v_lim=10;w_lim=PI/2;delta_t=0.002;
    epsilon_P_desired=1;
    epsilon_R_desired=0.017;
    update_inter_para();
}

Matrix<double,6,1> Reso_Rates::resolved_rates(Matrix<double,4,4> T)
{
    //update inter parameters
    update_inter_para();
    //update target position and orientation
    Vector3d P_t=T.block<3,1>(0,3);
    Matrix3d R_t=T.block<3,3>(0,0);
    //calculate current position and orientation
    Matrix<double,4,4> T_c=Transformation_matrix();
    Vector3d P_c=T_c.block<3,1>(0,3);
    Matrix3d R_c=T_c.block<3,3>(0,0);
    //update q_c
    Matrix<double, 6, 1> q_c;
    q_c<<phi,theta1L,delta1,L1,theta2L,delta2;
    //calcualte x_dot
    Matrix<double,6,1> x_dot;
    Vector3d temp=P_t-P_c;
    double epsilon_P=temp.norm();
    double epsilon_R=rot_theta(R_t*R_c.transpose());
    Vector3d x_dot_v,x_dot_w;
    //set x_dot_v
    if(epsilon_P>=epsilon_P_desired)
        x_dot_v=v_lim*(temp)/epsilon_P;
    else if(epsilon_P<epsilon_P_desired && epsilon_P>0.01)
        x_dot_v=v_lim/10*(temp)/epsilon_P;
    else
        x_dot_v=temp;
    //set x_dot_w
    if(epsilon_R>=epsilon_R_desired)
        x_dot_w=w_lim*rot_r(R_t*R_c.transpose());
    else
        x_dot_w=w_lim/10*rot_r(R_t*R_c.transpose());

    x_dot.block<3,1>(0,0)=x_dot_v;
    x_dot.block<3,1>(3,0)=x_dot_w;



    //calcualte inverse jacobi
    Matrix<double,6,6> J=jacobi();
    //calculate q_dot
    Matrix<double,6,1> q_dot;
//    cout<<"update_inter_para()=====x_dot\n"<<x_dot<<endl;
    q_dot=pinv(J)*x_dot;
    // update q_c
    q_c=q_c+q_dot*delta_t;

    //we need update phi thtea1L...
    phi=q_c(0);
    theta1L=q_c(1);
    delta1=q_c(2);
    L1=q_c(3);
    theta2L=q_c(4);
    delta2=q_c(5);

    return q_c;

}

Matrix<double,6,6> Reso_Rates::jacobi()
{
    Vector3d z_0_1=Vector3d::UnitZ();
    Matrix<double,3,1> J11=z_0_1.cross(P0b_g);
    Matrix<double,3,1> J21=z_0_1;

    Matrix<double,3,3> temp=skew_sym(R1b_2b*P2b_2L+R1b_2b*R2b_2e*R2e_g*Pg_g);
    Matrix<double,3,2> J12=R0b_1b*(J1v-temp*J1w);
    Matrix<double,3,2> J22=R0b_1b*J1w;

    temp=skew_sym(R2b_2e*R2e_g*Pg_g);
    Matrix<double,3,2> J14=R0b_1b*R1b_2b*(J2v-temp*J2w);
    Matrix<double,3,2> J24=R0b_1b*R1b_2b*J2w;

    Matrix<double,6,6> jacobi;
    jacobi<<J11,J12,R0b_1b*t1,J14,J21,J22,MatrixXd::Zero(3,1),J24;
    return jacobi;
}

Matrix<double,4,4> Reso_Rates::Transformation_matrix()
{
      Matrix<double,4,4>  T;
      T<<R0b_1b*R1b_2b*R2b_2e*R2e_g,P0b_g,MatrixXd::Zero(1,3),1;
      return T;
}

void Reso_Rates::update_inter_para()
{
    if (abs(theta1L-PI/2)>0.001)
    {
        P1b_1L<<cos(delta1)*(sin(theta1L)-1),sin(delta1)*(1-sin(theta1L)),-cos(theta1L);
        P1b_1L=P1b_1L*L1/(theta1L-PI/2);
    }
    else
    {
        P1b_1L<<0,0,L1;
    }
    if (abs(theta2L-PI/2)>0.001)
    {
        P2b_2L<<cos(delta2)*(sin(theta2L)-1),sin(delta2)*(1-sin(theta2L)),-cos(theta2L);
        P2b_2L=P2b_2L*L2/(theta2L-PI/2);
    }
    else
    {
        P2b_2L<<0,0,L2;
    }

    Pg_g<<0,0,gripper;


//    cout<<"P1b_1L is:\n"<<P1b_1L<<endl;
//    cout<<"P2b_2L is:\n"<<P2b_2L<<endl;
//    cout<<"Pg_g is:\n"<<Pg_g<<endl;

    R0b_1b=Rotdz(phi);

    Matrix<double,3,3> temp1=Rotdz(-delta1);
    Matrix<double,3,3> temp2=Rotdy(PI/2-theta1L);
    Matrix<double,3,3> temp3=Rotdz(delta1);
    R1b_2b=temp1*temp2*temp3;

    temp1=Rotdz(-delta2);
    temp2=Rotdy(PI/2-theta2L);
    temp3=Rotdz(delta2);
    R2b_2e=temp1*temp2*temp3;

    R2e_g.setIdentity();

//    cout<<"R0b_1b is:\n"<<R0b_1b<<endl;
//    cout<<"R1b_2b is:\n"<<R1b_2b<<endl;
//    cout<<"R2b_2e is:\n"<<R2b_2e<<endl;
//    cout<<"R2e_g is:\n"<<R2e_g<<endl;
    P0b_g=R0b_1b*P1b_1L+R0b_1b*R1b_2b*P2b_2L+R0b_1b*R1b_2b*R2b_2e*R2e_g*Pg_g;

    J1v=calculate_Jv(theta1L,delta1,L1);
    J1w=calculate_Jw(theta1L,delta1);

    J2v=calculate_Jv(theta2L,delta2,L2);
    J2w=calculate_Jw(theta2L,delta2);

//    cout<<"J1v is:\n"<<J1v<<endl;
//    cout<<"J1w is:\n"<<J1w<<endl;
    if (abs(theta1L-PI/2)>0.001)
    {
        t1<<cos(delta1)*(sin(theta1L)-1),sin(delta1)*(1-sin(theta1L)),-cos(theta1L);
        t1=t1/(theta1L-PI/2);
    }
    else
    {
        t1<<0,0,1;
    }
}


// subfunctions

Matrix<double, 3, 2> Reso_Rates::calculate_Jv(double thetaL,double delta,double L)
{
    Matrix<double, 3, 2> Jv;
    if (abs(thetaL-PI/2)>0.001)
    {
    double J11=L*cos(delta)*((thetaL-PI/2)*cos(thetaL)-sin(thetaL)+1)/pow((PI/2-thetaL),2);
    double J12=-L*sin(delta)*(sin(thetaL)-1)/(thetaL-PI/2);
    double J21=-L*sin(delta)*((thetaL-PI/2)*cos(thetaL)-sin(thetaL)+1)/pow((PI/2-thetaL),2);
    double J22=-L*cos(delta)*(sin(thetaL)-1)/(thetaL-PI/2);
    double J31=L*((thetaL-PI/2)*sin(thetaL)+cos(thetaL))/pow((PI/2-thetaL),2);
    Jv<<J11,J12,J21,J22,J31,0;
    }
    else
    {
        Jv<<-L*cos(delta)/2,0,L*sin(delta)/2,0,0,0;
    }
    return Jv;
}

Matrix<double, 3, 2> Reso_Rates::calculate_Jw(double thetaL,double delta)
{
    Matrix<double, 3, 2> Jw;
    if (abs(thetaL-PI/2)>0.001)
    {
        Jw<<-sin(delta),cos(delta)*cos(thetaL),-cos(delta),-sin(delta)*cos(thetaL),0,-1+sin(thetaL);
    }
    else
    {
        Jw<<-sin(delta),0,-cos(delta),0,0,0;
    }
    return Jw;
}

Matrix<double,3,3> Reso_Rates::skew_sym(Vector3d vector)
{
    Matrix<double,3,3> skew;
    skew<<0,-vector(2),vector(1),vector(2),0,-vector(0),-vector(1),vector(0),0;
    return skew;
}



Matrix<double, 3, 3> Reso_Rates::Rotdx(double angle)
{
    Matrix<double,3,3> Rotd;
    Rotd<<1,0,0,0,cos(angle),-sin(angle),0,sin(angle),cos(angle);
    return Rotd;
}

Matrix<double,3,3> Reso_Rates::Rotdy(double angle)
{
    Matrix<double,3,3> Rotd;
    Rotd<<cos(angle),0,sin(angle),0,1,0,-sin(angle),0,cos(angle);
    return Rotd;
}

Matrix<double,3,3> Reso_Rates::Rotdz(double angle)
{
    Matrix<double,3,3> Rotd;
    Rotd<<cos(angle),-sin(angle),0,sin(angle),cos(angle),0,0,0,1;
    return Rotd;
}

Vector3d Reso_Rates::rot_r(Matrix3d R)
{
    Vector3d r;
    r<<R(2,1)-R(1,2),R(0,2)-R(2,0),R(1,0)-R(0,1);
    double temp;
    temp=rot_theta(R);
    if(sin(temp)!=0){
        r=r/(2*sin(temp));
    }
    else{
        r=r*0;
    }
    return r;
}

double Reso_Rates::rot_theta(Matrix3d R)
{
    return acos((R.trace()-1)/2);
}

Matrix<double,6,6> Reso_Rates::pinv(Matrix<double,6,6> J)
{
        SVD<MatrixXd> svd(J);
        VectorXd singular;
        VectorXd singular_inv;
        Matrix<double,6,6> pinv;
        singular=svd.singularValues();
        singular_inv=singular;
        double  pinvtoler=1.e-5; // choose your tolerance wisely!
        //double  pinvtoler=A.rows()*A.norm()*2.2e-16;
         for ( long i=0; i<singular.rows(); ++i)
         {
            if ( singular(i) > pinvtoler )
            {
               singular_inv(i)=1.0/singular(i);
    //        cout<<"singular_inv"<<i<<"is"<<singular_inv(i)<<endl;
            }
           else singular_inv(i)=0;
         }
        pinv= (svd.matrixV()*singular_inv.asDiagonal()*svd.matrixU().transpose());
        return pinv;
}
