#include <string>
#include <vector>
#include "pch.h"
#include "SubnetCaculator.h"

SubnetCaculator subnet("192.168.0.180", "255.255.255.192");

TEST(SubnetCaculatorTest, GetAvailableNetMaskTest) 
{
	vector<vector<int>> answer = {
		{255, 255, 255, 0},
		{255, 255, 255, 128},
		{255, 255, 255, 192},
		{255, 255, 255, 224},
		{255, 255, 255, 240},
		{255, 255, 255, 248},
		{255, 255, 255, 252}
	};
	vector<vector<int>>available_netmask_list = SubnetCaculator::GetAvailableNetMask('c');

	EXPECT_EQ(available_netmask_list, answer);
}



TEST(SubnetCaculatorTest, OctetIPTest)
{
	std::vector<int> answer = { 192, 168, 0, 180 };
	std::vector<int> octets_ip = subnet.OctetIP();

	EXPECT_EQ(octets_ip, answer);
}


TEST(SubnetCaculatorTest, OctetNetmaskTest)
{
	std::vector<int> answer = { 255, 255, 255, 192 };
	std::vector<int> octets_netmask = subnet.OctetNetmask();

	EXPECT_EQ(octets_netmask, answer);
}


TEST(SubnetCaculatorTest, GetNetIDTest)
{
	vector<int> answer = { 192, 168, 0, 128 };
	vector<int> net_id = subnet.GetNetID();

	EXPECT_EQ(net_id, answer);
}



TEST(SubnetCaculatorTest, GetNetIDRangeTest)
{
	vector<int> answer = { 192, 168, 0, 131 };
	vector<int> brocast_id = subnet.GetNetIDRange();

	EXPECT_EQ(brocast_id, answer);
}


TEST(SubnetCaculatorTest, GetHostsPerSubnetTest)
{
	int answer = 62;
	int total_hosts = subnet.GetHostsPerSubnet();
	EXPECT_EQ(total_hosts, answer);
}


TEST(SubnetCaculatorTest, VevtIpToDecimalTest)
{
	int answer = 3232235700;
	int ip = subnet.IpToDecimal(subnet.OctetIP());
	EXPECT_EQ(ip, answer);
}


TEST(SubnetCaculatorTest, StrIpToDecimalTest)
{
	int answer = 3699800002;
	int ip = subnet.IpToDecimal("220.134.119.194");
	EXPECT_EQ(ip, answer);
}


TEST(SubnetCaculatorTest, GetIncrementTest)
{
	int answer = 4;
	int increment = subnet.GetIncrement();
	EXPECT_EQ(increment, answer);
}

//subnet.DecimalToIpString
TEST(SubnetCaculatorTest, DecimalToIpStringTest)
{
	string answer = "220.134.119.194";
	string ip = subnet.DecimalToIpString(subnet.IpToDecimal(answer));

	EXPECT_EQ(ip, answer);
}


TEST(SubnetCaculatorTest, StartIpStringTest)
{
	string start_ip = subnet.StartIpString();
	string start_ip_answer = "192.168.0.129";

	EXPECT_EQ(start_ip, start_ip_answer);

	string latest_ip = subnet.LatestIpString();
	string latest_ip_answer = "192.168.0.190";

	EXPECT_EQ(latest_ip, latest_ip_answer);
}