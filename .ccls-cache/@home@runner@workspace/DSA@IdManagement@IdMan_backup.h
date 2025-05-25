//
// Class : IdMan
// Description: Singleton class to manage the Ids.
//
//#include "IdGenHelper.h"
#include <bits/stdc++.h>
#include <iostream>

constexpr int rows = 65536;
constexpr int cols = 65536;
// 1 sec cooling time
constexpr int coolingTime = 1000;
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
  int createId(std::string data, int len) {
    delPendingList();
    auto it = idMap.find(data);
    if (it != idMap.end()) {
      // update the refcnt
      refCntMap[it->second] += 1;

      std::cout << "refCnt for Id:" << it->second << " "
                << refCntMap[it->second];
      return it->second;
    }

    int id = findFirstAvailableId();
    if (id != -1) {
      reserveId(id);
      idMap.insert({data, id});
      dataMap.insert({id, data});
    }
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
    auto it = dataMap.find(id);
    if (it != dataMap.end()) {
      addPendingList(id);
      // BackgroundTimer::start(coolingTime, &getInstance()->delPendingList);
      auto refCntIt = refCntMap.find(id);
      if (refCntIt != refCntMap.end()) {
        refCntMap.erase(refCntIt);
      }
    
      auto itId = idMap.find(it->second);
      if (itId != idMap.end()) {
        idMap.erase(itId);
      }
      it = dataMap.find(id);
      dataMap.erase(it);
    }

    return;
  }

  //
  // return the id for the give data if exist otherwise
  // return -1;
  //
  int getId(std::string data) {
    auto it = idMap.find(data);
    if (it != idMap.end()) {
      return it->second;
    }
    return -1;
  }

  //
  // return the id for the give data if exist otherwise
  // return -1;
  //
  std::string queryId(int id) {
    auto it = dataMap.find(id);
    if (it != dataMap.end()) {
      return it->second;
    }
    std::cout << "id not found: " << id; 
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
    // initialize the refCnt for Id to 1
    refCntMap[id] = 1;
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
    //pendingIdList.insert({id, std::time(0)});
    return;
  }

  // api to del id from pending list and add it back to available list
  void delPendingList() {
    for (auto it = pendingIdList.begin(); it != pendingIdList.end(); it++) {
      auto id = it->first;
      if (std::time(0) - it->second >= coolingTime) {
        // cooling time is over add Id back in available list
        releaseId(id);
        pendingIdList.erase(it);
      }
    }
    return;
  }

  static IdMan *_instancePtr;
  // Static pointer to the IdMen instance
  static IdMan *instancePtr;
  // Map to hold the <data->id>
  std::map<std::string, int> idMap;
  // Map to hold the <id->data>
  std::map<int, std::string> dataMap;
  // Id refcnt map to hold the ref cnt of id
  std::map<int, int> refCntMap;

  // pending Id list which will be available after cooling time
  std::map<int, time_t> pendingIdList;
  // Id Available list
  std::vector<std::vector<bool>> availableIdList;
};

IdMan *IdMan::_instancePtr = nullptr;
