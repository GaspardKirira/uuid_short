/**
 * @file uuid_short.hpp
 * @brief Short unique ID generation utilities for C++.
 *
 * `uuid_short` provides a small, dependency-free, header-only toolkit for
 * generating compact unique identifiers for applications that need readable,
 * URL-friendly, and reasonably unique IDs without the verbosity of full UUIDs.
 *
 * This library is intentionally simple and focuses on practical identifier
 * generation for common use cases such as database records, short links,
 * temporary tokens, request tracing, filenames, and lightweight object IDs.
 *
 * Supported generation modes:
 * - Random alphanumeric IDs
 * - Custom alphabet IDs
 * - Prefix-based IDs
 *
 * Design goals:
 * - Header-only and dependency-free
 * - Small and practical API surface
 * - Compact identifier output
 * - Easy integration into applications and libraries
 * - Configurable alphabet and length
 * - Suitable for open source and production usage
 *
 * Non-goals:
 * - RFC-compliant UUID generation
 * - Cryptographic identity guarantees
 * - Distributed monotonic sequence coordination
 * - Full ULID or UUID replacement semantics
 *
 * Notes:
 * - This library is designed for compact unique identifiers, not strict
 *   universally unique identity guarantees across all systems forever.
 * - For security-sensitive tokens, prefer a dedicated cryptographic solution.
 * - Uniqueness depends on the selected alphabet, output length, and runtime
 *   random source quality.
 *
 * Requirements: C++17+
 */

#ifndef UUID_SHORT_UUID_SHORT_HPP
#define UUID_SHORT_UUID_SHORT_HPP

#include <cstddef>
#include <cstdint>
#include <random>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>

namespace uuid_short
{
  /**
   * @brief Result type used by non-throwing APIs.
   */
  struct Result
  {
    bool ok = false;
    std::string value;
    std::string error;

    /**
     * @brief Create a successful result.
     */
    static Result success(std::string text)
    {
      return Result{true, std::move(text), {}};
    }

    /**
     * @brief Create a failed result.
     */
    static Result failure(std::string message)
    {
      return Result{false, {}, std::move(message)};
    }
  };

  /**
   * @brief Options controlling ID generation behavior.
   */
  struct Options
  {
    /**
     * @brief Output length of the generated ID.
     */
    std::size_t length = 12;

    /**
     * @brief Alphabet used for generated characters.
     *
     * Default alphabet is URL-friendly and excludes special characters.
     */
    std::string_view alphabet =
        "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    /**
     * @brief Optional prefix prepended to the generated ID.
     *
     * Example:
     * - prefix = "usr_"
     * - generated = "usr_A7f92kLmQx1P"
     */
    std::string_view prefix = {};

    /**
     * @brief Optional separator inserted between prefix and generated ID.
     *
     * Only used when prefix is not empty.
     */
    std::string_view separator = {};
  };

  namespace detail
  {
    inline bool is_valid_length(std::size_t length) noexcept
    {
      return length > 0;
    }

    inline bool is_valid_alphabet(std::string_view alphabet) noexcept
    {
      return alphabet.size() >= 2;
    }

    inline std::mt19937_64 &rng()
    {
      static thread_local std::mt19937_64 engine{std::random_device{}()};
      return engine;
    }

    inline char random_char_from(std::string_view alphabet)
    {
      std::uniform_int_distribution<std::size_t> dist(0, alphabet.size() - 1);
      return alphabet[dist(rng())];
    }

    inline Result validate_options(const Options &opt)
    {
      if (!is_valid_length(opt.length))
      {
        return Result::failure("uuid_short: length must be greater than 0");
      }

      if (!is_valid_alphabet(opt.alphabet))
      {
        return Result::failure("uuid_short: alphabet must contain at least 2 characters");
      }

      return Result::success({});
    }

    inline std::string generate_impl(const Options &opt)
    {
      std::string out;
      out.reserve(opt.prefix.size() +
                  (opt.prefix.empty() ? 0 : opt.separator.size()) +
                  opt.length);

      if (!opt.prefix.empty())
      {
        out.append(opt.prefix.data(), opt.prefix.size());
        if (!opt.separator.empty())
          out.append(opt.separator.data(), opt.separator.size());
      }

      for (std::size_t i = 0; i < opt.length; ++i)
        out.push_back(random_char_from(opt.alphabet));

      return out;
    }

  } // namespace detail

  /**
   * @brief Generate a compact random identifier.
   *
   * This is the primary non-throwing API.
   *
   * @param opt Generation options.
   * @return Result containing the generated identifier or an error.
   */
  inline Result generate(const Options &opt = {})
  {
    const Result validation = detail::validate_options(opt);
    if (!validation.ok)
      return validation;

    return Result::success(detail::generate_impl(opt));
  }

  /**
   * @brief Generate a compact random identifier and throw on invalid options.
   *
   * @param opt Generation options.
   * @return Generated identifier.
   * @throws std::runtime_error if options are invalid.
   */
  inline std::string generate_or_throw(const Options &opt = {})
  {
    const Result r = generate(opt);
    if (!r.ok)
      throw std::runtime_error(r.error);
    return r.value;
  }

  /**
   * @brief Generate a compact random identifier using the default options.
   *
   * Equivalent to:
   *
   * @code
   * uuid_short::generate_or_throw()
   * @endcode
   *
   * @return Generated identifier.
   */
  inline std::string make()
  {
    return generate_or_throw();
  }

  /**
   * @brief Generate a compact random identifier with a custom length.
   *
   * @param length Number of random characters to generate.
   * @return Generated identifier.
   * @throws std::runtime_error if length is invalid.
   */
  inline std::string make(std::size_t length)
  {
    Options opt;
    opt.length = length;
    return generate_or_throw(opt);
  }

  /**
   * @brief Generate a compact random identifier with a prefix.
   *
   * Example output:
   * - "user_Ab91xYk20Q"
   *
   * @param prefix Prefix to prepend.
   * @param length Number of random characters to generate.
   * @param separator Separator placed between prefix and ID.
   * @return Generated identifier.
   * @throws std::runtime_error if options are invalid.
   */
  inline std::string make_prefixed(std::string_view prefix,
                                   std::size_t length = 12,
                                   std::string_view separator = "_")
  {
    Options opt;
    opt.length = length;
    opt.prefix = prefix;
    opt.separator = separator;
    return generate_or_throw(opt);
  }

  /**
   * @brief Generate a compact random identifier using a custom alphabet.
   *
   * @param length Number of random characters to generate.
   * @param alphabet Alphabet to use.
   * @return Generated identifier.
   * @throws std::runtime_error if options are invalid.
   */
  inline std::string make_with_alphabet(std::size_t length, std::string_view alphabet)
  {
    Options opt;
    opt.length = length;
    opt.alphabet = alphabet;
    return generate_or_throw(opt);
  }

} // namespace uuid_short

#endif // UUID_SHORT_UUID_SHORT_HPP
