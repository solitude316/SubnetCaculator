/*----------------------------------------
ViewSonic Corporation, PMSD
Module Name :  SubnetCaculator.h
Abstract : Subnet Caculator
Author : Eric Teng
Date : 2021/01/08
----------------------------------------*/

#pragma once
#include <string>
#include <vector>
using std::vector;
using std::string;

class SubnetCaculator
{
public:
	// Default constructor;
	SubnetCaculator();

	// Constructor with ip address and netmask
	SubnetCaculator(const std::string &, const std::string &);

	// Destructor
	~SubnetCaculator();

	// Set Ip address and convert it to octet format;
	bool SetOctetIp(const std::string &);

	// Set netmask and convert it to octet format;
	bool SetOctetNetmask(const std::string &);

	// Convert ip from string to octet;
	vector<int> ConvertToOctet(const std::string &);

	// Determine Binary
	vector<int> GetNetID();

	// 
	vector<int> GetNetIDRange();

	// Get total amount of subnets depending on submask
	int GetIncrement();

	// Caculate availabl ip in current subnet
	unsigned int GetHostsPerSubnet();
	
	// Convert Ip To Decimal
	unsigned int IpToDecimal(const vector<int> &);

	// Convert Ip from string to Decimal 
	unsigned int IpToDecimal(const string &);

	// Convert Ip from decimal to string
	string DecimalToIpString(const unsigned int &);

	// Convert Ip from decimal to string
	vector<int> DecimalToIpOtect(const unsigned int &);

	// Get IP in octet
	vector<int> OctetIP();

	// Get Netmask in octet;
	vector<int> OctetNetmask();

	// Get the first IP of subnet in otect format
	vector<int> StartIpOtect();

	// Get the first IP of subnet in string format
	string StartIpString();

	// Get the first IP of subnet in otect format
	vector<int> LatestIpOtect();

	// Get the first IP of subnet in string format
	string LatestIpString();

	// Static methods
	// Get Availavle netmask with given class level;
	static vector<vector<int>> GetAvailableNetMask(const char &network_class)
	{
		if (!(network_class == 'A' || network_class == 'a' ||
			network_class == 'B' || network_class == 'b' ||
			network_class == 'C' || network_class == 'c'
			))
		{
			throw string("Unavailable network class type (should be a, b or c)");
		}

		// Available netmask value
		vector<int> netmask_value = { 0, 128, 192, 224, 240, 248, 252, 254 };

		vector<vector<int>> netmask_list;
		switch (network_class)
		{
		case 'A':
		case 'a':
			for (int & var : netmask_value)
			{
				netmask_list.push_back({ 255, var, 0, 0 });
			}

			for (int & var : netmask_value)
			{
				netmask_list.push_back({ 255, 255, var, 0 });
			}

			for (int & var : netmask_value)
			{
				if (var == 254) continue;
				netmask_list.push_back({ 255, 255, 255, var });
			}
			break;
		case'B':
		case 'b':
			for (int & var : netmask_value)
			{
				netmask_list.push_back({ 255, 255, var, 0 });
			}

			for (int & var : netmask_value)
			{
				if (var == 254) continue;
				netmask_list.push_back({ 255, 255, 255, var });
			}

			break;
		case 'C':
		case 'c':
			for (int & var : netmask_value)
			{
				if (var == 254) continue;
				netmask_list.push_back({ 255, 255, 255, var });
			}
			break;
		}

		return netmask_list;
	}

	// Get Availavle netmask with given class level;
	//static vector<vector<int>> GetAvailableNetMask(const string &network_class)
	//{
	//	if (network_class.length() != 1)
	//	{
	//		throw std::string("Unavailable network class");
	//	}

	//	char char_network_class = network_class.c_str()[0];
	//	return GetAvailableNetMask(char_network_class);
	//}
private:
	// IP
	vector<int> octet_ip_;


	// Netmask
	vector<int> octet_netmask_;
};

