#include <uuid_short/uuid_short.hpp>
#include <cassert>
#include <string>

namespace
{
  void test_generate_default()
  {
    const uuid_short::Result result = uuid_short::generate();

    assert(result.ok);
    assert(result.error.empty());
    assert(!result.value.empty());
    assert(result.value.size() == 12);
  }

  void test_generate_custom_length()
  {
    uuid_short::Options opt;
    opt.length = 20;

    const uuid_short::Result result = uuid_short::generate(opt);

    assert(result.ok);
    assert(result.value.size() == 20);
  }

  void test_generate_with_prefix()
  {
    uuid_short::Options opt;
    opt.prefix = "user";
    opt.separator = "_";
    opt.length = 10;

    const uuid_short::Result result = uuid_short::generate(opt);

    assert(result.ok);
    assert(result.value.rfind("user_", 0) == 0);
    assert(result.value.size() == 15); // "user_" + 10
  }

  void test_generate_with_custom_alphabet()
  {
    uuid_short::Options opt;
    opt.length = 16;
    opt.alphabet = "ABC123";

    const uuid_short::Result result = uuid_short::generate(opt);

    assert(result.ok);
    assert(result.value.size() == 16);

    for (char ch : result.value)
    {
      assert(opt.alphabet.find(ch) != std::string_view::npos);
    }
  }

  void test_make_default()
  {
    const std::string id = uuid_short::make();

    assert(!id.empty());
    assert(id.size() == 12);
  }

  void test_make_custom_length()
  {
    const std::string id = uuid_short::make(8);

    assert(id.size() == 8);
  }

  void test_make_prefixed()
  {
    const std::string id = uuid_short::make_prefixed("req", 6, "-");

    assert(id.rfind("req-", 0) == 0);
    assert(id.size() == 10); // "req-" + 6
  }

  void test_make_with_alphabet()
  {
    const std::string alphabet = "01";
    const std::string id = uuid_short::make_with_alphabet(32, alphabet);

    assert(id.size() == 32);

    for (char ch : id)
    {
      assert(ch == '0' || ch == '1');
    }
  }

  void test_invalid_length()
  {
    uuid_short::Options opt;
    opt.length = 0;

    const uuid_short::Result result = uuid_short::generate(opt);

    assert(!result.ok);
    assert(!result.error.empty());
    assert(result.value.empty());
  }

  void test_invalid_alphabet()
  {
    uuid_short::Options opt;
    opt.length = 8;
    opt.alphabet = "A";

    const uuid_short::Result result = uuid_short::generate(opt);

    assert(!result.ok);
    assert(!result.error.empty());
    assert(result.value.empty());
  }

} // namespace

int main()
{
  test_generate_default();
  test_generate_custom_length();
  test_generate_with_prefix();
  test_generate_with_custom_alphabet();
  test_make_default();
  test_make_custom_length();
  test_make_prefixed();
  test_make_with_alphabet();
  test_invalid_length();
  test_invalid_alphabet();

  return 0;
}
