//
// Class : IdMan
// Description: Singleton class to manage the Ids.
//
#include "IdGenHelper.h"
#include <bits/stdc++.h>
#include <iostream>

constexpr int rows = 65536;
constexpr int cols = 65536;
// 2 sec cooling time
constexpr int coolingTime = 2;

// Forward declaration
class IdMan;

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
  // and bump the ref cnt to the id;
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
    // std::cout << "createId: ";
    auto opqData = findOpaqueData(data, len);
    if (opqData == nullptr) {
      opqData = std::make_shared<OpaqueData>(data, len);
      opqDataSet.insert(opqData);
      // std::cout << "createId::refCnt for new Data:" << opqData->getData() <<
      // " "
      //           << opqData.use_count() << std::endl;
    }

    delPendingList();

    auto it = _idMulMap.find(opqData);
    if (it != _idMulMap.end()) {
      _idMulMap.insert({opqData, it->second});
      return it->second;
    }

    int id = findFirstAvailableId();
    if (id != -1) {
      reserveId(id);
      _idMulMap.insert({opqData, id});
      _dataMap.insert({id, opqData});
    }
    // std::cout << "createId::refCnt for Data:" << opqData->getData() << " "
    //           << opqData.use_count() << " id:" << id << std::endl;

    return id;
  }

  //
  // Delete id.
  // If id is allocated for given data return
  // If Id is allocated decrement the ref cnt,
  //   if refCnt become 0 release the id and
  //   and add into free list
  //
  // @param data
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
        auto itSet = opqDataSet.find(it->second);
        if (itSet != opqDataSet.end()) {
          opqDataSet.erase(itSet);
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
  // return the id for the give data if exist otherwise
  // return -1;
  //
  const char *queryId(int id) {
    auto it = _dataMap.find(id);
    if (it != _dataMap.end()) {
      return it->second->getData();
    }
    // std::cout << "queryId:id not found" << std::endl;
    return nullptr;
  }

private:
  // Private Constructor
  IdMan() {
    // initilize id available list
    availableIdList.resize(cols);
    for (auto &i : availableIdList)
      i.resize(rows);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        availableIdList[i][j] = true;
      }
    }
  }

  // api to find fist available id from the available list
  int findFirstAvailableId() {
    for (int i = 0; i < availableIdList.size(); i++) {
      for (int j = 0; j < availableIdList[i].size(); j++) {
        if (availableIdList[i][j] == true) {
          return (i * 65536 + j + 1);
        }
      }
    }
    return -1;
  }

  // api to reserve id in the available list
  void reserveId(int id) {
    id = id - 1;
    availableIdList[id / 65536][id % 65536] = false;
    return;
  }

  // api to release id in the available list
  void releaseId(int id) {
    id = id - 1;
    availableIdList[id / 65536][id % 65536] = true;
    return;
  }

  // api to add id in pending list
  void addPendingList(int id) {
    pendingIdList.insert({id, std::time(0)});
    return;
  }

  // API to del id from pending list and add it back to available list
  void delPendingList() {
    for (auto it = pendingIdList.begin(); it != pendingIdList.end();) {
      auto id = it->first;
      auto elapsedTime = std::time(0) - it->second;
      if (elapsedTime >= coolingTime) {
        // cooling time is over add Id back in available list
        releaseId(id);
        it = pendingIdList.erase(it);
      } else {
        it++;
      }
    }
    return;
  }

  // API to find if data is already present in the set
  opaqueDataPtr findOpaqueData(const char *data, std::size_t size) {
    for (auto it = opqDataSet.begin(); it != opqDataSet.end(); ++it) {
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
  std::set<opaqueDataPtr> opqDataSet;
  // Map to hold the <OpaqueData ptr->id>
  std::multimap<opaqueDataPtr, int> _idMulMap;
  // Map to hold the <id->OpaqueData ptr>
  std::map<int, opaqueDataPtr> _dataMap;

  // pending Id list which will be available after cooling time
  std::map<int, time_t> pendingIdList;
  // Id Available list
  std::vector<std::vector<bool>> availableIdList;
};

IdMan *IdMan::_instancePtr = nullptr;
