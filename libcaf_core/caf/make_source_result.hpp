/******************************************************************************
 *                       ____    _    _____                                   *
 *                      / ___|  / \  |  ___|    C++                           *
 *                     | |     / _ \ | |_       Actor                         *
 *                     | |___ / ___ \|  _|      Framework                     *
 *                      \____/_/   \_|_|                                      *
 *                                                                            *
 * Copyright 2011-2018 Dominik Charousset                                     *
 *                                                                            *
 * Distributed under the terms and conditions of the BSD 3-Clause License or  *
 * (at your option) under the terms and conditions of the Boost Software      *
 * License 1.0. See accompanying files LICENSE and LICENSE_ALTERNATIVE.       *
 *                                                                            *
 * If you did not receive a copy of the license files, see                    *
 * http://opensource.org/licenses/BSD-3-Clause and                            *
 * http://www.boost.org/LICENSE_1_0.txt.                                      *
 ******************************************************************************/

#ifndef CAF_MAKE_SOURCE_RESULT_HPP
#define CAF_MAKE_SOURCE_RESULT_HPP

#include "caf/fwd.hpp"
#include "caf/stream_slot.hpp"
#include "caf/stream_source.hpp"

#include "caf/detail/implicit_conversions.hpp"

namespace caf {

/// Helper trait for deducing an `output_stream` from the arguments to
/// `scheduled_actor::make_source`.
template <class DownstreamManager, class... Ts>
struct make_source_result {
  /// Type of a single element.
  using output_type = typename DownstreamManager::output_type;

  /// Fully typed stream manager as returned by `make_source`.
  using source_type = stream_source<output_type, DownstreamManager>;

  /// Pointer to a fully typed stream manager.
  using source_ptr_type = intrusive_ptr<source_type>;

  /// The return type for `scheduled_actor::make_source`.
  using type = output_stream<output_type, std::tuple<Ts...>, source_ptr_type>;
};

/// Helper type for defining an `output_stream` from a downstream manager plus
/// the types of the handshake arguments.
template <class DownstreamManager, class... Ts>
using make_source_result_t =
  typename make_source_result<DownstreamManager,
                              detail::strip_and_convert_t<Ts>...>::type;

} // namespace caf

#endif // CAF_MAKE_SOURCE_RESULT_HPP
