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
  int createId(const std::string &data) {
    if (data == "") {
      std::cout << "Invalid Input" << std::endl;
      return -1;
    }

    auto opqData = _opaqueDataTrie.insertOpaqData(data);
    // auto opqData = _opaqueDataTrie.getOpaqData(data);
    if (opqData == nullptr) {
      std::cout << "failed to create opaque data node" << std::endl;
    }
    if (opqData->getId() != -1) {
      return opqData->getId();
    }

    //
    // Find first available id. If finds reserve it and add it to multimap as
    // well as in dataMap
    int id = findFirstAvailableId();
    if (id != -1) {
      reserveId(id);
      _dataMap.insert({id, opqData});
      opqData->setId(id);
    }
    // std::cout << "createdId:" << id << endl;
    // cout << "data: " << opqData->getData() << std::endl;
    return id;
  }

  //
  // Delete id.
  // If id is not allocated for given data return
  // If Id is allocated check use_count of shared_ptr and if it is 1 then
  // release the id and add into pendingDelList for cooling time.
  // Once cooling time is over add it back to available list
  //
  // @param id
  //
  void deleteId(int id) {
    auto it = _dataMap.find(id);
    if (it != _dataMap.end()) {
      auto data = it->second->getData();
      // BackgroundTimer::start(coolingTime, &getInstance()->delPendingList);
      // Delete from dataMap and remove opaque data from trie
      _opaqueDataTrie.removeOpaqData(data);
      // Add id in pending list
      addPendingList(id);
      // cout << " deleting id:" << id << endl;
      auto opqData = _opaqueDataTrie.getOpaqData(data);
      if ((opqData == nullptr) ||
          (opqData != nullptr && opqData->getRefCnt() <= 0)) {
        // opaque data is not used by any id so delete it now
        it = _dataMap.erase(it);
        // cout << " deleted id from map:" << id << endl;
      }
    }
    return;
  }

  //
  // queryId API to get the opaque data for the given id if exist otherwise
  // return nullptr
  //
  // @param id
  // @return opaque data;
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
  // findFirstAvailableId API to find fist available id from the available list
  // from lower id to higher id number
  //
  // @return id
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
  // reserveId API to reserve id in the available list by resetting the bit so
  // that it will not be available for next request until it is released and add
  // back after cooling time
  //
  //  @param id
  //
  void reserveId(int id) {
    // std::cout << " reserving id:" << id << endl;
    id = id - 1;
    int bucketIndex = id / bucketSize;
    int bitIndex = id % bucketSize;
    _availableIdList[bucketIndex].reset(bitIndex);
    return;
  }

  //
  // releaseId API to release id in the available list by setting the bit
  //
  // @param id
  //
  void releaseId(int id) {
    id = id - 1;
    int bucketIndex = id / bucketSize;
    int bitIndex = id % bucketSize;
    _availableIdList[bucketIndex].set(bitIndex);
    // cout << "releasing id:" << (id + 1) << endl;
    return;
  }

  //
  // addPendingList API to add id in the pending list after deletion
  // @param id
  //
  void addPendingList(int id) {
    std::lock_guard<std::mutex> lock(pendingListMutex);
    _pendingIdList.insert({id, std::time(0)});
    return;
  }

  //
  // delPendingList API to remove id from pending list once cooling time expires
  // and add it back to available list
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

  //
  // findOpaqueData API to find if opaque data is already present in the data
  // set, if so return TrieOpaqNodePtr
  //
  // @param data
  // @return TrieOpaqNodePtr
  //
  TrieOpaqNodePtr findOpaqueData(const std::string &data) {
    return _opaqueDataTrie.getOpaqData(data);
  }

  // Static pointer to the IdMen instance
  static IdMan *_instancePtr;

  // Map to hold the <id->OpaqueData ptr>
  std::map<int, TrieOpaqNodePtr> _dataMap;

  // pending Id list where id gets added after deletion for cooling time
  std::map<int, time_t> _pendingIdList;
  // Id Available list
  std::vector<bitset<bucketSize>> _availableIdList;

  // Trie object to hold the opaque data
  TrieOpaq _opaqueDataTrie;

  // Timer related parameters
  int _intervalMs = 1000; // 1 second interval
  std::thread _thread;
};

// Initialize the static singleton instance pointer
IdMan *IdMan::_instancePtr = nullptr;

// Timer thread to run in background to check the pending Id list where id gets
// added after deletion for cooling time
//
void timerRun(int interval_ms, IdMan *obj) {
  while (_running) {
    std::this_thread::sleep_for(std::chrono::milliseconds(interval_ms));
    if (_running) {
      obj->timerCallBack();
    }
  }
}
