#include "Potentials.h"

namespace libpot{

double Gay_Berne(VECTOR& ri,VECTOR& rj,VECTOR& ui,VECTOR& uj,          /*Inputs*/
                 VECTOR& fi,VECTOR& fj,VECTOR& ti,VECTOR& tj,          /*Outputs*/
                 double di, double dj,double li,double lj,
                 double e0,double rat,double dw,double mu,double nu){  /*Parameters*/
//****************** double Gay-Berne potential ******************************
//*                                                                          *
//*       E = 4*epsilon*[R^12 - R^6]                                         *
//*       R = dw*sigma_0 / (rij - sigma + dw*sigma_0)                        *
//*       epsilon = e0 * e1^mu * e2^nu                                       *
//*                                                                          *
//* As described in:                                                         *
//* Golubkov, P. A.; Ren. P. "Generalized coarse-grained model based on point*
//* multipole an Gay-Berne potentials" J. Chem. Phys., 2006, 125, 064103-1-11*
//****************************************************************************

  double energy = 0.0;
  double s0, xa2,xam2,x2,xp,ap2,rat_pow;
  double e1,e2,s;
  double R,H,Hp,e;
  double R3,R6,R12;
  double dUdr,dUda,dUdb,dUdg;
  double a,b,g;


  VECTOR rij = ri - rj;
  VECTOR rij_hat  = rij.unit();
  VECTOR ui_hat = ui.unit();
  VECTOR uj_hat = uj.unit();
  double d = rij.length();
 

  xa2 = (li*li-di*di)/(li*li+dj*dj);
  xam2= (lj*lj-dj*dj)/(lj*lj+di*di);
  x2  = xa2*xam2;
  if(mu==2.0){ rat_pow = sqrt(rat); }
  else{ rat_pow = pow(rat, (1.0/mu)); }
  xp = (1.0-rat_pow)/(1.0+rat_pow); 
  ap2 = 1.0/(1.0+rat_pow); 

  a = ui_hat*rij_hat;
  b = uj_hat*rij_hat;
  g = ui_hat*uj_hat;


  H  = ( xa2*a + xam2*b - 2.0*x2*a*b*g )/( 1.0-x2*g*g ) ;
  Hp = ( xp*ap2*a + (xp/ap2)*b - 2.0*xp*xp*a*b*g )/( 1.0-xp*xp*g*g ) ;

  e1  = 1.0/sqrt(1.0 - x2*g*g);
  e2  = 1.0 - Hp;
  e   = (e0)*(e1)*(e2*e2);

  s0  = sqrt(di*di + dj*dj);
  s = s0/sqrt(1.0 - H);
  R = dw*s0/(d-s+dw*s0);



  R3 = R*R*R;
  R6 = R3*R3;
  R12 = R6*R6;
  energy = 4.0*e*(R12-R6);

  //-------------- Derivatives ----------------------
  dUdr = (8.0*e*mu*Hp/(e2*d))*(R12-R6) - (24.0*e/(dw*s0))*R*(2.0*R12-R6)*(1.0+(s*s*s*H/(s0*s0*d)));

  dUda = (-8.0*e*mu/(d*e2))*(R12-R6)*(xp*ap2*a-xp*xp*b*g)/(1.0-xp*xp*g*g)+
         ( 24.0*e*s*s*s/(d*s0*s0*s0*dw))*R*(2.0*R12-R6)*(xa2*a-x2*b*g)/(1.0-x2*g*g);

  dUdb = (-8.0*e*mu/(d*e2))*(R12-R6)*((xp/ap2)*b-xp*xp*a*g)/(1.0-xp*xp*g*g)+
         ( 24.0*e*s*s*s/(d*s0*s0*s0*dw))*R*(2.0*R12-R6)*(xam2*b-x2*a*g)/(1.0-x2*g*g);

  dUdg = (4.0*e*nu)*(R12-R6)*(x2*g)/(1.0-x2*g*g)+
         ((8.0*e*mu/e2)*(R12-R6)*(xp*xp*a*b-Hp*xp*xp*g)/(1.0-xp*xp*g*g))+
         ( 24.0*e*s*s*s/(s0*s0*s0*dw))*R*(R6-2.0*R12)*(x2*a*b-H*x2*g)/(1-x2*g*g);


  fi = (-dUdr*rij_hat-dUda*ui_hat-dUdb*uj_hat);
  fj = -fi;

  ti = (cross(dUda,rij,ui_hat)+cross(dUdg,uj_hat,ui_hat));
  tj = (cross(dUdb,rij,uj_hat)+cross(dUdg,ui_hat,uj_hat));

  return energy;
}

}// namespace libpot
