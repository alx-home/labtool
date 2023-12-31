// This is mul/mbl/tests/test_mask.cxx
#include <testlib/testlib_test.h>
#include <vcl_vector.h>
#include <mbl/mbl_mask.h>
#include <vcl_fstream.h>

unsigned mask4_to_number(const mbl_mask & r)
{
  return (r[0] ? 8 : 0) +
         (r[1] ? 4 : 0) +
         (r[2] ? 2 : 0) +
         (r[3] ? 1 : 0);
}

vcl_string number_to_fourbit(unsigned n)
{
  vcl_stringstream ss;
  for (int i = 3; i >= 0; --i)
  {
    ss << ((n >> i) & 1);
  }
  return ss.str();
}

void setup_default_masks(mbl_mask & m1, mbl_mask & m2)
{
  m1.resize(5);
  m1[0] = true;
  m1[1] = false;
  m1[2] = false;
  m1[3] = true;
  m1[4] = true;
  m2 = m1;
}

void setup_default_values(vcl_vector<unsigned> & v1, vcl_vector<unsigned> & v2)
{
  v1.resize(5); v2.resize(5);
  for (unsigned i = 0 ; i < 5 ; ++i)
  {
    v1[i] = i;
    v2[i] = 10+i;
  }
}

void test_mask()
{
  // workspace
  vcl_vector<unsigned> v1, v2, v_tgt;
  mbl_mask m1, m2, m_op;


  // Test mask IO
  vcl_cout << "\nTesting mbl_mask IO" << vcl_endl;
  setup_default_masks(m1, m2);
  m2.clear();
  mbl_save_mask(m1, "mbl_mask_test_maskfile.txt");
  mbl_load_mask(m2, "mbl_mask_test_maskfile.txt");
  TEST("Mask saved and loaded", (m1 == m2), true);

  // Test proper failure of badly formatted file
  vcl_ofstream fout("mbl_mask_test_badmask.txt");
  fout << "1\n0\nbad\n1\n";
  fout.close();
  bool failed_load = false;
  m2.clear();
  try         { mbl_load_mask(m2, "mbl_mask_test_badmask.txt"); }
  catch (...) { failed_load = true; }
  TEST("Expected fail to load badly formatted file", failed_load, true);
  TEST("Mask empty after file load fail", m2.empty(), true);


  // Test mbl_apply_mask(mask,vector)
  vcl_cout << "\nTesting mbl_apply_mask(mask,vector) version" << vcl_endl;
  setup_default_masks(m1, m2);
  setup_default_values(v1, v2);
  v_tgt.clear();
  v_tgt.push_back(0); // see definition of m1 above for relationship values->target
  v_tgt.push_back(3);
  v_tgt.push_back(4);

  // Test application of mask to a values vector using direct version
  mbl_apply_mask(m1, v1);
  TEST("Application of mask to vector of values", (v1 == v_tgt), true);

  // Test proper failure of mismatched lengths
  setup_default_masks(m1, m2);
  setup_default_values(v1, v2);
  m1.resize(3);
  v_tgt = v1;
  bool failed_application = false;
  try         { mbl_apply_mask(m1, v1); }
  catch (...) { failed_application = true; }
  TEST("Expected fail of apply mask where lengths differ", failed_application, true);
  TEST("Values invariant on failure of mask application", (v1 == v_tgt), true);


  // Test mbl_apply_mask(mask,vector,vector)
  vcl_cout << "\nTesting mbl_apply_mask(mask,vector,vector) version" << vcl_endl;
  setup_default_masks(m1, m2);
  setup_default_values(v1, v2);
  v_tgt.clear();
  v_tgt.push_back(0); // see definition of m1 above for relationship values->target
  v_tgt.push_back(3);
  v_tgt.push_back(4);

  // Test application of mask to a values vector using src,dst version  
  mbl_apply_mask(m1, v1, v2);
  TEST("Application of mask to vector of values", (v2 == v_tgt), true);

  // Test proper failure of mismatched lengths
  setup_default_masks(m1, m2);
  setup_default_values(v1, v2);
  m1.resize(3);
  v_tgt = v1;
  failed_application = false;
  try         { mbl_apply_mask(m1, v1); }
  catch (...) { failed_application = true; }
  TEST("Expected fail of apply mask where lengths differ", failed_application, true);
  TEST("Values invariant on failure of mask application", (v1 == v_tgt), true);


  // Test iterator version
  vcl_cout << "\nTesting mbl_apply_mask iterator version" << vcl_endl;
  setup_default_masks(m1, m2);
  setup_default_values(v1, v2);
  vcl_vector<unsigned> result;
  v_tgt.clear();
  v_tgt.push_back(0); // see definition of m1 above for relationship values->target
  v_tgt.push_back(3);
  v_tgt.push_back(4);
  mbl_apply_mask(m1, v1.begin(), v1.end(), vcl_inserter(result, result.begin()));
  TEST("Application of mask using insert iterator method", (result == v_tgt), true);
  failed_application = false;
  result.clear();
  m1.resize(4);
  try         { mbl_apply_mask(m1, v1.begin(), v1.end(), vcl_inserter(result, result.begin())); }
  catch (...) { failed_application = true; }
  TEST("Expected fail of apply mask where lengths differ", failed_application, true);
  TEST("Values invariant on failure of mask application", result.empty(), true);


  // Test mbl_mask_logic
  vcl_cout << "\nTesting mbl_mask_logic" << vcl_endl;
  m1.clear(); m2.clear();
  m1.push_back(false); m2.push_back(false);
  m1.push_back(false); m2.push_back(true);
  m1.push_back(true); m2.push_back(false);
  m1.push_back(true); m2.push_back(true);
  bool logic_success = true;
  for (unsigned rule = 0 ; rule < 16 ; ++rule)
  {
    m_op = m2;
    mbl_mask_logic(m1, m_op, number_to_fourbit(rule));
    logic_success &= (rule == mask4_to_number(m_op));
  }
  TEST("Correctness of general logical operations", logic_success, true);
  logic_success = true;
  m_op = m2; mbl_mask_logic_and(m1,m_op); logic_success &= (mask4_to_number(m_op) == 1);
  m_op = m2; mbl_mask_logic_nand(m1,m_op); logic_success &= (mask4_to_number(m_op) == 14);
  m_op = m2; mbl_mask_logic_nor(m1,m_op); logic_success &= (mask4_to_number(m_op) == 8);
  m_op = m2; mbl_mask_logic_or(m1,m_op); logic_success &= (mask4_to_number(m_op) == 7);
  m_op = m2; mbl_mask_logic_xnor(m1,m_op); logic_success &= (mask4_to_number(m_op) == 9);
  m_op = m2; mbl_mask_logic_xor(m1,m_op); logic_success &= (mask4_to_number(m_op) == 6);
  TEST("Correctness of specific logical operations", logic_success, true);

  // Test failures of mbl_mask_logic
  unsigned failed_logic = 0;
  m_op = m2;
  try         { mbl_mask_logic(m1, m_op, "010"); } // wrong length op string
  catch (...) { failed_logic++; }
  try         { mbl_mask_logic(m1, m_op, "01B0"); } // bad op string format
  catch (...) { failed_logic++; }
  m1.push_back(false); // mismatched mask lengths
  try         { mbl_mask_logic(m1, m_op, "0110"); }
  catch (...) { failed_logic++; }
  TEST("Expected fails for invalid logic ops", (failed_logic == 3), true);
  TEST("Result invariant on failure of mask logic", (m2 == m_op), true);


  // Test merging of value vectors
  vcl_cout << "\nTesting mbl_mask_merge_values" << vcl_endl;
  setup_default_masks(m1, m2);
  setup_default_values(v1, v2);
  v_tgt.resize(5);
  v_tgt[0] = v2[0];
  v_tgt[1] = v1[1];
  v_tgt[2] = v1[2];
  v_tgt[3] = v2[3];
  v_tgt[4] = v2[4];
  mbl_mask_merge_values(m1, v1.begin(), v1.end(), v2.begin(), v2.end(), v2.begin());
  TEST("Correctness of values according to mask", (v2==v_tgt), true);

  // Test failure of merge operation
  setup_default_values(v1, v2);
  v_tgt = v2;
  m1.resize(4);
  bool merge_failed = false;
  try         { mbl_mask_merge_values(m1, v1.begin(), v1.end(), v2.begin(), v2.end(), v2.begin()); }
  catch (...) { merge_failed = true; }
  TEST("Expected fail of merge values where lengths differ", merge_failed, true);
  TEST("Values invariant on failure of merge operation", v2 == v_tgt, true);


  // Test mbl_mask_on_mask
  vcl_cout << "\nTesting mbl_mask_on_mask" << vcl_endl;
  m1.resize(4); m2.resize(6); m_op.resize(6);
  m1[0] = true;  m2[0] = true;  m_op[0] = true;
  m1[1] = false; m2[1] = true;  m_op[1] = false;
  m1[2] = true;  m2[2] = false; m_op[2] = false;
  m1[3] = false; m2[3] = true;  m_op[3] = true;
                 m2[4] = false; m_op[4] = false;
                 m2[5] = true;  m_op[5] = false;

  mbl_mask_on_mask(m1, m2);
  TEST("Correctness of mask-on-mask operation", (m2 == m_op), true);

  // Test failure of mask-on-mask
  m2[0] = true;
  m2[1] = true;
  m2[2] = false;
  m2[3] = false; // i.e. m1 has too many elements c.f. setup of m2 above
  m2[4] = false;
  m2[5] = true;
  m_op = m2;
  bool mask_mask_failure = false;
  try         { mbl_mask_on_mask(m1, m2); }
  catch (...) { mask_mask_failure = true; }
  TEST("Expected fail of mask-on-mask due to count mismatch", mask_mask_failure, true);
  TEST("Result invariant on failure of mask-on-mask operation", (m2 == m_op), true);


  // Test mbl_masks_from_index_set
  vcl_cout << "\nTesting mbl_masks_from_index_set" << vcl_endl;
  vcl_vector<unsigned> index_set(5);
  index_set[0] = 1;
  index_set[1] = 4;
  index_set[2] = 2;
  index_set[3] = 1;
  index_set[4] = 2;
  vcl_vector<mbl_mask> masks;
  mbl_masks_from_index_set(index_set, masks);
  mbl_mask mask1(5), mask2(5), mask4(5);
  mask1[0] = true;
  mask4[1] = true;
  mask2[2] = true;
  mask1[3] = true;
  mask2[4] = true;
  bool index_masks_match = true;
  index_masks_match &= (masks[0] == mask1);
  index_masks_match &= (masks[1] == mask2);
  index_masks_match &= (masks[2] == mask4);
  TEST("Correctness of masks from index set", index_masks_match, true);
}

TESTMAIN(test_mask);
