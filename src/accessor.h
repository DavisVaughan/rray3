#ifndef RRAY_ACCESSOR
#define RRAY_ACCESSOR

#include "rlang.h"

namespace rray {

  namespace detail {

    template <r_type T> struct get_value_type;
    template <> struct get_value_type<R_TYPE_logical> { using type = int; };
    template <> struct get_value_type<R_TYPE_integer> { using type = int; };
    template <> struct get_value_type<R_TYPE_double> { using type = double; };
    template <> struct get_value_type<R_TYPE_complex> { using type = r_complex_t; };
    template <> struct get_value_type<R_TYPE_raw> { using type = Rbyte; };
    template <> struct get_value_type<R_TYPE_character> { using type = r_obj*; };
    template <> struct get_value_type<R_TYPE_list> { using type = r_obj*; };

    template <r_type T>
    struct get_gettable_type {
      using type = typename get_value_type<T>::type const*;
    };

    template <r_type T>
    static
    inline
    typename get_gettable_type<T>::type
    cbegin(r_obj* x) {
      r_stop_internal("cbegin", "Unknown template type '%s'.", r_type_as_c_string(T));
    }
    template <>
    inline
    typename get_gettable_type<R_TYPE_logical>::type
    cbegin<R_TYPE_logical>(r_obj* x) {
      return r_lgl_cbegin(x);
    }
    template <>
    inline
    typename get_gettable_type<R_TYPE_integer>::type
    cbegin<R_TYPE_integer>(r_obj* x) {
      return r_int_cbegin(x);
    }
    template <>
    inline
    typename get_gettable_type<R_TYPE_double>::type
    cbegin<R_TYPE_double>(r_obj* x) {
      return r_dbl_cbegin(x);
    }
    template <>
    inline
    typename get_gettable_type<R_TYPE_complex>::type
    cbegin<R_TYPE_complex>(r_obj* x) {
      return r_cpl_cbegin(x);
    }
    template <>
    inline
    typename get_gettable_type<R_TYPE_raw>::type
    cbegin<R_TYPE_raw>(r_obj* x) {
      return static_cast<const Rbyte*>(RAW(x));
    }
    template <>
    inline
    typename get_gettable_type<R_TYPE_character>::type
    cbegin<R_TYPE_character>(r_obj* x) {
      return r_chr_cbegin(x);
    }
    template <>
    inline
    typename get_gettable_type<R_TYPE_list>::type
    cbegin<R_TYPE_list>(r_obj* x) {
      return r_list_cbegin(x);
    }

  }

  template <r_type T>
  class rgetter {
  public:
    using value_type = typename detail::get_value_type<T>::type;

    explicit rgetter(r_obj* x);

    value_type get(r_ssize i) const;
  private:
    using gettable_type = typename detail::get_gettable_type<T>::type;

    gettable_type m_getter;
  };

  template <r_type T>
  inline
  rgetter<T>::rgetter(r_obj* x)
    : m_getter(detail::cbegin<T>(x)) {
  }

  template <r_type T>
  inline
  auto
  rgetter<T>::get(r_ssize i) const -> value_type {
    return m_getter[i];
  }


  namespace detail {

    template <r_type T> struct get_settable_type;
    template <> struct get_settable_type<R_TYPE_logical> { using type = int*; };
    template <> struct get_settable_type<R_TYPE_integer> { using type = int*; };
    template <> struct get_settable_type<R_TYPE_double> { using type = double*; };
    template <> struct get_settable_type<R_TYPE_complex> { using type = r_complex_t*; };
    template <> struct get_settable_type<R_TYPE_raw> { using type = Rbyte*; };
    template <> struct get_settable_type<R_TYPE_character> { using type = r_obj*; };
    template <> struct get_settable_type<R_TYPE_list> { using type = r_obj*; };

    template <r_type T>
    static
    inline
    typename get_settable_type<T>::type
    begin(r_obj* x) {
      r_stop_internal("begin", "Unknown template type '%s'.", r_type_as_c_string(T));
    }
    template <>
    inline
    typename get_settable_type<R_TYPE_logical>::type
    begin<R_TYPE_logical>(r_obj* x) {
      return r_lgl_begin(x);
    }
    template <>
    inline
    typename get_settable_type<R_TYPE_integer>::type
    begin<R_TYPE_integer>(r_obj* x) {
      return r_int_begin(x);
    }
    template <>
    inline
    typename get_settable_type<R_TYPE_double>::type
    begin<R_TYPE_double>(r_obj* x) {
      return r_dbl_begin(x);
    }
    template <>
    inline
    typename get_settable_type<R_TYPE_complex>::type
    begin<R_TYPE_complex>(r_obj* x) {
      return r_cpl_begin(x);
    }
    template <>
    inline
    typename get_settable_type<R_TYPE_raw>::type
    begin<R_TYPE_raw>(r_obj* x) {
      return RAW(x);
    }
    template <>
    inline
    typename get_settable_type<R_TYPE_character>::type
    begin<R_TYPE_character>(r_obj* x) {
      return x;
    }
    template <>
    inline
    typename get_settable_type<R_TYPE_list>::type
    begin<R_TYPE_list>(r_obj* x) {
      return x;
    }
  }

  template <r_type T>
  class rsetter {
  public:
    using value_type = typename detail::get_value_type<T>::type;

    explicit rsetter(r_obj* x);

    void set(r_ssize i, value_type const& value);
  private:
    using settable_type = typename detail::get_settable_type<T>::type;

    settable_type m_setter;
  };

  template <r_type T>
  inline
  rsetter<T>::rsetter(r_obj* x)
    : m_setter(detail::begin<T>(x)) {
  }

  template <>
  inline void rsetter<R_TYPE_logical>::set(r_ssize i, int const& value) {
    m_setter[i] = value;
  }
  template <>
  inline void rsetter<R_TYPE_integer>::set(r_ssize i, int const& value) {
    m_setter[i] = value;
  }
  template <>
  inline void rsetter<R_TYPE_double>::set(r_ssize i, double const& value) {
    m_setter[i] = value;
  }
  template <>
  inline void rsetter<R_TYPE_complex>::set(r_ssize i, r_complex_t const& value) {
    m_setter[i] = value;
  }
  template <>
  inline void rsetter<R_TYPE_raw>::set(r_ssize i, Rbyte const& value) {
    m_setter[i] = value;
  }
  template <>
  inline void rsetter<R_TYPE_character>::set(r_ssize i, r_obj* const& value) {
    r_chr_poke(m_setter, i, value);
  }
  template <>
  inline void rsetter<R_TYPE_list>::set(r_ssize i, r_obj* const& value) {
    r_list_poke(m_setter, i, value);
  }
}

#endif
