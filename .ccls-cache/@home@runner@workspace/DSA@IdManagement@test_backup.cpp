#include "IdMan.h"

int main() {
  auto idGen = IdMan::getInstance();
  std::string data;
  auto id = idGen->createId(data.data(), data.length());
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (id == -1) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  data = "abcd";
  id = idGen->createId(data.data(), data.length());
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  id = idGen->createId(data.data(), data.length());
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;

  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  data = "abc";
  id = idGen->createId(data.data(), data.length());
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;

  if (id == 2 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  id = 1;
  idGen->deleteId(id);
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;

  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  idGen->deleteId(id);
  if (idGen->queryId(id) != nullptr) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (idGen->queryId(id) == nullptr) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  data = "abcde";
  id = idGen->createId(data.data(), data.length());
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  if (id == 3 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  idGen->deleteId(id);
  if (idGen->queryId(id) != nullptr) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (idGen->queryId(id) == nullptr) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  sleep(1);
  id = idGen->createId(data.data(), data.length());
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  if (id == 4 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  sleep(1);
  data = "abcd";
  id = idGen->createId(data.data(), data.length());
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }

  data = "pqrstuvwxyz";
  id = idGen->createId(data.data(), data.length());
  std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  if (id == 3 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
  }
  return 0;
}
#endif