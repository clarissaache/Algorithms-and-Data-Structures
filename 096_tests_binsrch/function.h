#ifndef __FUNCTION_H__
#define __FUNCTION_H__

template<typename R, typename A>
class Function {
 public:
  virtual R invoke(
      A arg) = 0;  // invoke method implementation needs to be defined in child
  virtual ~Function() {}
};
#endif
