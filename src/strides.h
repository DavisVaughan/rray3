#ifndef RRAY_STRIDES
#define RRAY_STRIDES

#include "rlang.h"
#include "dimension-sizes.h"

namespace rray {

  class strides {
  private:
    r_obj* m_shelter;

    r_obj* m_strides;
    int* m_v_strides;

    r_ssize m_size;
  public:
    explicit strides(const dimension_sizes& ds);
    strides(const strides&) = delete;
    strides& operator=(const strides&) = delete;

    r_obj* shelter() const;
    r_obj* data() const;
  };

  inline
  strides::strides(const dimension_sizes& ds) {
    m_shelter = KEEP(r_alloc_list(1));

    m_strides = r_alloc_integer(ds.size());
    r_list_poke(m_shelter, 0, m_strides);

    m_v_strides = r_int_begin(m_strides);
    m_size = ds.size();

    int stride = 1;
    const r_ssize dimensionality = m_size;

    for (r_ssize i = 0; i < dimensionality - 1; ++i) {
      m_v_strides[i] = stride;
      stride += ds[i];
    }

    m_v_strides[dimensionality - 1] = stride;

    for (r_ssize i = 0; i < dimensionality; ++i) {
      if (m_v_strides[i] == 1) {
        m_v_strides[i] = 0;
      }
    }

    FREE(1);
  }

  inline
  r_obj*
  strides::shelter() const {
    return m_shelter;
  }

  inline
  r_obj*
  strides::data() const {
    return m_strides;
  }
}

#endif
