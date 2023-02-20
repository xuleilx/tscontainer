/*****************************************************************************
* ADFS

*Copyright(c) 2022 Cambricon SingGo(Nanjing) Technology Co., Ltd.
*All Rights Reserved

*THIS WORK CONTAINS TRADE SECRET AND PROPRIETARY
*INFORMATION WHICH ARE THE PROPERTY OF CAMBRICON
*SING GO OR ITS LICENSORS AND IS
*SUBJECT TO LICENSE TERMS.
 ******************************************************************************/
#ifndef __TSMAP_H__
#define __TSMAP_H__
#include <algorithm>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <utility>
#include "adfsCore/Common/base/atomic_rw_lock.hpp"
#include "adfsCore/Common/base/rw_lock_guard.hpp"
namespace adfs {
/**
 * @brief tsmap
 *
 * @tparam Key key
 * @tparam T t
 * @tparam Compare compare
 * @tparam std::allocator<std::pair<const Key, T>> alloc
 */
template <class Key, class T, class Compare = std::less<Key>,
          class Alloc = std::allocator<std::pair<const Key, T>>>
class tsmap : public std::map<Key, T, Compare, Alloc> {
  // iterator
  using iterator = typename std::map<Key, T, Compare, Alloc>::iterator;
  // const_iterator
  using const_iterator =
      typename std::map<Key, T, Compare, Alloc>::const_iterator;
  // key_type
  using key_type = typename std::map<Key, T, Compare, Alloc>::key_type;
  // key_compare
  using key_compare = typename std::map<Key, T, Compare, Alloc>::key_compare;
  // allocator_type
  using allocator_type =
      typename std::map<Key, T, Compare, Alloc>::allocator_type;
  // value_type
  using value_type = typename std::map<Key, T, Compare, Alloc>::value_type;
  // mapped_type
  using mapped_type = typename std::map<Key, T, Compare, Alloc>::mapped_type;
  // size_type
  using size_type = typename std::map<Key, T, Compare, Alloc>::size_type;
  // map
  using map = typename std::map<Key, T, Compare, Alloc>;
  // mtx
  mutable base::AtomicRWLock mtx;

