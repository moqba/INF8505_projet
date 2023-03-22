inline std::stack<vbool_t> init_vbs_vbool() {
  std::stack<vbool_t> vbs_vbool;
  vbool_t vb;
  for (int i=0; i<4; i++) vb.elem(i) = true;
  vbs_vbool.push(vb);
  return vbs_vbool;
}
std::stack<vbool_t> vbs_vbool = init_vbs_vbool();

inline std::stack<vint_t> init_vbs_vint() {
  std::stack<vint_t> vbs_vint;
  vint_t vb;
  for (int i=0; i<4; i++) vb.elem(i) = true;
  vbs_vint.push(vb);
  return vbs_vint;
}
std::stack<vint_t> vbs_vint = init_vbs_vint();

inline std::stack<vuint_t> init_vbs_vuint() {
  std::stack<vuint_t> vbs_vuint;
  vuint_t vb;
  for (int i=0; i<4; i++) vb.elem(i) = true;
  vbs_vuint.push(vb);
  return vbs_vuint;
}
std::stack<vuint_t> vbs_vuint = init_vbs_vuint();
