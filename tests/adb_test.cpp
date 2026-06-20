#include "../src/adb/adb.hpp"

#include <cassert>

static void test_parse_adb_devices()
{
    const char *t1 = R"(List of devices attached
xyz-abc     device
)";
    vector<adb::Device> t1_res = adb::parse_adb_devices(t1);
    assert(t1_res.size() == 1);
    assert(t1_res[0].Serial == "xyz-abc");
    assert(t1_res[0].State == "device");

    const char *t2 = R"(* daemon not running; starting now at tcp:5037
* daemon started successfully
List of devices attached
)";
    vector<adb::Device> t2_res = adb::parse_adb_devices(t2);
    assert(t2_res.empty());

    const char *t3 = R"(List of devices attached
alioth     device
emulator-5554   device
)";
    vector<adb::Device> t3_res = adb::parse_adb_devices(t3);
    assert(t3_res.size() == 2);
    assert(t3_res[0].Serial == "alioth");
    assert(t3_res[1].Serial == "emulator-5554");

    const char *t4 = R"(List of devices attached
)";
    vector<adb::Device> t4_res = adb::parse_adb_devices(t4);
    assert(t4_res.empty());
}

int main()
{
    test_parse_adb_devices();

    return 0;
}