 public:
  /**
   * @brief Construct a new tsmap object
   *
   * @param comp compare
   * @param alloc alloc
   */
  explicit tsmap(const key_compare& comp = key_compare(),
                 const allocator_type& alloc = allocator_type()) noexcept
      : std::map<Key, T, Compare, Alloc>(comp, alloc) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param alloc alloc
   */
  explicit tsmap(const allocator_type& alloc)
      : std::map<Key, T, Compare, Alloc>(alloc) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @tparam InputIterator InputIterator
   * @param first first
   * @param last last
   * @param comp comp
   * @param alloc alloc
   */
  template <class InputIterator>
  tsmap(InputIterator first, InputIterator last,
        const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
      : std::map<Key, T, Compare, Alloc>(first, last, comp, alloc) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param x x
   */
  explicit tsmap(const map& x) : std::map<Key, T, Compare, Alloc>(x) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param x x
   */
  tsmap(const tsmap& x) : std::map<Key, T, Compare, Alloc>(x) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param x x
   * @param alloc alloc
   */
  tsmap(const tsmap& x, const allocator_type& alloc)
      : std::map<Key, T, Compare, Alloc>(x, alloc) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param x x
   */
  explicit tsmap(map&& x) : std::map<Key, T, Compare, Alloc>(x) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param x x
   */
  tsmap(tsmap&& x) : std::map<Key, T, Compare, Alloc>(x) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param x x
   * @param alloc alloc
   */
  tsmap(map&& x, const allocator_type& alloc)
      : std::map<Key, T, Compare, Alloc>(x, alloc) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param x x
   * @param alloc alloc
   */
  tsmap(tsmap&& x, const allocator_type& alloc)
      : std::map<Key, T, Compare, Alloc>(x, alloc) {}
  /**
   * @brief Construct a new tsmap object
   *
   * @param il il
   * @param comp comp
   * @param alloc alloc
   */
  tsmap(std::initializer_list<value_type> il,
        const key_compare& comp = key_compare(),
        const allocator_type& alloc = allocator_type())
      : std::map<Key, T, Compare, Alloc>(il, comp, alloc) {}
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsmap<Key, T, Compare, Alloc>& tsmap
   */
  tsmap<Key, T, Compare, Alloc>& operator=(const map& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsmap<Key, T, Compare, Alloc>& tsmap
   */
  tsmap<Key, T, Compare, Alloc>& operator=(
      const tsmap<Key, T, Compare, Alloc>& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsmap<Key, T, Compare, Alloc>& tsmap
   */
  tsmap<Key, T, Compare, Alloc>& operator=(map&& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param x x
   * @return tsmap<Key, T, Compare, Alloc>& tsmap
   */
  tsmap<Key, T, Compare, Alloc>& operator=(
      tsmap<Key, T, Compare, Alloc>&& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::operator=(x);
    return *this;
  }
  /**
   * @brief operator=
   *
   * @param il il
   * @return tsmap<Key, T, Compare, Alloc>& tsmap
   */
  tsmap<Key, T, Compare, Alloc>& operator=(
      std::initializer_list<value_type> il) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::operator=(il);
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
    return this->std::map<Key, T, Compare, Alloc>::empty();
  }
  /**
   * @brief size
   *
   * @return size_type size
   */
  size_type size() const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::size();
  }
  /**
   * @brief operator[]
   *
   * @param k k
   * @return mapped_type&
   */
  mapped_type& operator[](const key_type& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::operator[](k);
  }
  /**
   * @brief operator[]
   *
   * @param k k
   * @return mapped_type& mapped_type
   */
  mapped_type& operator[](key_type&& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::operator[](k);
  }
  /**
   * @brief at
   *
   * @param k k
   * @return mapped_type& mapped_type
   */
  mapped_type& at(const key_type& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::at(k);
  }

  /**
   * @brief at
   *
   * @param k k
   * @return const mapped_type& const mapped_type
   */
  const mapped_type& at(const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::at(k);
  }
  /**
   * @brief insert
   *
   * @param val val
   * @return std::pair<iterator, bool> std::pair
   */
  std::pair<iterator, bool> insert(const value_type& val) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::insert(val);
  }
  /**
   * @brief insert
   *
   * @param val val
   * @return std::pair<iterator, bool> std::pair
   */
  std::pair<iterator, bool> insert(value_type&& val) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::insert(std::move(val));
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
    return this->std::map<Key, T, Compare, Alloc>::insert(position, val);
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
    return this->std::map<Key, T, Compare, Alloc>::insert(position,
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
    return this->std::map<Key, T, Compare, Alloc>::insert(first, last);
  }
  /**
   * @brief erase
   *
   * @param position position
   * @return iterator iterator
   */
  iterator erase(const_iterator position) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::erase(position);
  }
  /**
   * @brief erase
   *
   * @param k k
   * @return size_type size_type
   */
  size_type erase(const key_type& k) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::erase(k);
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
    return this->std::map<Key, T, Compare, Alloc>::erase(first, last);
  }
  /**
   * @brief swap
   *
   * @param x x
   */
  void swap(map& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::swap(x);
  }
  /**
   * @brief swap
   *
   * @param x x
   */
  void swap(tsmap<Key, T, Compare, Alloc>& x) noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::swap(x);
  }
  /**
   * @brief clear
   *
   */
  void clear() noexcept {
    base::WriteLockGuard<base::AtomicRWLock> wlg{mtx};
    this->std::map<Key, T, Compare, Alloc>::clear();
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
    return this->std::map<Key, T, Compare, Alloc>::emplace(args...);
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
    return this->std::map<Key, T, Compare, Alloc>::emplace_hint(position,
                                                                args...);
  }
  /**
   * @brief find
   *
   * @param k k
   * @return iterator iterator
   */
  iterator find(const key_type& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::find(k);
  }
  /**
   * @brief find
   *
   * @param k k
   * @return const_iterator const_iterator
   */
  const_iterator find(const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::find(k);
  }
  /**
   * @brief count
   *
   * @param k k
   * @return size_type size_type
   */
  size_type count(const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::count(k);
  }
  /**
   * @brief lower_bound
   *
   * @param k k
   * @return iterator iterator
   */
  iterator lower_bound(const key_type& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::lower_bound(k);
  }
  /**
   * @brief lower_bound
   *
   * @param k k
   * @return const_iterator const_iterator
   */
  const_iterator lower_bound(const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::lower_bound(k);
  }
  /**
   * @brief upper_bound
   *
   * @param k k
   * @return iterator iterator
   */
  iterator upper_bound(const key_type& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::upper_bound(k);
  }
  /**
   * @brief upper_bound
   *
   * @param k k
   * @return const_iterator const_iterator
   */
  const_iterator upper_bound(const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::upper_bound(k);
  }
  /**
   * @brief equal_range
   *
   * @param k k
   * @return std::pair<const_iterator, const_iterator> std::pair
   */
  std::pair<const_iterator, const_iterator> equal_range(
      const key_type& k) const noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::equal_range(k);
  }
  /**
   * @brief equal_range
   *
   * @param k k
   * @return std::pair<iterator, iterator> std::pair
   */
  std::pair<iterator, iterator> equal_range(const key_type& k) noexcept {
    base::ReadLockGuard<base::AtomicRWLock> rlg{mtx};
    return this->std::map<Key, T, Compare, Alloc>::equal_range(k);
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
    std::for_each(this->std::map<Key, T, Compare, Alloc>::begin(),
                  this->std::map<Key, T, Compare, Alloc>::end(), pred);
  }
};
}  // namespace adfs
#endif  // __CONCURRENTMAP_H__
