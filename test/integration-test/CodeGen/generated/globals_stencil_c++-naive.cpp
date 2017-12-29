// gtclang (0.0.1-c392bf6-x86_64-linux-gnu-5.4.0)
// based on LLVM/Clang (3.8.0), Dawn (0.0.1)
// Generated on 2017-12-28  02:54:38

#define GRIDTOOLS_CLANG_GENERATED 1
#define GRIDTOOLS_CLANG_HALO_EXTEND 3
#ifndef BOOST_RESULT_OF_USE_TR1
 #define BOOST_RESULT_OF_USE_TR1 1
#endif
#ifndef BOOST_NO_CXX11_DECLTYPE
 #define BOOST_NO_CXX11_DECLTYPE 1
#endif
//===--------------------------------------------------------------------------------*- C++ -*-===//
//                         _       _
//                        | |     | |
//                    __ _| |_ ___| | __ _ _ __   __ _
//                   / _` | __/ __| |/ _` | '_ \ / _` |
//                  | (_| | || (__| | (_| | | | | (_| |
//                   \__, |\__\___|_|\__,_|_| |_|\__, | - GridTools Clang DSL
//                    __/ |                       __/ |
//                   |___/                       |___/
//
//
//  This file is distributed under the MIT License (MIT).
//  See LICENSE.txt for details.
//
//===------------------------------------------------------------------------------------------===//

#include "gridtools/clang_dsl.hpp"

using namespace gridtools::clang;

namespace cxxnaive {

struct globals : public gridtools::clang::globals_impl<globals> {
  using base_t = gridtools::clang::globals_impl<globals>;

  struct var_compiletime_adapter : public base_t::variable_adapter_impl<bool> {
    var_compiletime_adapter() : base_t::variable_adapter_impl<bool>(bool(true)) {}

    template <class ValueType>
    var_compiletime_adapter& operator=(ValueType&& value) {
      throw std::runtime_error("invalid assignment to constant variable 'var_compiletime'");
      return *this;
    }
  } var_compiletime;

  struct var_default_adapter : public base_t::variable_adapter_impl<int> {
    var_default_adapter() : base_t::variable_adapter_impl<int>(int(2)) {}

    template <class ValueType>
    var_default_adapter& operator=(ValueType&& value) {
      get_value() = value;
      return *this;
    }
  } var_default;

  struct var_runtime_adapter : public base_t::variable_adapter_impl<int> {
    var_runtime_adapter() : base_t::variable_adapter_impl<int>(int()) {}

    template <class ValueType>
    var_runtime_adapter& operator=(ValueType&& value) {
      get_value() = value;
      return *this;
    }
  } var_runtime;
};
template <>
globals* gridtools::clang::globals_impl<globals>::s_instance = nullptr;
}  // namespace cxxnaiv
;

namespace cxxnaive {

class globals_stencil {
 private:
  template <class DataView>
  struct ParamWrapper {
    DataView dview_;
    std::array<int, DataView::storage_info_t::ndims> offsets_;

    ParamWrapper(DataView dview, std::array<int, DataView::storage_info_t::ndims> offsets)
        : dview_(dview), offsets_(offsets) {}
  };

  struct sbase {
    virtual void run() {}

    virtual ~sbase() {}
  };
  template <class StorageType0, class StorageType1>
  struct stencil_0 : public sbase {
    // //Members
    const gridtools::clang::domain& m_dom;
    StorageType0& m_in;
    StorageType1& m_out;

   public:
    stencil_0(const gridtools::clang::domain& dom_, StorageType0& in_, StorageType1& out_)
        : m_dom(dom_), m_in(in_), m_out(out_) {}

    ~stencil_0() {}

    virtual void run() {
      gridtools::data_view<StorageType0> in = gridtools::make_host_view(m_in);
      gridtools::data_view<StorageType1> out = gridtools::make_host_view(m_out);
      for (int k = 0; k <= (m_dom.ksize() == 0 ? 0 : (m_dom.ksize() - m_dom.kplus() - 1)); ++k) {
        for (int i = m_dom.iminus(); i <= m_dom.isize() - m_dom.iplus() - 1; ++i) {
          for (int j = m_dom.jminus(); j <= m_dom.jsize() - m_dom.jplus() - 1; ++j) {
            if ((bool)true) {
              out(i + 0, j + 0, k + 0) =
                  ((in(i + 0, j + 0, k + 0) + globals::get().var_runtime) + globals::get().var_default);
            }
          }
        }
      }
    }
  };
  static constexpr const char* s_name = "globals_stencil";
  sbase* m_stencil_0;

 public:
  globals_stencil(const globals_stencil&) = delete;

  // Members

  template <class StorageType1, class StorageType2>
  globals_stencil(const gridtools::clang::domain& dom, StorageType1& in, StorageType2& out)
      : m_stencil_0(new stencil_0<StorageType1, StorageType2>(dom, in, out)) {}

  void run() { m_stencil_0->run(); }
};
}  // namespace cxxnaiv
;

// int main() {
//  domain dom(64, 64, 80);
//  dom.set_halos(halo::value, halo::value, halo::value, halo::value, 0, 0);
//  verifier verif(dom);

//  meta_data_t meta_data(dom.isize(), dom.jsize(), dom.ksize());
//  storage_t s(meta_data, "s"), s_ref(meta_data, "s_ref");

//  verif.fill(-1.0, s);
//  verif.fill(3.0, s_ref);

//  globals::get().var_runtime = 1;

//  Test01 test(dom, s);
//  test.run();

//  return !verif.verify(s, s_ref);
//}
