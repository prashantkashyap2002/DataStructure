
#include <bits/stdc++.h>
#include <iostream>

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

class BackgroundTimer {
public:
  static void start(int coolingTime, void (*callback)()) {
    std::thread([coolingTime, callback = std::move(callback)]() {
      std::this_thread::sleep_for(std::chrono::milliseconds(coolingTime));
      callback();
    }).detach(); // detached thread
  }
};