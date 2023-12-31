//:
// \file
// \author Ozge C. Ozcanli (Brown)
// \date   April 21, 2009

#include "bsvg_document.h"
#include <vcl_iostream.h>

bsvg_document::bsvg_document(float w, float h) : w_(w), h_(h)
{
  bxml_element* root = new bxml_element("svg");
  this->set_root_element(root);

  root->set_attribute("xmlns", "http://www.w3.org/2000/svg");
    
  vcl_stringstream ss_w; ss_w << w;
  root->set_attribute("width", ss_w.str()); 
    
  vcl_stringstream ss_h; ss_h << h;
  root->set_attribute("height", ss_h.str());
    
  //: viewBox is by default, the same size as width and height
  vcl_string v_box = "0,0,"+ss_w.str()+","+ss_h.str();
  root->set_attribute("viewBox", v_box);
  root->append_text("\n");
  
}

bsvg_document::bsvg_document(float w, float h, float viewBox_x, float viewBox_y, float viewBox_w, float viewBox_h) : w_(w), h_(h)
{
  bxml_element* root = new bxml_element("svg");
  this->set_root_element(root);

  root->set_attribute("xmlns", "http://www.w3.org/2000/svg");
    
  vcl_stringstream ss_w; ss_w << w;
  root->set_attribute("width", ss_w.str()); 
    
  vcl_stringstream ss_h; ss_h << h;
  root->set_attribute("height", ss_h.str());
    
  vcl_stringstream ss_x; ss_x << viewBox_x;
  vcl_stringstream ss_y; ss_y << viewBox_y;
  vcl_stringstream ss_Bw; ss_Bw << viewBox_w;
  vcl_stringstream ss_Bh; ss_Bh << viewBox_h;

  vcl_string v_box = ss_x.str()+","+ss_y.str()+","+ss_Bw.str()+","+ss_Bh.str();
  root->set_attribute("viewBox", v_box);
  root->append_text("\n");
}

bool bsvg_document::add_description(const vcl_string& d)
{
  if (!this->root_element()) {
    vcl_cout << "Error: Root element of SVG document has not been created!\n";
    return false;
  } 

  bxml_element* root = dynamic_cast<bxml_element*>(this->root_element().ptr());
  
  bxml_element* desc = new bxml_element("desc");
  desc->append_text(d);
  root->append_data(desc);
  root->append_text("\n");
 
  return true;
}

bool bsvg_document::add_element(const bxml_data_sptr& element)
{
  if (!this->root_element()) {
    vcl_cout << "Error: Root element of SVG document has not been created!\n";
    return false;
  } 

  bxml_element* root = dynamic_cast<bxml_element*>(this->root_element().ptr());
  root->append_data(element);
  root->append_text("\n");

  return true;
}

