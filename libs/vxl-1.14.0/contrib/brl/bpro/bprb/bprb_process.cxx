// This is brl/bpro/bprb/bprb_process.cxx
#include "bprb_process.h"
//:
// \file

#include <bprb/bprb_parameters.h>
#include <vcl_iostream.h>


bprb_process::bprb_process()
{
  parameters_ = new bprb_parameters;
}


bprb_process::~bprb_process()
{
}


//: Copy Constructor
bprb_process::bprb_process(const bprb_process& other)
: vbl_ref_count(),
  input_data_(other.n_inputs()), output_data_(other.n_outputs()),
  parameters_(new bprb_parameters(other.parameters_)),
  input_types_(other.input_types()),output_types_(other.output_types())
{
}


bprb_parameters_sptr bprb_process::parameters()
{
  return parameters_;
}


void bprb_process::set_parameters(const bprb_parameters_sptr& params)
{
  parameters_ = params;
}

bool bprb_process::parse_params_XML(const vcl_string& xml_path)
{
  return parameters_->parse_XML(xml_path, name());
}

//: The number of inputs
unsigned bprb_process::n_inputs() const
{
  return input_data_.size();
}

//: The type of each input
vcl_string bprb_process::input_type(unsigned i) const
{
  if (i<n_inputs())
    return input_types_[i];
  return "";
}

//: The number of outputs
unsigned bprb_process::n_outputs() const
{
  return output_data_.size();
}

//: The type of each output
vcl_string bprb_process::output_type(unsigned i) const
{
  if (i<n_outputs())
    return output_types_[i];
  return "";
}

//: Set all the inputs at once
bool bprb_process::set_input_data(vcl_vector<brdb_value_sptr> const& inputs)
{
  if (inputs.size()!= n_inputs())
    return false;
  for (unsigned i = 0; i<n_inputs(); ++i)
    if (!set_input(i, inputs[i]))
      return false;
  return true;
}

//: set a particular input
bool bprb_process::set_input(unsigned i, brdb_value_sptr const& value)
{
  if (i>=n_inputs()){
    vcl_cout << "bprb_process::set_input() - index out of range\n";
    return false;
  }
  if (!value){
    vcl_cout << "bprb_process::set_input() - null value\n";
    return false;
  }
  if (!(value->is_a() == input_type(i))){
    vcl_cout << "bprb_process::set_input() - type mismatch\n";
    return false;
  }
  input_data_[i]=value;
  return true;
}

bool bprb_process::verify_inputs()
{
  for (unsigned i = 0; i<n_inputs(); ++i)
  {
    if (!input_data_[i]) return false;
    if (!(input_data_[i]->is_a()==input_types_[i])) {
      vcl_cout << "Invalid input_data_type[" << i << "] - should be " << input_types_[i]
               << " but is " << input_data_[i]->is_a() << " instead\n";
      return false;
    }
  }
  return true;
}

