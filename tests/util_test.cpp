#include "../src/util/util.hpp"

#include <cassert>

static void test_split_string()
{
    string t1 = R"(package:com.android.nfc
package:com.android.devicelockcontroller)";

    vector<string> t1_res = util::split_string(t1, '\n');
    assert("package:com.android.nfc" == t1_res[0]);
    assert("package:com.android.devicelockcontroller" == t1_res[1]);

    vector<string> t2_res = util::split_string(t1_res[0], ':');
    assert("package" == t2_res[0]);
    assert("com.android.nfc" == t2_res[1]);

    string t3 = R"(com.xyz.abc,in.def.uvw,org.rst.ghi)";
    vector<string> t3_res = util::split_string(t3, ',');
    assert("com.xyz.abc" == t3_res[0]);
    assert("org.rst.ghi" == t3_res[2]);
}

static void test_trim_string()
{
    string t1 = " org.rst.ghi ";
    assert("org.rst.ghi" == util::trim_string(t1));

    string t2 = "\r com.android.nfc\n\t";
    assert("com.android.nfc" == util::trim_string(t2));

    string t3 = R"(
    com
    xyz
    abc
    )";
    assert("com\n    xyz\n    abc" == util::trim_string(t3));
}

static void test_uset_difference()
{
    unordered_set<string> t1_a = {"org", "com", "in"};
    unordered_set<string> t1_b = {"a", "in"};
    unordered_set<string> t1_exp = {"org", "com"};
    assert(t1_exp == util::uset_difference(t1_a, t1_b));
    assert(t1_exp == util::uset_difference(t1_b, t1_a));

    // All packages including uninstalled system packages
    // command: pm list packages -u
    unordered_set<string> t2_a = {
        "org.lineageos.aperture",
        "org.lineageos.camelot",
        "org.lineageos.recorder",
        "org.lineageos.glimpse",
    };
    // Packages other than uninstalled system packages
    // command: pm list packages
    unordered_set<string> t2_b = {
        "org.lineageos.aperture",
        "org.lineageos.recorder",
        "org.lineageos.camelot",
    };
    // Packages that can be installed using install-existing
    unordered_set<string> t2_exp = {"org.lineageos.glimpse"};
    assert(t2_exp == util::uset_difference(t2_a, t2_b));
    assert(t2_exp == util::uset_difference(t2_b, t2_a));

    unordered_set<string> t3_exp;
    assert(t3_exp == util::uset_difference(t1_a, t1_a));
}

int main()
{
    test_split_string();
    test_trim_string();
    test_uset_difference();
    return 0;
}