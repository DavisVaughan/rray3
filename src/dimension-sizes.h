#ifndef RRAY_DIMENSION_SIZES
#define RRAY_DIMENSION_SIZES

#include "rlang.h"

namespace rray {

  namespace detail {

    static inline
    bool is_atomic(const enum r_type& type) {
      switch(type) {
      case R_TYPE_logical:
      case R_TYPE_integer:
      case R_TYPE_double:
      case R_TYPE_complex:
      case R_TYPE_raw:
      case R_TYPE_character:
      case R_TYPE_list:
        return true;
      default:
        return false;
      }
    }

    [[noreturn]]
    static inline
    void stop_non_atomic_typeof(const enum r_type& type) {
      r_abort(
        "`x` must be an atomic vector type, not a <%s>.",
        r_type_as_c_string(type)
      );
    }

  }

  class dimension_sizes {
  private:
    r_obj* m_shelter;

    r_obj* m_dimension_sizes;
    int* m_v_dimension_sizes;

    r_ssize m_size;
  public:
    explicit dimension_sizes(r_obj* x);
    dimension_sizes(const dimension_sizes&) = delete;
    dimension_sizes& operator=(const dimension_sizes&) = delete;

    r_obj* shelter() const;
    r_obj* data() const;
    const int* cbegin() const;
    r_ssize size() const;
    int operator[](r_ssize i) const;
  };

  inline
  dimension_sizes::dimension_sizes(r_obj* x) {
    m_shelter = KEEP(r_alloc_list(1));

    r_obj* dimension_sizes = r_dim(x);

    if (dimension_sizes == r_null) {
      const r_type type = r_typeof(x);

      if (!detail::is_atomic(type)) {
        detail::stop_non_atomic_typeof(type);
      }

      dimension_sizes = r_int(r_ssize_as_integer(r_length(x)));
    }

    m_dimension_sizes = dimension_sizes;
    r_list_poke(m_shelter, 0, m_dimension_sizes);

    m_v_dimension_sizes = r_int_begin(m_dimension_sizes);
    m_size = r_length(m_dimension_sizes);

    FREE(1);
  }

  inline
  r_obj*
  dimension_sizes::shelter() const {
    return m_shelter;
  }

  inline
  r_obj*
  dimension_sizes::data() const {
    return m_dimension_sizes;
  }

  inline
  const int*
  dimension_sizes::cbegin() const {
    return static_cast<const int*>(m_v_dimension_sizes);
  }

  inline
  r_ssize
  dimension_sizes::size() const {
    return m_size;
  }

  inline
  int
  dimension_sizes::operator[](r_ssize i) const {
    return m_v_dimension_sizes[i];
  }


  static inline
  void poke_dimension_sizes(r_obj* x, const dimension_sizes& ds) {
    r_attrib_poke_dim(x, ds.data());
  }
}

#endif
