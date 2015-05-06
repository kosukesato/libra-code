#include "RigidBody.h"

namespace librigidbody{

void RigidBody::rotate_no_squish(int k,double dt){
  double zeta,cos_zeta,sin_zeta, rot_const;
  MATRIX P(4,4);

  if(k==1) { P = *P1; rot_const = rb_A;}
  else if(k==2) { P = *P2; rot_const = rb_B;}
  else if(k==3) { P = *P3; rot_const = rb_C;}


  zeta = 0.25*rot_const*dt*dot_prod(rb_p_r,P*rb_L);
  cos_zeta = cos(zeta);
  sin_zeta = sin(zeta);

  rb_L = cos_zeta * rb_L + sin_zeta * P*rb_L;
  rb_p_r = cos_zeta * rb_p_r + sin_zeta * P*rb_p_r;

}

void RigidBody::propagate_no_squish(double t){

  double t_half = 0.5 * t;

  rotate_no_squish(3,t_half);
  rotate_no_squish(2,t_half);
  rotate_no_squish(1,t);
  rotate_no_squish(2,t_half);
  rotate_no_squish(3,t_half);

  set_orientation(rb_L);
  set_quaternion_momentum(rb_p_r);

}

}// namespace librigidbody
