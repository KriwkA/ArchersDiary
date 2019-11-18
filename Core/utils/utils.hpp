#pragma once

#include <utility>
#include <functional>
#include <optional>

namespace utils {

namespace details {

template<typename T, typename F>
constexpr inline bool compare_eq(const T& m1, const T& m2, const F& fld) noexcept {
   return (m1.*fld) == (m2.*fld);
}

template<typename T, typename F, typename ...Flds>
constexpr inline bool compare_eq(const T& m1, const T& m2, const F& fld, Flds... flds) noexcept {
   return (m1.*fld) == (m2.*fld) && compare_eq(m1, m2, std::forward<Flds>(flds)...);
}

template<typename T, typename F>
constexpr inline bool compare_le(const T& m1, const T& m2, const F& fld) noexcept {
   return (m1.*fld) < (m2.*fld);
}

template<typename T, typename F, typename ...Flds>
constexpr inline bool compare_le(const T& m1, const T& m2, const F& fld, Flds... flds) noexcept {
   return (m1.*fld) < (m2.*fld) || (compare_eq(m1, m2, fld) && compare_le(m1, m2, std::forward<Flds>(flds)...));
}

template<typename T, typename F>
constexpr inline bool compare_ge(const T& m1, const T& m2, const F& fld) noexcept {
   return (m1.*fld) > (m2.*fld);
}

template<typename T, typename F, typename ...Flds>
constexpr inline bool compare_ge(const T& m1, const T& m2, const F& fld, Flds... flds) noexcept {
   return (m1.*fld) > (m2.*fld) || (compare_eq(m1, m2, fld) && compare_le(m1, m2, std::forward<Flds>(flds)...));
}

}

template<typename T, typename ...Flds>
constexpr inline bool compare_eq(const T& m1, const T& m2, Flds... flds) noexcept {
   return &m1 == &m2 || details::compare_eq(m1, m2, std::forward<Flds>(flds)...);
}

template<typename T, typename ...Flds>
constexpr inline bool compare_le(const T& m1, const T& m2, Flds... flds) noexcept {
   return &m1 != &m2 && details::compare_le(m1, m2, std::forward<Flds>(flds)...);
}

template<typename T, typename ...Flds>
constexpr inline bool compare_ge(const T& m1, const T& m2, Flds... flds) noexcept {
   return &m1 != &m2 && details::compare_ge(m1, m2, std::forward<Flds>(flds)...);
}

template <class T>
constexpr inline void hash_combine(size_t& seed, const T& v) noexcept {
    seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}


template<typename T, typename ...Flds>
constexpr inline size_t hash(const T& m, Flds... flds) noexcept {
   size_t res = 0;
   (hash_combine(res, (m.*flds)), ...);
   return res;
}

template<typename T>
class Lazy {
   std::optional<T> m_data;
   std::function<T()> m_initFunc;
public:
   constexpr inline Lazy(const std::function<T()>& init_func) noexcept : m_initFunc(init_func) {}

   constexpr inline Lazy(Lazy&&) = default;
   constexpr inline Lazy(const Lazy&) = default;
   constexpr inline Lazy& operator=(Lazy&&) = default;
   constexpr inline Lazy& operator=(const Lazy&) = default;
   ~Lazy() = default;

   constexpr inline void reset() noexcept { m_data.reset(); }

   constexpr T& get() {
      if(m_data) {
         return *m_data;
      }
      m_data = m_initFunc();
      return *m_data;
   }

   constexpr inline T& get() const {
      return const_cast<Lazy&>(*this).get();
   }

};

}