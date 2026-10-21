
extern volatile unsigned int *D_800B0E98;
extern volatile int *D_800B0E9C;
extern volatile int D_800B0EA0;
extern int D_800B0EA4;
extern volatile int D_800B6C74;
extern void func_800889E8(int target, int timeout);
int func_80088870(int mode)
{
  unsigned int status;
  volatile int rcnt;
  int ret;
  int new_var;
  int target;
  status = *D_800B0E98;
  do
  {
    rcnt = *D_800B0E9C;
  }
  while (rcnt != (*D_800B0E9C));
  ret = (rcnt - D_800B0EA0) & 0xFFFF;
  if (mode < 0)
  {
    return D_800B6C74;
  }
  if (mode == 1)
  {
    return ret;
  }
  new_var = mode;
  if (new_var > 0) { int base = D_800B0EA4 - 1; target = base + new_var; } else { target = D_800B0EA4; }
  func_800889E8(target, (new_var > 0) ? (new_var - 1) : (0));
  status = *D_800B0E98;
  func_800889E8(D_800B6C74 + 1, 1);
  if (status & 0x400000)
  {
    if (((int) (status ^ (*D_800B0E98))) >= 0)
    {
      do
      {
      }
      while (((status ^ (*D_800B0E98)) & 0x80000000) == 0);
    }
  }
  D_800B0EA4 = D_800B6C74;
  do
  {
    D_800B0EA0 = *D_800B0E9C;
  }
  while (D_800B0EA0 != (*D_800B0E9C));
  return ret;
}
