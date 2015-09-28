// -*- C++ -*-
// C++ runtime for NLI generated code.

#ifndef _ccrt_h_
#define _ccrt_h_

#include <deque>
#include <iostream>
#include <map>
#include <string>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

using namespace std;

const int kIdleState = -1;

class NliArrayBase {
public:
  virtual ~NliArrayBase() {
  }
  virtual uint32_t Read(uint32_t addr) = 0;
  virtual void Write(uint32_t addr, uint32_t data) = 0;
};

class NliArray : public NliArrayBase {
public:
  NliArray(int len) : len_(len) {
    image_ = new uint64_t[len];
    for (int i = 0; i < len; ++i) {
      image_[i] = 0;
    }
  }
  virtual ~NliArray() {
    delete [] image_;
  }
  virtual uint32_t Read(uint32_t addr) {
    addr %= len_;
    return image_[addr];
  }
  virtual void Write(uint32_t addr, uint32_t data) {
    addr %= len_;
    image_[addr] = data;
  }

protected:
  int len_;
  uint64_t *image_;
};

class NliChannel {
public:
  NliChannel(const string &name) : name_(name) {
  }
  virtual void Write(uint64_t data) {
    cout << "Channel " << name_ << " " << data << "\n";
  }
  virtual uint64_t Read() {
    uint64_t d = 0;
    if (data_.size() > 0) {
      d = data_.front();
      data_.pop_front();
    }
    cout << "Channel " << name_ << " feed" << d << "\n";
    return d;
  }

  static deque<uint64_t> data_;

private:
  string name_;
};

// For main memory space.
class NliSparseMemory : public NliArrayBase {
public:
  virtual ~NliSparseMemory() {
    for (map<uint32_t, Page *>::iterator it = pages_.begin();
	 it != pages_.end(); ++it) {
      delete it->second;
    }
  }
  virtual uint32_t Read(uint32_t addr) {
    addr /= 4;
    Page *page = GetPage(addr);
    return page->image[addr % kPageSize];
  }
  virtual void Write(uint32_t addr, uint32_t data) {
    addr /= 4;
    Page *page = GetPage(addr);
    page->image[addr % kPageSize] = data;
  }

private:
  static const int kPageSize = 4096;
  struct Page {
    Page() {
      for (int i = 0; i < kPageSize; ++i) {
	image[i] = 0;
      }
    }
    uint32_t image[kPageSize];
  };
  map<uint32_t, Page *> pages_;
  Page *GetPage(uint32_t addr) {
    uint32_t page_index = addr / kPageSize;
    Page *p = pages_[page_index];
    if (!p) {
      p = new Page;
      pages_[page_index] = p;
    }
    return p;
  }
};

// Base class for every module.
class NliCCRTBase {
protected:
  void SRAMWrite(uint32_t addr, int data, NliArrayBase *array) {
    if (!array) {
      array = &main_memory_;
    }
    array->Write(addr, data);
  }

  uint32_t SRAMRead(uint32_t addr, NliArrayBase *array) {
    if (!array) {
      array = &main_memory_;
    }
    return array->Read(addr);
  }

  int BitSelect(uint64_t v, int src_msb, int src_lsb) {
    uint64_t mask = 0xffffffffffffffffLL >> (63 - (src_msb - src_lsb));
    return (v >> src_lsb) & mask;
  }

  void Assert(bool cond) {
    if (!cond) {
      cout << "Assertion failed\n";
      exit(1);
    }
  }

  virtual void DumpState() {}

  bool finish_;

private:
  NliSparseMemory main_memory_;
};

#endif
