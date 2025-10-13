//
//  IOSConnection.h
//  ChineseChess
//
//  Created by Dong Truong Quang on 3/5/14.
//
//

#ifndef ChineseChess_IOSConnection_h
#define ChineseChess_IOSConnection_h

#include <string>

class IOSConnection
{
public:
    static std::string getIMEI();
	static std::string getDeviceModel();
    static void saveData(std::string key, std::string value);
    static void deleteData(std::string key);
    static std::string getData(std::string key);

    static void openURL(std::string url);
	
    static void goStore();
  
};


#endif
