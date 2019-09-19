#pragma once

#include "ofMain.h"
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/DatagramSocket.h>
#include <Poco/Net/MulticastSocket.h>
#include <Poco/Net/NetworkInterface.h>
#include <Poco/Net/NetException.h>


class ofApp : public ofBaseApp{
	
	public:
		
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);		

        // member variables to store the current mouse X and Y position 
        // as a percentage of the width/height of the screen
        float mouseXPercent, mouseYPercent;
        map<string, Poco::Net::IPAddress> getNetworkInterfaces()
		{
		    map<string, Poco::Net::IPAddress> ret;

		    Poco::Net::NetworkInterface::Map m = Poco::Net::NetworkInterface::map(true, true);
		    assert (!m.empty());
		    for (Poco::Net::NetworkInterface::Map::const_iterator it = m.begin(); it != m.end(); ++it)
		    {
		        std::cout << std::endl << "=============" << std::endl;

		        std::cout << "Index:       " << it->second.index() << std::endl;
		        std::cout << "Name:        " << it->second.name() << std::endl;
		        std::cout << "DisplayName: " << it->second.displayName() << std::endl;
		        std::cout << "Status:      " << (it->second.isUp() ? "Up" : "Down") << std::endl;

		        Poco::Net::NetworkInterface::MACAddress mac(it->second.macAddress());
		        if (!mac.empty() && (it->second.type() != Poco::Net::NetworkInterface::NI_TYPE_SOFTWARE_LOOPBACK))
		                std::cout << "MAC Address: (" << it->second.type() << ") " << mac << std::endl;

		        typedef Poco::Net::NetworkInterface::AddressList List;

		        const List& ipList = it->second.addressList();
		        List::const_iterator ipIt = ipList.begin();
		        List::const_iterator ipEnd = ipList.end();
		        for (int counter = 0; ipIt != ipEnd; ++ipIt, ++counter)
		        {
		            int fam = ipIt->get<Poco::Net::NetworkInterface::IP_ADDRESS>().family();

		            std::cout << std::endl << "----------" << std::endl;
		            std::cout << "Address " << counter << std::endl;
		            std::cout << "----------" << std::endl;
		            std::cout << "Family:     " << fam << std::endl;
		            std::cout << "Address:     " << ipIt->get<Poco::Net::NetworkInterface::IP_ADDRESS>() << std::endl;
		            Poco::Net::IPAddress addr = ipIt->get<Poco::Net::NetworkInterface::SUBNET_MASK>();
		            if (!addr.isWildcard()) std::cout << "Subnet:      " << addr << " (/" << addr.prefixLength() << ")" << ")" << std::endl;
		                    addr = ipIt->get<Poco::Net::NetworkInterface::BROADCAST_ADDRESS>();
		            if (!addr.isWildcard()) std::cout << "Broadcast:   " << addr << std::endl;
		            if (fam == Poco::Net::AddressFamily::IPv4)
		            {
		                ret[it->second.name()] = ipIt->get<Poco::Net::NetworkInterface::IP_ADDRESS>();
		            }
		        }
		    }
		    return ret;
		}
};
	
