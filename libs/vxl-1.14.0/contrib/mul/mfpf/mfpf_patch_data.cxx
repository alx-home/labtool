#include "mfpf_patch_data.h"
//:
// \file
// \author Tim Cootes
// \brief Defines region size, shape, and form of model to use

#include <vsl/vsl_indent.h>
#include <vsl/vsl_binary_loader.h>

#include <mbl/mbl_parse_block.h>
#include <mbl/mbl_read_props.h>
#include <mbl/mbl_exception.h>
#include <vul/vul_string.h>

//=======================================================================
// Dflt ctor
//=======================================================================

mfpf_patch_data::mfpf_patch_data()
{
}

//=======================================================================
// Destructor
//=======================================================================

mfpf_patch_data::~mfpf_patch_data()
{
}

//: Initialise from a string stream
bool mfpf_patch_data::set_from_stream(vcl_istream &is)
{
  // Cycle through string and produce a map of properties
  vcl_string s = mbl_parse_block(is);
  vcl_istringstream ss(s);
  mbl_read_props_type props = mbl_read_props_ws(ss);

  name_=props.get_required_property("name");
  min_width_=vul_string_atoi(props.get_optional_property("min_width","7"));
  max_width_=vul_string_atoi(props.get_optional_property("max_width","25"));

  vcl_string region_str = props.get_required_property("region");
  {
    vcl_istringstream iss(region_str);
    definer_ = *mfpf_region_definer::create_from_stream(iss);
  }

  vcl_string builder_str = props.get_required_property("builder");
  {
    vcl_istringstream iss(builder_str);
    builder_ = *mfpf_point_finder_builder::create_from_stream(iss);
  }

  // Check for unused props
  mbl_read_props_look_for_unused_props(
      "mfpf_patch_data::set_from_stream", props, mbl_read_props_type());
  return true;
}


//=======================================================================
// Method: version_no
//=======================================================================

short mfpf_patch_data::version_no() const
{
  return 1;
}


//=======================================================================
// Method: is_a
//=======================================================================

vcl_string mfpf_patch_data::is_a() const
{
  return vcl_string("mfpf_patch_data");
}

//: Print class to os
void mfpf_patch_data::print_summary(vcl_ostream& os) const
{
  os<<" {\n";
  vsl_indent_inc(os);
  os<<vsl_indent()<<"name: "<<name_<<'\n'
    <<vsl_indent()<<"min_width: "<<min_width_<<'\n'
    <<vsl_indent()<<"max_width: "<<max_width_<<'\n'
    <<vsl_indent()<<"region: "<<definer_<<'\n'
    <<vsl_indent()<<"builder: "<<builder_<<'\n';
  vsl_indent_dec(os);
  os<<"} ";
}

//=======================================================================
// Method: save
//=======================================================================

void mfpf_patch_data::b_write(vsl_b_ostream& bfs) const
{
  vsl_b_write(bfs,version_no());
  vsl_b_write(bfs,name_);
  vsl_b_write(bfs,min_width_);
  vsl_b_write(bfs,max_width_);
  vsl_b_write(bfs,definer_);
  vsl_b_write(bfs,builder_);
}

//=======================================================================
// Method: load
//=======================================================================

void mfpf_patch_data::b_read(vsl_b_istream& bfs)
{
  if (!bfs) return;
  short version;
  vsl_b_read(bfs,version);
  switch (version)
  {
    case (1):
      vsl_b_read(bfs,name_);
      vsl_b_read(bfs,min_width_);
      vsl_b_read(bfs,max_width_);
      vsl_b_read(bfs,definer_);
      vsl_b_read(bfs,builder_);
      break;
    default:
      vcl_cerr << "I/O ERROR: vsl_b_read(vsl_b_istream&)\n";
      vcl_cerr << "           Unknown version number "<< version << vcl_endl;
      bfs.is().clear(vcl_ios::badbit); // Set an unrecoverable IO error on stream
      return;
  }
}

//=======================================================================
// Associated function: operator<<
//=======================================================================

vcl_ostream& operator<<(vcl_ostream& os,const mfpf_patch_data& b)
{
  os << b.is_a() << ": ";
  vsl_indent_inc(os);
  b.print_summary(os);
  vsl_indent_dec(os);
  return os;
}

  //: Binary file stream output operator for class reference
void vsl_b_write(vsl_b_ostream& bfs, const mfpf_patch_data& b)
{
  b.b_write(bfs);
}

  //: Binary file stream input operator for class reference
void vsl_b_read(vsl_b_istream& bfs, mfpf_patch_data& b)
{
  b.b_read(bfs);
}

// =====================================================
// ======= Functions for sets of mfpf_patch_data =======
// =====================================================

//: Reads in a list of mfpf_patch_data objects from a text stream
//  Format: "{ region: { ... } region: { ... } .... }"
void mfpf_read_from_stream(vcl_istream &is,
                           vcl_vector<mfpf_patch_data>& data)
{
  vcl_string s = mbl_parse_block(is);
  vcl_istringstream ss(s);
  char c;
  ss>>c;  // Remove opening brace
  if (c!='{')
  {
    throw mbl_exception_parse_error("Expected '{' in ggr_parse_list");
  }
  data.resize(0);

  vcl_string label;
  while (!ss.eof())
  {
    ss >> label;         // Next follows the parameters
    if (label == "}") continue;
    if (label!="region:")
    {
      vcl_string error_msg = "Expected keyword: region:";
      error_msg+=" Got '"+label+"'";
      throw mbl_exception_parse_error(error_msg);
    }

    mfpf_patch_data patch;
    vcl_istringstream ss2(mbl_parse_block(ss));
    patch.set_from_stream(ss2);
    data.push_back(patch);
  }
}

