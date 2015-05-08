#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include "libcell.h"

using namespace libcell;
using namespace boost::python;


void export_Cell_objects(){


//int (DATA::*ScaleData1)(double)                = &DATA::ScaleData;
//int (DATA::*ScaleData2)(double,double)         = &DATA::ScaleData;


  class_<Cell>("Cell",init<>())
      .def(init<VECTOR&, VECTOR&, VECTOR&, double>())
      .def("init", &Cell::init)
      .def("__copy__", &generic__copy__<Cell>) 
      .def("__deepcopy__", &generic__deepcopy__<Cell>)
//      .def_readwrite("x",&VECTOR::x)
            
  ;

  def("max_vector", max_vector);
  def("apply_pbc", apply_pbc);
  def("serial_to_vector",serial_to_vector);
  def("serial_to_vector_symm",serial_to_vector_symm);
  def("form_neibc",form_neibc);
  def("find_min_shell",find_min_shell);

  def("make_nlist",make_nlist);
  def("make_nlist_auto",make_nlist_auto);

  def("bruteforce",bruteforce);
  def("energy",energy);


} // export_Cell_objects()



#ifdef CYGWIN
BOOST_PYTHON_MODULE(cygcell){
#else
BOOST_PYTHON_MODULE(libcell){
#endif

  // Register converters:
  // See here: https://misspent.wordpress.com/2009/09/27/how-to-write-boost-python-converters/
  //to_python_converter<std::vector<DATA>, VecToList<DATA> >();

  export_Cell_objects();

}

