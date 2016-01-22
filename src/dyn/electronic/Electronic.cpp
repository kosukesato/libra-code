/*********************************************************************************
* Copyright (C) 2015 Alexey V. Akimov
*
* This file is distributed under the terms of the GNU General Public License
* as published by the Free Software Foundation, either version 2 of
* the License, or (at your option) any later version.
* See the file LICENSE in the root directory of this distribution
* or <http://www.gnu.org/licenses/>.
*
*********************************************************************************/
/**
  \file Electronic.cpp
  \brief The file implements Electronic class methods and functions for propagation of electronic DOF
    
*/

#include "Electronic.h"

/// libdyn namespace 
namespace libdyn{

/// libelectronic namespace 
namespace libelectronic{

using namespace libmmath;


Electronic& Electronic::operator=(const Electronic& ob){  
/**
  \brief An assignment operator

*/

  *rnd_obj = *ob.rnd_obj;
  nstates = ob.nstates;
  istate = ob.istate;
  q = ob.q;
  p = ob.p;

  return *this; // return reference to allow chaining: A = B = C =...
}


void Electronic::rnd_phase(double& x, double& y, double nrm){ 
/**
  \brief An auxiliary function to generate a random (uniform distribution) phase complex number

  \param[out] x The real component of the complex number generated
  \param[out] y The imaginary component of the complex number generated
  \param[in] nrm The norm of the generated random number

*/                                         

  double phi = rnd_obj->uniform(0.0,1.0);
  x = std::sqrt(nrm) * std::cos(M_PI*phi); 
  y = std::sqrt(nrm) * std::sin(M_PI*phi); 
}

void Electronic::init(int n_,int st){
/**
  \brief An auxiliary function to initialize (or reinitialize the Electronic object)

  This function allocates memory for time-dependent wfc with n_ stationary states
  Then it initializes the overall multiconfigurational wfc
  to be a 1-configurational, with the weight 1 set to basis state with index st
  and with a random phase

  \param[in] n_ The number of electronic states to include: the dimensionality of the electronic problem
  \param[in] st The index of electronic state to which we initialize the system 

*/
  rnd_obj = new Random();

  if(st>=n_){ std::cout<<"Error in Electronic::init - st("<<st<<") must be smaller than n_("<<n_<<")\n"; exit(0); }

  nstates = n_;
  q = std::vector<double>(n_,0.0);
  p = std::vector<double>(n_,0.0); 

  istate = st;
  rnd_phase(q[istate],p[istate],1.0);   // populate only istate-th state

}

//
// Overloaded version
//
void Electronic::init(int n_){ 
/**
  \brief An auxiliary function to initialize (or reinitialize the Electronic object)

  This function allocates memory for time-dependent wfc with n_ stationary states
  Then it initializes the overall multiconfigurational wfc
  to be a 1-configurational, with the weight 1 set to basis state with index 0
  and with a random phase

  \param[in] n_ The number of electronic states to include: the dimensionality of the electronic problem

*/

  init(n_,0);
}  


//
// Constructors
//
Electronic::Electronic(int n_,int st){ 
/**
  \brief Constructor

  \param[in] n_ The number of electronic states to include: the dimensionality of the electronic problem
  \param[in] st The index of electronic state to which we initialize the system 
*/

 init(n_,st);
}

Electronic::Electronic(int n_){ 
/**
  \brief Constructor

  The system is initialized to be in the lowest (index 0) electronic state.
  \param[in] n_ The number of electronic states to include: the dimensionality of the electronic problem
*/

 init(n_,0); 
}

Electronic::Electronic(){ 
/**
  \brief Constructor

  The dimensionality of the electronic problem is set to 1 (no excited states)
  The system is initialized to be in the lowest (index 0) electronic state - the only one available
*/

 init(1,0);
}


Electronic::Electronic(const Electronic& ob){ /// cctor
/**
  \brief Copy constructor
*/


  rnd_obj = new Random();
  *rnd_obj = *ob.rnd_obj;

  nstates = ob.nstates;
  istate = ob.istate;
  q = ob.q;
  p = ob.p;

}


Electronic::~Electronic(){  
/**
  \brief Destructor
*/
  if(rnd_obj!=NULL){ delete rnd_obj; rnd_obj = NULL; }
  if(q.size()>0){ q.clear(); }
  if(p.size()>0){ p.clear(); }
}



std::complex<double> Electronic::c(int i){
/**
  \brief Return the amplitude of a quantum state in the complex format: c_i = q_i + i*p_i

  \param[in] i Index of the quantum state
*/

  return complex<double>(q[i],p[i]);

}

std::complex<double> Electronic::rho(int i, int j){
/**
  \brief Returns the density matrix element: rho_ij = c^*_i * c_j

  \param[in] i index of one state
  \param[in] j index of another state
*/

  return complex<double>((q[i]*q[j] + p[i]*p[j]), (q[i]*p[j]-p[i]*q[j]));

}



}//namespace libelectronic
}// namespace libdyn

