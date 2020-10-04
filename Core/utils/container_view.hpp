#pragma once

namespace core::utils {


template<typename vType>
class ContainterView {
protected:

   struct v_it {
      virtual ~v_it() = default;

      virtual const vType& operator*() const noexcept = 0;
      virtual v_it& operator++() noexcept = 0;
      virtual bool operator==(const v_it&) const noexcept = 0;
   };

   struct v_it_bin {
      char data[40] = {0};
   };

   template<typename V_IT>
   static v_it_bin make_v_it_bin(V_IT it) noexcept {
      static_assert (sizeof (it) <= sizeof (v_it_bin), "V_IT size error" );
      v_it_bin res;
      using used_data = char[sizeof (it)];
      memcpy(&reinterpret_cast<used_data&>(res), &reinterpret_cast<used_data&>(it), sizeof(used_data));
      return res;
   }

   virtual v_it_bin bin_begin() const noexcept = 0;
   virtual v_it_bin bin_end() const noexcept = 0;

   virtual size_t index(const v_it& it) const noexcept = 0;


public:

   struct const_iterator : public std::iterator<std::forward_iterator_tag,
                                                vType, vType, vType*, vType&> {
      using value_type = vType;

      const value_type& operator*() const noexcept {
         return *iter();
      }

      const_iterator& operator++() noexcept {
         ++iter();
         return *this;
      }

      const_iterator operator++(int) noexcept {
         auto res = *this;
         ++iter();
         return *this;
      }

      bool operator==(const const_iterator& it) const noexcept {
         return iter() == it.iter();
      }

      bool operator!=(const const_iterator& it) const noexcept { return !operator==(it); }


   private:
      inline const_iterator(v_it_bin&& it) noexcept : m_it(std::move(it)){

      }

      v_it& iter() noexcept {
         return *static_cast<v_it*>(static_cast<void*>(&m_it));
      }

      const v_it& iter() const noexcept {
         return *static_cast<const v_it*>(static_cast<const void*>(&m_it));
      }

      friend class ContainterView;

      v_it_bin m_it;
   };

   const_iterator begin() const noexcept {
      return {bin_begin()};
   }

   const_iterator end() const noexcept {
      return {bin_end()};
   }

   size_t index(const const_iterator& it) const noexcept {
      return index(it.iter());
   }

   virtual size_t size() const noexcept = 0;


};

template<typename Container>
class ContainterViewImpl : public ContainterView<typename Container::value_type> {
   using base = ContainterView<typename Container::value_type>;
   using value_type = typename Container::value_type;
   const Container& m_container;

   using v_it = typename base::v_it;
   using v_it_bin = typename base::v_it_bin;

   struct it_impl : v_it {
      using it_type = typename Container::const_iterator;
      it_type m_it;

      it_impl(it_type&& it) : m_it(std::move(it)) {}

      const value_type& operator *() const noexcept override {
         return *m_it;
      }

      typename base::v_it& operator ++() noexcept override {
         ++m_it;
         return *this;
      }

      bool operator ==(const v_it& it) const noexcept override {
         return m_it == static_cast<const it_impl&>(it).m_it;
      }
   };

public:
   constexpr inline ContainterViewImpl(const Container& cont) noexcept : m_container(cont) {}

   size_t index(const v_it& it) const noexcept override {
      return std::distance(m_container.begin(), static_cast<const it_impl&>(it).m_it);
   }

   size_t size() const noexcept override {
      return m_container.size();
   }


protected:
   v_it_bin bin_begin() const noexcept override {
      return base::make_v_it_bin(it_impl{m_container.begin()});
   }

   v_it_bin bin_end() const noexcept override {
      return base::make_v_it_bin(it_impl{m_container.end()});
   }
};


}
