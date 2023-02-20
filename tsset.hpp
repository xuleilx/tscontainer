#ifndef __TSSET_H__
#define __TSSET_H__
#include <algorithm>
#include <functional>
#include <memory>
#include <mutex>
#include <set>
#include <utility>
#include "atomic_rw_lock.hpp"
#include "rw_lock_guard.hpp"
namespace tscontainer {
/**
 * @brief tsset
 *
 * @tparam Key Key
 * @tparam Compare Compare
 * @tparam Alloc Alloc
 */
template <typename Key, typename Compare = std::less<Key>,
          typename Alloc = std::allocator<Key>>
class tsset : public std::set<Key> {
 private:
  // iterator
  using iterator = typename std::set<Key, Compare, Alloc>::iterator;
  // const_iterator
  using const_iterator = typename std::set<Key, Compare, Alloc>::const_iterator;
  // key_type
  using key_type = typename std::set<Key, Compare, Alloc>::key_type;
  // value_type
  using value_type = typename std::set<Key, Compare, Alloc>::value_type;
  // size_type
  using size_type = typename std::set<Key, Compare, Alloc>::size_type;
  // key_compare
  using key_compare = typename std::set<Key, Compare, Alloc>::key_compare;
  // allocator_type
  using allocator_type = typename std::set<Key, Compare, Alloc>::allocator_type;
  // set
  using set = typename std::set<Key, Compare, Alloc>;
  // mtx
  mutable base::AtomicRWLock mtx;

 public:
  /**
   * @brief Construct a new tsset object
   *
   * @param comp compare
   * @param alloc alloc
   */
  explicit tsset(const key_compare& comp = key_compare(),
                 const allocator_type& alloc = allocator_type()) noexcept
      : std::set<Key, Compare, Alloc>(comp, alloc) {}
  /**
   * @brief Copy construct a new tsset object
   *
   * @param x x
   */
  explicit tsset(const set& x) : std::set<Key, Compare, Alloc>(x) {}
  /**
   * @brief Construct a new tsset object
   *
   * @param x x
   */
  tsset(const tsset& x) : std::set<Key, Compare, Alloc>(x) {}
  /**
   * @brief Construct a new tsset object
   *
   * @param x x
   */
  explicit tsset(set&& x) : std::set<Key, Compare, Alloc>(x) {}
  /**
   * @brief Construct a new tsset object
   *
   * @param x x
   */
  tsset(tsset&& x) : std::set<Key, Compare, Alloc>(x) {}
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsset<Key, Compare, Alloc>& tsset
   */
  tsset<Key, Compare, Alloc>& operator=(const set& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::set<Key, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsset<Key, Compare, Alloc>& tsset
   */
  tsset<Key, Compare, Alloc>& operator=(
      const tsset<Key, Compare, Alloc>& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::set<Key, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsset<Key, Compare, Alloc>& tsset
   */
  tsset<Key, Compare, Alloc>& operator=(set&& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::set<Key, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsset<Key, Compare, Alloc>& tsset
   */
  tsset<Key, Compare, Alloc>& operator=(
      tsset<Key, Compare, Alloc>&& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::set<Key, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param il il
   * @return tsset<Key, Compare, Alloc>& tsset
   */
  tsset<Key, Compare, Alloc>& operator=(
      std::initializer_list<value_type> il) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::set<Key, Compare, Alloc>::operator=(il);
    return *this;
  }
  /**
   * @brief empty
   *
   * @return true true
   * @return false false
   */
  bool empty() const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::set<Key, Compare, Alloc>::empty();
  }
  /**
   * @brief size
   *
   * @return size_type size_type
   */
  size_type size() const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::set<Key, Compare, Alloc>::size();
  }
  /**
   * @brief insert
   *
   * @param val val
   * @return std::pair<iterator, bool> std::pair
   */
  std::pair<iterator, bool> insert(const value_type& val) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::insert(val);
  }
  /**
   * @brief insert
   *
   * @param val val
   * @return std::pair<iterator, bool> std::pair
   */
  std::pair<iterator, bool> insert(value_type&& val) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::insert(std::move(val));
  }
  /**
   * @brief insert
   *
   * @param position position
   * @param val val
   * @return iterator iterator
   */
  iterator insert(iterator position, const value_type& val) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::insert(position, val);
  }
  /**
   * @brief insert
   *
   * @param position position
   * @param val val
   * @return iterator iterator
   */
  iterator insert(iterator position, value_type&& val) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::insert(position,
                                                       std::move(val));
  }
  /**
   * @brief insert
   *
   * @tparam InputIterator InputIterator
   * @param first first
   * @param last last
   */
  template <class InputIterator>
  void insert(InputIterator first, InputIterator last) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::insert(first, last);
  }
  /**
   * @brief erase
   *
   * @param position position
   * @return iterator iterator
   */
  iterator erase(const_iterator position) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::erase(position);
  }
  /**
   * @brief erase
   *
   * @param k k
   * @return size_type size_type
   */
  size_type erase(const key_type& k) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::erase(k);
  }
  /**
   * @brief erase
   *
   * @param first first
   * @param last last
   * @return iterator iterator
   */
  iterator erase(const_iterator first, const_iterator last) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::erase(first, last);
  }
  /**
   * @brief clear
   *
   */
  void clear() noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::set<Key, Compare, Alloc>::clear();
  }
  /**
   * @brief emplace
   *
   * @tparam Args Args
   * @param args args
   * @return std::pair<iterator, bool> std::pair
   */
  template <class... Args>
  std::pair<iterator, bool> emplace(Args&&... args) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::emplace(args...);
  }
  /**
   * @brief emplace_hint
   *
   * @tparam Args Args
   * @param position position
   * @param args args
   * @return iterator iterator
   */
  template <class... Args>
  iterator emplace_hint(const_iterator position, Args&&... args) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::set<Key, Compare, Alloc>::emplace_hint(position, args...);
  }
  /**
   * @brief find
   *
   * @param k k
   * @return iterator iterator
   */
  iterator find(const key_type& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::set<Key, Compare, Alloc>::find(k);
  }
  /**
   * @brief find
   *
   * @param k k
   * @return const_iterator const_iterator
   */
  const_iterator find(const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::set<Key, Compare, Alloc>::find(k);
  }
  /**
   * @brief count
   *
   * @param k k
   * @return size_type size_type
   */
  size_type count(const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::set<Key, Compare, Alloc>::count(k);
  }
  /**
   * @brief call_each
   *
   * @tparam P p
   * @param pred pred
   */
  template <typename P>
  void call_each(P pred) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    std::for_each(this->std::set<Key, Compare, Alloc>::begin(),
                  this->std::set<Key, Compare, Alloc>::end(), pred);
  }
};
}  // namespace tscontainer
#endif  // __TSSET_H__
