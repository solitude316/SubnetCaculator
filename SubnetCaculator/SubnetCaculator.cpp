#include "SubnetCaculator.h"
#include <vector>
#include <cstdlib>
#include <sstream>


SubnetCaculator::SubnetCaculator()
{
}


SubnetCaculator::SubnetCaculator(const string & ip_address, const string & netmask)
{
	//Validate IP
	octet_ip_.clear();
	SetOctetIp(ip_address);

	octet_netmask_.clear();
	SetOctetNetmask(netmask);
}


SubnetCaculator::~SubnetCaculator()
{
}


vector<int> SubnetCaculator::ConvertToOctet(const string &address)
{
	std::stringstream address_stream(address);
	string temp;

	vector<int> octets_address;
	while (getline(address_stream, temp, '.'))
	{
		octets_address.push_back(atoi(temp.c_str()));
	}

	return octets_address;
}

bool SubnetCaculator::SetOctetIp(const string &ip)
{
	if (ip == "127.0.0.1")
	{
		throw string( ip + " is loopback.");
	}

	octet_ip_ = ConvertToOctet(ip);
	
	if (octet_ip_.size() != 4)
	{
		octet_ip_.clear();
		throw string("IP format error : " + ip);
	}

	for (unsigned int i = 0; i < octet_ip_.size(); i++)
	{
		if (octet_ip_[i] < 0 || octet_ip_[i] > 255)
		{
			throw string("Ip out of range" + ip);
		}
	}

	return true;
}

bool SubnetCaculator::SetOctetNetmask(const string &netmask)
{
	octet_netmask_ = ConvertToOctet(netmask);

	if (octet_netmask_.size() != 4)
	{
		throw string("Netmask format error : " + netmask);
	}

	if (octet_netmask_[0] != 255)
	{
		throw string("Netmask noet available : " + netmask);
	}

	for (unsigned int i = 1; i < octet_netmask_.size(); i++)
	{
		if (!(
			octet_netmask_[i] == 0 ||
			octet_netmask_[i] == 128 ||
			octet_netmask_[i] == 192 ||
			octet_netmask_[i] == 224 ||
			octet_netmask_[i] == 240 ||
			octet_netmask_[i] == 248 ||
			octet_netmask_[i] == 252 ||
			octet_netmask_[i] == 254 ||
			octet_netmask_[i] == 255
			))
		{
			throw string("Netmask not available : " + netmask);
		}
	}

	return true;
}

vector<int> SubnetCaculator::StartIpOtect()
{
	int start_ip = IpToDecimal(GetNetID()) + 1;
	return DecimalToIpOtect(start_ip);
}


string SubnetCaculator::StartIpString()
{
	int start_ip = IpToDecimal(GetNetID()) + 1;
	return DecimalToIpString(start_ip);
}


vector<int> SubnetCaculator::LatestIpOtect()
{
	int latest_ip = IpToDecimal(GetNetID()) + GetHostsPerSubnet();
	return DecimalToIpOtect(latest_ip);
}


string SubnetCaculator::LatestIpString()
{
	int latest_ip = IpToDecimal(GetNetID()) + GetHostsPerSubnet();
	return DecimalToIpString(latest_ip);
}


vector<int> SubnetCaculator::GetNetID()
{
	vector<int> net_id;

	for (unsigned int i = 0; i < octet_ip_.size(); i++)
	{
		net_id.push_back(octet_ip_[i] & octet_netmask_[i]);
	}

	return net_id;
}



vector<int> SubnetCaculator::GetNetIDRange()
{
	vector<int> net_id_end;
	vector<int> net_id = GetNetID();

	for (unsigned int i = 0; i < net_id.size(); i++)
	{
		if (octet_netmask_[i] == 255)
		{
			net_id_end.push_back(net_id[i]);
		}
		else if (octet_netmask_[i] < 255 && octet_netmask_[i] > 0)
		{
			net_id_end.push_back((net_id[i] + GetIncrement()) - 1);
		}
		else
		{
			net_id_end.push_back(255);
		}
	}

	return net_id_end;
}



int SubnetCaculator::GetIncrement()
{
	int increment = 1;
	for (unsigned int i = 0; i < octet_netmask_.size(); i++)
	{
		switch (octet_netmask_[i])
		{
		case 254:
			increment = 1 << 7;
			break;
		case 252:
			increment = 1 << 6;
			break;
		case 248:
			increment = 1 << 5;
			break;
		case 240:
			increment = 1 << 4;
			break;
		case 224:
			increment = 1 << 3;
			break;
		case 192:
			increment = 1 << 2;
			break;
		case 128:
			increment = 1 << 1;
			break;
		}
	}
	return increment;
}


unsigned int SubnetCaculator::IpToDecimal(const vector<int> &octets_ip)
{
	unsigned int ip = 16777216 * octets_ip[0] +
		(octets_ip[1] << 16) +
		(octets_ip[2] << 8) +
		octets_ip[3];

	return ip;
}


unsigned int SubnetCaculator::IpToDecimal(const string &str_ip)
{
	vector<int> octets_ip = ConvertToOctet(str_ip);
	return IpToDecimal(octets_ip);
}


string SubnetCaculator::DecimalToIpString(const unsigned int & ip)
{
	vector<int> otect_ip = DecimalToIpOtect(ip);

	std::stringstream str_ip;

	str_ip << otect_ip[0] << "." << otect_ip[1] << "."
		<< otect_ip[2] << "." << otect_ip[3];

	return str_ip.str();
}

vector<int> SubnetCaculator::DecimalToIpOtect(const unsigned int & ip)
{
	vector<int> otect_ip;

	otect_ip.push_back(ip / 16777216);
	otect_ip.push_back((ip % 16777216) / 65536);
	otect_ip.push_back((ip % 65536) / 256);
	otect_ip.push_back(ip % 256);

	return otect_ip;
}


unsigned int SubnetCaculator::GetHostsPerSubnet()
{
	int total_hosts = (256 - octet_netmask_[0]) * (256 - octet_netmask_[1])
			* (256 - octet_netmask_[2]) * (256 - octet_netmask_[3]) - 2;
	return total_hosts;
}



vector<int> SubnetCaculator::OctetIP()
{
	return octet_ip_;
}



vector<int> SubnetCaculator::OctetNetmask()
{
	return octet_netmask_;
}