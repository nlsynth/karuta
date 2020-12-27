// -*- C++ -*-
#ifndef _base_stl_util_h_
#define _base_stl_util_h_

// the names of function come from some opensource projects.

template <class Iterator>
void STLEraseData(Iterator begin, Iterator end) {
  for (Iterator it = begin; it != end; ++it) {
    delete it->second;
  }
}
template <class Iterator>
void STLEraseValues(Iterator begin, Iterator end) {
  for (Iterator it = begin; it != end; ++it) {
    delete *it;
  }
}

template <class T>
void STLDeleteSecondElements(T *t) {
  STLEraseData(t->begin(), t->end());
}

template <class T>
void STLDeleteValues(T *t) {
  STLEraseValues(t->begin(), t->end());
}

#endif  // _base_stl_util_h_
