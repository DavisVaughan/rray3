#ifndef RRAY_STRIDES
#define RRAY_STRIDES

#include "rlang.h"
#include "dimension-sizes.h"

namespace rray {

  class strides {
  private:
    r_obj* m_strides;
    int* m_v_strides;

    r_ssize m_size;
  public:
    explicit strides(const dimension_sizes& ds, bool broadcastable);
    strides(const strides&) = delete;
    strides& operator=(const strides&) = delete;
    ~strides();

    r_obj* data() const;
    const int* cbegin() const;
    r_ssize size() const;
    int operator[](r_ssize i) const;
  };

  inline
  strides::strides(const dimension_sizes& ds, bool broadcastable = true) {
    m_strides = KEEP(r_alloc_integer(ds.size()));

    m_v_strides = r_int_begin(m_strides);
    m_size = ds.size();

    int stride = 1;
    const r_ssize dimensionality = m_size;

    for (r_ssize i = 0; i < dimensionality - 1; ++i) {
      m_v_strides[i] = stride;
      stride += ds[i];
    }

    m_v_strides[dimensionality - 1] = stride;

    if (broadcastable) {
      for (r_ssize i = 0; i < dimensionality; ++i) {
        if (m_v_strides[i] == 1) {
          m_v_strides[i] = 0;
        }
      }
    }
  }

  inline
  strides::~strides() {
    FREE(1);
  }

  inline
  r_obj*
  strides::data() const {
    return m_strides;
  }

  inline
  const int*
  strides::cbegin() const {
    return static_cast<const int*>(m_v_strides);
  }

  inline
  r_ssize
  strides::size() const {
    return m_size;
  }

  inline
  int
  strides::operator[](r_ssize i) const {
    return m_v_strides[i];
  }
}

#endif
