//
// Class : IdMan
// Description: Singleton class to manage the Ids.
//
#include "IdGenHelper.h"
#include <bits/stdc++.h>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

// Forward declaration
class IdMan;

// lock for pendingList since it is accessed by timer thread and main thread
// both
std::mutex pendingListMutex;
void timerRun(int interval_ms, IdMan *obj);

class IdMan {
public:
  // getInstance API to get the instance of IdMan
  static IdMan *getInstance() {
    if (_instancePtr == nullptr) {
      _instancePtr = new IdMan();
    }
    return _instancePtr;
  }

  //
  // Create id for the given data. If data is already present retun the same id
  // and update the multimap so the use_count of shared_ptr will be increamented
  //
  // @param data
  // @param len
  // @return id
  //
  int createId(const char *data, std::size_t len) {
    if (len == 0 || data == nullptr) {
      std::cout << "Invalid Input" << std::endl;
      return -1;
    }

    auto opqData = findOpaqueData(data, len);
    if (opqData == nullptr) {
      opqData = std::make_shared<OpaqueData>(data, len);
      _opqDataSet.insert(opqData);
    }

    // Check if id is already allocated for given data, if so return the same id
    // and insert the data in multimap
    auto it = _idMulMap.find(opqData);
    if (it != _idMulMap.end()) {
      _idMulMap.insert({opqData, it->second});
      return it->second;
    }

    //
    // Find first available id. If finds reserve it and add it to multimap as
    // well as in dataMap
    int id = findFirstAvailableId();
    if (id != -1) {
      reserveId(id);
      _idMulMap.insert({opqData, id});
      _dataMap.insert({id, opqData});
    }

    return id;
  }

  //
  // Delete id.
  // If id is not allocated for given data return
  // If Id is allocated check use_count of shared_ptr and if it is 1 then
  // release the id and add into pendingDelList for cooling time.
  // Once cooling time is over add it back to available list
  // @param id
  //
  void deleteId(int id) {
    auto it = _dataMap.find(id);
    if (it != _dataMap.end()) {
      // BackgroundTimer::start(coolingTime, &getInstance()->delPendingList);
      // Delete from multiMap
      auto itId = _idMulMap.find(it->second);
      if (itId != _idMulMap.end()) {
        _idMulMap.erase(itId);
      }

      if (_idMulMap.find(it->second) == _idMulMap.end()) {
        // now safe to delete from set as well as dataMap
        auto itSet = _opqDataSet.find(it->second);
        if (itSet != _opqDataSet.end()) {
          _opqDataSet.erase(itSet);
        }
        _dataMap.erase(it);

        // Add id in pending list
        addPendingList(id);
      }
    }

    return;
  }

  //
  // return the id for the give data if exist otherwise
  // return -1;
  //
  int getId(const char *data, size_t len) {
    auto dataPtr = findOpaqueData(data, len);
    auto it = _idMulMap.find(dataPtr);
    if (it != _idMulMap.end()) {
      return it->second;
    }
    return -1;
  }

  //
  // return the data for the give id if exist otherwise
  // return nullptr;
  //
  const char *queryId(int id) {
    auto it = _dataMap.find(id);
    if (it != _dataMap.end()) {
      return it->second->getData();
    }
    return nullptr;
  }

  void timerCallBack() { delPendingList(); }

private:
  // Private Constructor
  IdMan() {
    // initilize id available list
    _availableIdList.resize(numBucket);
    for (int i = 0; i < numBucket; i++) {
      _availableIdList[i].set();
    }
    // starting timer thread for id cooling time
    _running = true;
    _thread = std::thread(timerRun, _intervalMs, this);
  }

  // Private Destructor
  ~IdMan() {
    if (_running) {
      _running = false;
      if (_thread.joinable()) {
        _thread.join();
      }
    }
  }

  //
  // API to find fist available id from the available list from lower id to
  // higher id number
  //
  int findFirstAvailableId() {
    for (int i = 0; i < _availableIdList.size(); i++) {
      if (_availableIdList[i].any()) {
        return (i * bucketSize + _availableIdList[i]._Find_first() + 1);
      }
    }
    return -1;
  }

  //
  // API to reserve id in the available list by marking it false so that it will
  // not be available for next request until it is released and add back after
  // cooling time
  //
  void reserveId(int id) {
    id = id - 1;
    int bucketIndex = id / bucketSize;
    int bitIndex = id % bucketSize;
    _availableIdList[bucketIndex].reset(bitIndex);
    return;
  }

  //
  // API to add id back in the available list by marking it true
  //
  void releaseId(int id) {
    id = id - 1;
    int bucketIndex = id / bucketSize;
    int bitIndex = id % bucketSize;
    _availableIdList[bucketIndex].set(bitIndex);
    return;
  }

  // api to add id in pending list
  void addPendingList(int id) {
    std::lock_guard<std::mutex> lock(pendingListMutex);
    _pendingIdList.insert({id, std::time(0)});
    return;
  }

  //
  //  API to remove id from pending list once cooling time expires and add it
  //  back to available list
  //
  void delPendingList() {
    std::lock_guard<std::mutex> lock(pendingListMutex);
    for (auto it = _pendingIdList.begin(); it != _pendingIdList.end();) {
      auto id = it->first;
      auto elapsedTime = std::time(0) - it->second;
      // std::cout << "delPendingList elapsedTime for id:" << id << " is "
      //<< elapsedTime << std::endl;
      if (elapsedTime >= coolingTime) {
        // cooling time is over add Id back in available list
        releaseId(id);
        it = _pendingIdList.erase(it);
      } else {
        it++;
      }
    }
    return;
  }

  // API to find if opaque data is already present in the data set, if so return
  // opaqueDataPtr
  opaqueDataPtr findOpaqueData(const char *data, std::size_t size) {
    for (auto it = _opqDataSet.begin(); it != _opqDataSet.end(); ++it) {
      opaqueDataPtr dataPtr = *it;
      if ((std::memcmp(data, dataPtr->getData(), size) == 0) &&
          (size == dataPtr->getSize())) {
        return dataPtr;
      }
    }
    return nullptr;
  }

  // Static pointer to the IdMen instance
  static IdMan *_instancePtr;

  // Set to hold the OpaqueData ptr
  std::set<opaqueDataPtr> _opqDataSet;
  // Map to hold the <OpaqueData ptr->id>
  std::multimap<opaqueDataPtr, int> _idMulMap;
  // Map to hold the <id->OpaqueData ptr>
  std::map<int, opaqueDataPtr> _dataMap;

  // pending Id list where id gets added after deletion for cooling time
  std::map<int, time_t> _pendingIdList;
  // Id Available list
  std::vector<bitset<bucketSize>> _availableIdList;

  // Timer related parameters
  int _intervalMs = 1000; // 1 second interval
  std::thread _thread;
};

// Initialize the static singleton instance pointer
IdMan *IdMan::_instancePtr = nullptr;

// Timer thread to run in background to check the pending Id list where id gets
// added after deletion for cooling time
//
// TBD : This can be optimized by scheduling the timer only when there is id in
// pendingList
void timerRun(int interval_ms, IdMan *obj) {
  while (_running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    if (_running) {
      obj->timerCallBack();
    }
  }
}
