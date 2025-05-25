
#include <atomic>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;

// id space :: rows*cols = 65536*65536 = 4294967296 ids 2^32
constexpr int rows = 65536;
constexpr int cols = 65536;
// 2 sec cooling time for id to be available again after deletion
constexpr int coolingTime = 2;
std::atomic<bool> _running;

// forward declaration
class OpaqueData;
typedef std::shared_ptr<OpaqueData> opaqueDataPtr;
class OpaqueData {
public:
  OpaqueData(const char *data, std::size_t size) {
    _data = new char[size];
    _size = size;
    std::memcpy(_data, data, _size);
  }

  const char *getData() { return _data; }
  std::size_t getSize() { return _size; }
  ~OpaqueData() { delete _data; }

private:
  char *_data;
  std::size_t _size;
};