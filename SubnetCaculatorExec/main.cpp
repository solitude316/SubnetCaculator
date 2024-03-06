#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include "subnetCaculator.h"
using namespace std;

int main()
{
	//string ip("10.0.0.5");
	//string netmask("255.0.0.0");

	try
	{
		//SubnetCaculator subnet(ip, netmask);

		SubnetCaculator subnet("192.168.0.180", "255.255.255.192");
		
		vector<vector<int>>available_netmask_list = SubnetCaculator::GetAvailableNetMask('c');

		cout << "Available Netmask : \n";
		for (vector<int>& item : available_netmask_list)
		{
			std::cout << item[0] << "." << item[1] << "." << item[2] << "." << item[3] << std::endl;
		}
		cout << "\n\n";

		std::vector<int> octets_ip = subnet.OctetIP();

		cout << "IP Address : " << octets_ip[0] << "." << octets_ip[1] << "." << octets_ip[2] << "." << octets_ip[3] << std::endl;
		
		std::vector<int> octets_netmask = subnet.OctetNetmask();

		cout << "Netmask : " << octets_netmask[0] << "." << octets_netmask[1] << "." << octets_netmask[2] << "." << octets_netmask[3] << std::endl;

		vector<int> net_id = subnet.GetNetID();
		cout << "NetID : " << net_id[0] << "." << net_id[1] << "." << net_id[2] << "." << net_id[3] << std::endl;

		vector<int> brocast_id = subnet.GetNetIDRange();
		cout << "Brocast ID : " << brocast_id[0] << "." << brocast_id[1] << "." << brocast_id[2] << "." << brocast_id[3] << std::endl;

		cout << "Total Hosts : " << subnet.GetHostsPerSubnet() << std::endl;

		cout << "IP to Decimal : " << subnet.IpToDecimal(subnet.OctetIP()) << std::endl;

		cout << "Get total amount of subnet : " << subnet.GetIncrement() << std::endl;

		cout << "IP to Decimal 220.134.119.194 \n";
		cout << subnet.IpToDecimal("220.134.119.194") << std::endl;
		cout << subnet.DecimalToIpString(subnet.IpToDecimal("220.134.119.194")) << std::endl;

		string start_ip = subnet.StartIpString();
		cout << "Start IP : " << start_ip << endl;

		string latest_ip = subnet.LatestIpString();
		cout << "Latest Ip : " << latest_ip << endl;

	}
	catch (std::string error_message)
	{
		std::cout << error_message << endl;
	}

	system("pause");

	return 0;
}