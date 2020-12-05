#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

std::ostream &operator<<(std::ostream &o, std::pair<int, int> p) {
  o << "(" << p.first << "," << p.second << ") ";
  return o;
}

std::ostream &operator<<(std::ostream &o, std::vector<std::pair<int, int>> v) {
  for (std::pair<int, int> &p : v)
    o << p;
  return o;
}

std::ostream &operator<<(std::ostream &o, std::vector<int> v) {
  for (int &e : v)
    o << e << " ";
  return o;
}

typedef std::pair<int, int> pair;
typedef std::vector<pair> vecpair;

vecpair operator+(vecpair p1, vecpair p2) {
  vecpair ret;
  for (pair &p : p1)
    ret.push_back(p);
  for (pair &p : p2)
    ret.push_back(p);
  return ret;
}

vecpair &operator+=(vecpair &p1, vecpair p2) {
  for (pair &p : p2)
    p1.push_back(p);
  return p1;
}

vecpair join(vecpair f, vecpair op) {
  vecpair ret;
  ret.push_back({0, 0});
  ret[0].first = (int)ret.size();
  ret += f;
  ret[0].second = (int)ret.size();
  ret += op;
  return ret;
}

typedef unsigned long ul;

bool beta(vecpair &e, int index = 0, std::vector<int> ld = {}) {
#define detect_loop(i, loop_detect)                                            \
  do {                                                                         \
    if (std::find(loop_detect.begin(), loop_detect.end(), i) !=                \
        loop_detect.end())                                                     \
      goto sad;                                                                \
    loop_detect.push_back(i);                                                  \
  } while (0)
  std::vector<int> ild;
  detect_loop(index, ld);
trry:
  while (e[(ul)index].first == 0) {
    index += e[(ul)index].second;
    detect_loop(index, ld);
  }
  ild.clear();
  while (e[(ul)(index + e[(ul)index].first)].first == 0) {
    int pnt = index + e[(ul)index].first;
    detect_loop(pnt, ild);
    e[(ul)index].first =
        e[(ul)(pnt)].second + pnt - index /*re-offset for self*/;
  }
  if (e[(ul)index].second != 0) {
    if (e[(ul)(index + e[(ul)index].first)].second == 0) {
      std::cout << "app->lambda : " << index << std::endl;
      int lambda = index + e[(ul)index].first;
      if (std::find(ld.begin(), ld.end(), lambda) !=
          ld.end()) // is back ref, ignore it
        return beta(e, e[(ul)index].second + index, ld);
      else // do beta reduction
        e[(ul)lambda].second = e[(ul)index].second + index - lambda;
      e[(ul)index].second = e[(ul)lambda].first + lambda - index;
      e[(ul)lambda].first = 0;
      e[(ul)index].first = 0;
      return true;
    } else {
      std::cout << "app->app : " << index << std::endl;
      // try left
      if (beta(e, e[(ul)index].first + index, ld))
        return true;
      std::cout << "app->app(back out) : " << index << std::endl;
      // try right
      return beta(e, e[(ul)index].second + index, ld);
    }
  } else {
    std::cout << "i=lambda : " << index << std::endl;
    // advance to next node
    index += e[(ul)index].first;
    detect_loop(index, ld);
    goto trry;
  }
sad:
  std::cout << "Loop found\n" << std::flush;
  std::cout << "trace :" << ld << std::endl;
  return false;
#undef detect_loop
}

void cleanup(vecpair &vp) {
  std::vector<int> ld;
#define detect_loop(i, loop_detect)                                            \
  do {                                                                         \
    if (std::find(loop_detect.begin(), loop_detect.end(), i) !=                \
        loop_detect.end())                                                     \
      goto sad;                                                                \
    loop_detect.push_back(i);                                                  \
  } while (0)
  for (int index = 0; index < (int)vp.size(); index++) {
    if (vp[(ul)index].first == 0) // we are a redirect
      continue;
    int pnt = index + vp[(ul)index].first; // dereference left arg
    ld.clear();
    detect_loop(index, ld);
    while (vp[(ul)pnt].first == 0) {
      detect_loop(pnt, ld);
      vp[(ul)index].first = vp[(ul)pnt].second + pnt - index;
      pnt = index + vp[(ul)index].first;
    }
    if (vp[(ul)index].second == 0) // we are a lambda
      continue;
    pnt = index + vp[(ul)index].second; // dereference right arg
    ld.clear();
    detect_loop(index, ld);
    while (vp[(ul)pnt].first == 0) {
      detect_loop(pnt, ld);
      vp[(ul)index].second = vp[(ul)pnt].second + pnt - index;
      pnt = index + vp[(ul)index].second;
    }
  }
  std::cout << "Cleanup dereference\n" << std::flush;
  for (int index = 0; index < (int)vp.size();) {
    if (vp[(ul)index].first == 0) {     // remove it
      vp.erase(vp.begin() + index);     // delete it
      for (int i = 0; i < index; i++) { // sub 1 form all left pointing right
        if (vp[(ul)i].first + i > index)
          vp[(ul)i].first--;
        if (vp[(ul)i].second + i > index)
          vp[(ul)i].second--;
      }
      for (int i = index; i < (int)vp.size();
           i++) { // sub 1 from all right pointing left
        if (vp[(ul)i].first + i < index)
          vp[(ul)i].first++;
        if (vp[(ul)i].second + i < index)
          vp[(ul)i].second++;
      }
    } else
      index++;
  }
  std::cout << "Dangling Refrences Removed" << std::endl;
  return;
sad:
  std::cout << "Loop found in cleanup\n"
            << "trace : " << ld << std::endl;
}

void test_1p2e3() {
  vecpair n1({{1, 0}, {1, 0}, {-2, -1}}),
      n2({{1, 0}, {1, 0}, {-2, 1}, {-3, -2}}),
      oplus({{1, 0},
             {1, 0},
             {1, 0},
             {1, 0},
             {1, 2},
             {-5, -3},
             {1, -3},
             {-6, -5}}),
      n3({{1, 0}, {1, 0}, {-2, 1}, {-3, 1}, {-4, -3}});
  std::cout << oplus << std::endl << n2 << std::endl << n1 << std::endl;
  std::cout << std::endl;
  vecpair p21 = join(join(oplus, n2), n1);
  do
    std::cout << p21 << std::endl << std::endl;
  while (beta(p21));
  cleanup(p21);
  std::cout << p21 << std::endl << std::endl;
  std::cout << n3 << std::endl;
}

void test_2t2e4() {
  // This test is borken.  I haven't used these as immutable
  // data-structures, so some of it is broken.
  vecpair n2({{1, 0}, {1, 0}, {-2, 1}, {-3, -2}}),
      otimes({{1, 0}, {1, 0}, {1, 0}, {1, 0}, {1, -1}, {-5, 1}, {-5, -4}}),
      n4({{1, 0}, {1, 0}, {-2, 1}, {-3, 1}, {-4, 1}, {-5, -4}});
  vecpair t22 = join(join(otimes, n2), n2);
  do
    std::cout << t22 << std::endl << std::endl;
  while (beta(t22));
  cleanup(t22);
  std::cout << t22 << std::endl << std::endl;
  std::cout << n4 << std::endl;
}

int main() {
  test_2t2e4();
  return 0;
}
