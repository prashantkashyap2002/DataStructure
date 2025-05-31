#include "IdMan.h"

int main() {
  auto idGen = IdMan::getInstance();
  std::string data = "";
  auto id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  std::cout << "TC1:: Create Id with empty data";
  if (id == -1) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  data = "abcd";
  std::cout << "TC2:: create id with data " << data;
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  std::cout << "TC3:: create id with same data";
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  data = "abc";
  std::cout << "TC4:: create id with new data " << data;
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  if (id == 2 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  std::cout << "TC5:: delete id 1 and query id 1";
  id = 1;
  idGen->deleteId(id);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }
  std::cout << "TC6:: delete id 1 again and query id 1";
  idGen->deleteId(id);
  if (idGen->queryId(id) != nullptr) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (idGen->queryId(id) == nullptr) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  data = "abcde";
  std::cout << "TC7:: create id with new data " << data;

  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (id == 3 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  std::cout << "TC8:: delete id 3 and query id 3";
  idGen->deleteId(id);
  if (idGen->queryId(id) != nullptr) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (idGen->queryId(id) == nullptr) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  sleep(1);
  std::cout
      << "TC9:: create id with same deleted data for id 3 before cooling time";
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (id == 4 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  sleep(2);
  data = "abcd";
  std::cout << "TC10:: create id with new data after cooling time " << data;
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }
  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  data = "pqrstuvwxyz";
  std::cout << "TC11:: create id with new data " << data;
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  if (id == 3 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  std::cout << "TC12:: delete all ids ";
  idGen->deleteId(1);
  idGen->deleteId(2);
  idGen->deleteId(3);
  idGen->deleteId(4);

  data = "pqrstuAUwxyz!";
  std::cout << "TC13:: create id with data " << data;
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  if (id == 5 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }
  sleep(3);
  data = "abcdE";
  std::cout << "TC14:: create id with data after cooling time " << data;
  id = idGen->createId(data);
  if (idGen->queryId(id)) {
    std::cout << "id: " << id << " data:" << idGen->queryId(id) << std::endl;
  }

  if (id == 1 &&
      std::memcmp(idGen->queryId(id), data.data(), data.length()) == 0) {
    std::cout << "Passed" << std::endl;
  } else {
    std::cout << "Failed" << std::endl;
    return 0;
  }

  return 0;
}